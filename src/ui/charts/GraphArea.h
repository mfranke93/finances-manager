//
// Created by max on 10/10/16.
//


#pragma once

#include <iostream>
#include <data/ResourceHandler.h>
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
    void clearBars() { bars.clear(); range = std::make_pair(0.0, 0.0); emit repaint(); };

public slots:
    void paintEvent(QPaintEvent * evt) override;
    void resizeEvent(QResizeEvent * evt) override;
    void rebuildBars();
    void reloadEvent();
    void mouseMoveEvent(QMouseEvent * evt) override;

private:
    GraphArea(QWidget * parent) : QWidget(parent) {};

    std::pair<QString, BarGraph> const& getBarAt(int const& posX) const;

    std::vector<std::pair<QString, BarGraph>> bars;
    PriceScaler scale;
    std::pair<double, double> range;

    int heightPerBar = 200;
    int yOffset = 20;
    int widthPerBar = 120;

    constexpr static int xOffsetGlobal = 50;
};


