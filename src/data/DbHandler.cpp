//
// Created by max on 04/10/16.
//

#include <stdlib.h>
#include "DbHandler.h"

DbHandler * DbHandler::instance = nullptr;

DbHandler::DbHandler()
: database(QSqlDatabase::addDatabase("QSQLITE"))
{
    database.setDatabaseName("/home/max/prog/finances-manager/data.db");
    if (!database.open())
    {
        std::cerr << "Could not open database at " << database.databaseName().toStdString() << std::endl;
        exit(1);
    }
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys=ON;");
    query.finish();
}

bool
DbHandler::insertNewItem(QString const& name,
                         int const& recipientId,
                         QDate const& date,
                         QString const& price,
                         int const& categoryId)
{
    QSqlQuery query (database);
    query.prepare("INSERT INTO Item (name, recid, date, price, catid) VALUES (:name, :recid, :date, :price, :catid);");
    query.bindValue(":name", name);
    query.bindValue(":recid", recipientId);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":price", price);
    query.bindValue(":catid", categoryId);

    return (itemsChanged = query.exec());
}

bool
DbHandler::insertNewRecipient(QString const& name,
                              QString const& address,
                              bool const& isOnline)
{
    QSqlQuery query (database);
    query.prepare("INSERT INTO Recipient (name, address, online) VALUES (:name, :address, :isOnline);");
    query.bindValue(":name", name);
    query.bindValue(":address", address);
    query.bindValue(":isOnline", isOnline?1:0);

    bool const b = query.exec();
    if (!b)
    {
        std::cerr << database.lastError().text().toStdString() << std::endl;
    }
    return b;
}

bool
DbHandler::insertNewCategory(QString const& name)
{
    QSqlQuery query (database);
    query.prepare("INSERT INTO Category (name) VALUES (:name);");
    query.bindValue(":name", name);

    bool const b = query.exec();
    if (!b)
    {
        std::cerr << database.lastError().text().toStdString() << std::endl;
    }
    return b;
}

bool
DbHandler::commit()
{
    bool b = database.commit();
    if (b && itemsChanged)
    {
        emit itemDataChanged();
        itemsChanged = false;
    }

    return b;
}

std::pair<QDate, QDate>
DbHandler::getDateRange() const
{
    QSqlQuery query(database);
    query.prepare("SELECT min(date) AS start, max(date) as end FROM Item;");
    bool const b = query.exec();
    if (!b)
    {
        std::cerr << database.lastError().text().toStdString() << std::endl;
        exit(1);
    }

    if (!query.next())
    {
        std::cerr << "No dates in table" << std::endl;
        exit(1);
    }

    QDate const start = query.value("start").toDate();
    QDate const end = query.value("end").toDate();

    return std::make_pair(start, end);
}
