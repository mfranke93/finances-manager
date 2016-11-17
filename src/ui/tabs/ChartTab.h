//
// Created by max on 10/10/16.
//


#pragma once


#include <QtWidgets/QWidget>
#include <ui/charts/BarGraph.h>
#include <ui/charts/GraphArea.h>
#include <QtWidgets/QVBoxLayout>
#include <ui/common/DateFilterPane.h>

class ChartTab : public QWidget
{
Q_OBJECT
signals:
    void barDataChanged();
public:

    ChartTab();

    ~ChartTab() = default;

    ChartTab(ChartTab const&) = delete;

    ChartTab& operator=(ChartTab const&) = delete;

public slots:
    void reloadData();

private:
    ChartTab(QWidget * parent);

    QVBoxLayout * mainLayout;
    GraphArea * area;
    DateFilterPane * dateFilterPane;
};


