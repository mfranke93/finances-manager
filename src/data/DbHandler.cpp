//
// Created by max on 04/10/16.
//

#include "DbHandler.h"

DbHandler * DbHandler::instance = nullptr;

DbHandler::DbHandler()
: database(QSqlDatabase::addDatabase("QSQLITE"))
{
    database.setDatabaseName("/home/max/dev/finances-manager/data.db");
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

    return query.exec();
}

bool
DbHandler::insertNewRecipient(QString const& name,
                              QString const& address,
                              bool const& isOnline)
{
    QSqlQuery query (database);
    query.prepare("INSERT INTO Recipient (name, address, isOnline) VALUES (:name, :address, :isOnline);");
    query.bindValue(":name", name);
    query.bindValue(":address", address);
    query.bindValue(":isOnline", isOnline);

    return query.exec();
}
