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
}

ChartTab::ChartTab()
: ChartTab(nullptr)
{
    // ctor
    mainLayout = new QVBoxLayout;
    area = new GraphArea;
    mainLayout->addWidget(area);

    setLayout(mainLayout);

    reloadData();

    connect(DbHandler::getInstance(), SIGNAL(itemDataChanged()), area, SLOT(reloadEvent()));
}

void
ChartTab::reloadData()
{
    area->clearBars();

    std::map<QString, std::pair<double, double>> ranges;

    QSqlQuery query;
    query.prepare("SELECT Category.name AS cat, Item.price AS amount FROM ITEM JOIN Category ON Item.catid = Category.id ORDER BY cat;");
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
}