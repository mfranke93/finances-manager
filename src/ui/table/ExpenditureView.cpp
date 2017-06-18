//
// Created by max on 30/09/16.
//

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
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setDefaultSectionSize(20);
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    this->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->priceColumnDelegate = new PriceColumnDelegate;
    this->setItemDelegateForColumn(4, priceColumnDelegate);

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
    while (model->canFetchMore()) model->fetchMore();
    this->scrollToBottom();
}

void
ExpenditureView::resizeEvent(QResizeEvent * event)
{
    this->resizeColumnsToContents();
    this->onPressReload();
    QTableView::resizeEvent(event);
}
