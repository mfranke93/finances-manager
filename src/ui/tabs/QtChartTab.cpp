#include "QtChartTab.h"

QtChartTab::QtChartTab()
:   QWidget(nullptr)
{
    QLineSeries * series = new QLineSeries;
    QTime time (12, 0,0);
    series->append(QDateTime(QDate(2017,12,31), time).toMSecsSinceEpoch(), 12.3);
    series->append(QDateTime(QDate(2018,1,1), time).toMSecsSinceEpoch(), 12.4);
    series->append(QDateTime(QDate(2018,1,2), time).toMSecsSinceEpoch(), 12.2);
    series->append(QDateTime(QDate(2018,1,3), time).toMSecsSinceEpoch(), 12.15);

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

    QChartView * chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setLayout(new QVBoxLayout);
    layout()->addWidget(chartView);
}
