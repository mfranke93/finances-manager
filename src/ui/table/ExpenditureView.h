//
// Created by max on 30/09/16.
//


#pragma once

#include <QtWidgets/QTableView>
#include <QtWidgets/QScrollBar>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QHeaderView>
#include <data/DbHandler.h>

class ExpenditureView : public QTableView
{
    Q_OBJECT
public:
    ExpenditureView(QWidget * parent = nullptr);
    ~ExpenditureView();

protected:
    virtual void resizeEvent(QResizeEvent * event) override;

public slots:
    void onPressReload();
private:
    QSqlTableModel * model;
};


