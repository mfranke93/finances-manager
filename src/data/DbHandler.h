//
// Created by max on 04/10/16.
//


#pragma once

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <iostream>
#include <QtCore/QDate>
#include <QVariant>

class DbHandler
{
public:
    static DbHandler * const getInstance()
    {
        if (instance == nullptr)
        {
            instance = new DbHandler;
        }

        return instance;
    }

    DbHandler(DbHandler const&) = delete;
    DbHandler& operator= (DbHandler const&) = delete;

    bool insertNewCategory(QString const& name);
    bool insertNewRecipient(QString const& name, QString const& address, bool const& isOnline);
    bool insertNewItem(QString const& name, int const& recipientId, QDate const& date, QString const& price, int const& categoryId);
    static DbHandler * instance;

    QSqlDatabase& getDatabase() { return database; }

private:
    DbHandler();

    QSqlDatabase database;
};


