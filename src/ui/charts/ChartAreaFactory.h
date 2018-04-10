#include <QtCharts>
#include "../../data/DbHandler.h"
#include "../../plotting/aggregation.h"
#include "ChartArea.h"

#pragma once

struct ChartAreaFactory
{
    template<typename AggregatorFn, typename GroupFn>
    QChart * buildChart(AggregatorFn agg, GroupFn grp)
    {
        auto items = DbHandler::getInstance()->getRawItems();
        auto accumulated = aggregate(items, agg, grp);

        using mapentry = typename decltype(accumulated)::value_type;
        QLineSeries * series = new QLineSeries;
        QTime time (12, 0, 0);
        std::for_each(accumulated.begin(), accumulated.end(), [&series,&time](mapentry const& v)
                {
                series->append(QDateTime(v.first, time).toMSecsSinceEpoch(), v.second);
                });

        QChart * chart = new ChartArea;
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setTitle("Test");

        QDateTimeAxis * axisX = new QDateTimeAxis;
        axisX->setTickCount(1);
        axisX->setFormat("dd MMM yyyy");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis * axisY = new QValueAxis;
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Value");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        return chart;
    }
};
