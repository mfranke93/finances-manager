#include "QtChartTab.h"

QtChartTab::QtChartTab()
:   QWidget(nullptr)
{
    chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    rebuildPlot();

    setLayout(new QVBoxLayout);
    layout()->addWidget(chartView);
}

void
QtChartTab::rebuildPlot()
{
    auto items = DbHandler::getInstance()->getRawItems();
    std::map<QDate, double> accumulated {};
    std::for_each(items.begin(), items.end(), [&accumulated](RawItem const& item)
            {
                accumulated[item.date] += item.price;
            });

    using mapentry = typename decltype(accumulated)::value_type;
    QLineSeries * series = new QLineSeries;
    QTime time (12, 0, 0);
    double accum {0.0};
    std::for_each(accumulated.begin(), accumulated.end(), [&series,&time,&accum](mapentry const& v)
            {
                accum += v.second;
                series->append(QDateTime(v.first, time).toMSecsSinceEpoch(), accum);
            });

    QChart * chart = new QChart;
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
