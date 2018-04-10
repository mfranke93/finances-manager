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
    auto items = DbHandler::getInstance()->getRawItems();
    sum_of_price sum {};
    group_by_month by_month {};
    auto by_week = [](RawItem const& item) -> QDate
    {
        int const day_of_week = item.date.dayOfWeek();
        int const difference = 1 - day_of_week;
        return item.date.addDays(difference);
    };
    std::map<QDate, double> accumulated = aggregate(items, sum, by_week);

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

    chartView->setChart(chart);
}
