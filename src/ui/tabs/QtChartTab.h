#include <QtWidgets>
#include <QtCharts>

#include "../charts/ChartAreaFactory.h"

#pragma once

class QtChartTab : public QWidget
{
public:
    QtChartTab();
    ~QtChartTab() = default;

public slots:
    void rebuildPlot();

private:
    QChartView * chartView;
};
