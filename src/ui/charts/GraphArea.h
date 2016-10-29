//
// Created by max on 10/10/16.
//


#pragma once

#include <cmath>
#include <QtWidgets/QWidget>
#include "BarGraph.h"

class GraphArea : public QWidget
{
    Q_OBJECT

public:
    GraphArea();
    ~GraphArea() = default;

    void addBar(QString const& name, double const& min, double const& max);
    void clearBars() { bars.clear(); emit repaint(); };

public slots:
    void paintEvent(QPaintEvent * evt) override;
    void resizeEvent(QResizeEvent * evt) override;
    void rebuildBars();
    void reloadEvent();

private:
    GraphArea(QWidget * parent) : QWidget(parent) {};

    std::vector<std::pair<QString, BarGraph>> bars;
    PriceScaler scale;
    std::pair<double, double> range;

    int heightPerBar = 200;
    int yOffset = 20;
};


