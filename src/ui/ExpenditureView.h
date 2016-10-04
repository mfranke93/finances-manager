//
// Created by max on 30/09/16.
//


#pragma once

#include <QtWidgets/QTableView>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>

class ExpenditureView : public QTableView
{
    Q_OBJECT
public:
    ExpenditureView(QWidget * parent = nullptr);
    ~ExpenditureView();

    static bool createConnection()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/max/dev/finances/data.db");
        if (!db.open()) return false;
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys=ON;");
        return true;
    }

public slots:
    void onPressReload();
private:
    QSqlTableModel * model;
};


