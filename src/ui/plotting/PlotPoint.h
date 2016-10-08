//
// Created by max on 08/10/16.
//


#pragma once


#include <QtGui/QColor>
#include <QtGui/QPainter>

class PlotPoint
{
public:
    PlotPoint() = delete;
    PlotPoint(int const& x, int const& y, double const& radius, QColor const& color = QColor(0,0,0));
    ~PlotPoint() = default;
    PlotPoint(PlotPoint const&) = default;
    PlotPoint& operator= (PlotPoint const&) = delete;

    void paint(QPainter * const painter) const;
    inline void drawLine(QPainter * const painter, PlotPoint const& other) const { drawLine(painter, other, color); };
    /* use start point color instead */
    void drawLine(QPainter * const painter, PlotPoint const& other, QColor const& color) const;

private:
    int x, y;
    double radius;
    QColor color;

};


