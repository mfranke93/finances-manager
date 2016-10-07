//
// Created by max on 06/10/16.
//


#pragma once


#include <QtSql/QtSql>
#include <QtWidgets/QPushButton>
#include "ExpenditureView.h"
#include "../data/DbHandler.h"
#include "AddItemDialog.h"

class TableTab : public QWidget
{
    Q_OBJECT

public:
    TableTab(QWidget * parent);
    ~TableTab();

protected slots:
    void onPressCreate();

private:
    ExpenditureView * table;
    QPushButton * reload;
    QPushButton * create;
};


