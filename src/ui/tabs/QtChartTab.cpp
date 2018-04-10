#include "QtChartTab.h"

QtChartTab::QtChartTab()
:   QWidget(nullptr)
{
    chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    rebuildPlot();

    setLayout(new QVBoxLayout);
    layout()->addWidget(chartView);

    // connect DbHandler signal
    connect(DbHandler::getInstance(), &DbHandler::itemDataChanged,
            this, &QtChartTab::rebuildPlot);
}

void
QtChartTab::rebuildPlot()
{
    sum_of_price sum {};
    auto by_day = [](RawItem const& item) -> QDate
    {
        return item.date;
    };
    ChartAreaFactory factory {};
    auto chart = factory.buildChart(sum, by_day);

    chartView->setChart(chart);
}
