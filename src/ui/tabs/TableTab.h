//
// Created by max on 06/10/16.
//


#pragma once


#include <QtSql/QtSql>
#include <QtWidgets/QPushButton>
#include "ui/table/ExpenditureView.h"
#include "data/DbHandler.h"
#include "data/RecurrentItemTemplate.h"
#include "ui/dialogs/AddItemDialog.h"
#include "ui/dialogs/SelectRecurrentItemTemplateDialog.h"

class TableTab : public QWidget
{
    Q_OBJECT

public:
    TableTab(QWidget * parent);
    ~TableTab();

protected slots:
    void onPressCreate();
    void onPressCreateFromTemplate();

protected:
    void showAddItemDialog(std::shared_ptr<RecurrentItem> recurrent);

private:
    ExpenditureView * table;
    QPushButton * reload;
    QPushButton * create;
    QPushButton * createFromTemplate;
};


