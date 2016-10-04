//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHeaderView>
#include "ExpenditureView.h"

ExpenditureView::ExpenditureView(QWidget * parent)
{
    this->model = new QSqlTableModel(parent);
    model->setTable("Expenditures");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    this->setStyleSheet("font: 12px Monospace;");
    this->setModel(this->model);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    this->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    this->setSortingEnabled(true);
}

ExpenditureView::~ExpenditureView()
{
    delete model;
}

void
ExpenditureView::onPressReload()
{
    this->model->select();
}
