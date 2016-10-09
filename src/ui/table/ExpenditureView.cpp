//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHeaderView>
#include <data/DbHandler.h>
#include "ExpenditureView.h"

ExpenditureView::ExpenditureView(QWidget * parent)
{
    this->model = new QSqlTableModel(parent, DbHandler::getInstance()->getDatabase());
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
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setSortingEnabled(true);
    this->horizontalHeader()->setSortIndicator(2, Qt::SortOrder::AscendingOrder);
}

ExpenditureView::~ExpenditureView()
{
    delete model;
}

void
ExpenditureView::onPressReload()
{
    this->model->select();
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
}

void
ExpenditureView::resizeEvent(QResizeEvent * event)
{
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    QTableView::resizeEvent(event);
}