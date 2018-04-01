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
#include <QObject>
#include <QFile>
#include <QTextStream>

#include "RecurrentItemTemplate.h"
#include "../plotting/RawItem.h"

class DbHandler : public QObject
{
    Q_OBJECT
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

    std::pair<QDate, QDate> getDateRange() const;

    QSqlDatabase& getDatabase() { return database; }
    bool commit();

    QString getRecipientStringFromId(int const recId) const;

    void restoreDatabaseFromFile(QString const& fileName);

    std::shared_ptr<std::map<QString, RecurrentItemTemplate>> getRecurringTemplates();

    std::vector<RawItem> getRawItems();

signals:
    void itemDataChanged();
    void dateRangeChanged(std::pair<QDate, QDate>);

private:
    DbHandler();

    QSqlDatabase database;
    bool itemsChanged = false;
};


