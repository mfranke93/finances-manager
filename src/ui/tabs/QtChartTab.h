#include <QtWidgets>
#include <QtCharts>

#include "../../data/DbHandler.h"
#include "../../plotting/aggregation.h"
#include "../charts/ChartArea.h"

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
