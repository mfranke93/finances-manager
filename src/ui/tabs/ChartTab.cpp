//
// Created by max on 10/10/16.
//

#include <QtSql/QSqlQuery>
#include <iostream>
#include <data/DbHandler.h>
#include "ChartTab.h"

ChartTab::ChartTab(QWidget * parent)
: QWidget(parent)
{
    // ctor
    mainLayout = new QVBoxLayout;
    area = new GraphArea;
    mainLayout->addWidget(area);
    auto p = DbHandler::getInstance()->getDateRange();
    dateFilterPane = new DateFilterPane(nullptr, p.first, p.second);
    mainLayout->addWidget(dateFilterPane);

    setLayout(mainLayout);


    connect(DbHandler::getInstance(), SIGNAL(itemDataChanged()), this, SLOT(reloadData()));
    connect(this, SIGNAL(barDataChanged()), area, SLOT(reloadEvent()));
    connect(dateFilterPane, SIGNAL(dateRangeChanged()), this, SLOT(reloadData()));
    connect(DbHandler::getInstance(), SIGNAL(dateRangeChanged(std::pair<QDate, QDate>)),
            dateFilterPane, SLOT(onDateRangeChanged(std::pair<QDate, QDate>)));
    reloadData();

    dateFilterPane->onClickReset();
}

ChartTab::ChartTab()
: ChartTab(nullptr)
{
    // ctor
}

void
ChartTab::reloadData()
{
    dateFilterPane->setValidRange(DbHandler::getInstance()->getDateRange());
    area->clearBars();

    std::map<QString, std::pair<double, double>> ranges;

    QSqlQuery query;
    query.prepare("SELECT Category.name AS cat, Item.price AS amount FROM ITEM JOIN Category ON Item.catid = Category.id"
                          " WHERE Item.date >= :start"
                          " AND Item.date <= :end"
                          " ORDER BY cat;");
    auto p = dateFilterPane->getRange();
    query.bindValue(":start", p.first.toString("yyyy-MM-dd"));
    query.bindValue(":end", p.second.toString("yyyy-MM-dd"));
    query.exec();
    while (query.next())
    {
        QString cat = query.value("cat").toString();
        double amount = query.value("amount").toDouble();

        if (ranges.find(cat) == ranges.end())
        {
            ranges[cat] = std::make_pair(0.0, 0.0);
        }

        if (amount < 0) ranges[cat].first += amount;
        else ranges[cat].second += amount;
    }

    // sort
    std::map<double, QString> sorterMap;
    for (auto it:ranges) sorterMap[it.second.first + it.second.second] = it.first;


    for (auto it : sorterMap)
    {
        area->addBar(it.second, ranges[it.second].first, ranges[it.second].second);
    }

    emit barDataChanged();
    emit repaint();
}
