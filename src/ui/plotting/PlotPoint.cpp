//
// Created by max on 08/10/16.
//

#include "PlotPoint.h"

PlotPoint::PlotPoint(int const& x, int const& y, double const& radius, const QColor& color)
: x(x), y(y), yRange(std::make_pair(y,y)), radius(radius), color(color)
{
    // ctor
}

void
PlotPoint::setYRange(int const& yMin, int const& yMax)
{
    yRange.first = yMin;
    yRange.second = yMax;
}

void
PlotPoint::paint(QPainter * const painter) const
{
    // draw dot
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(x-radius, y-radius, 2*radius, 2*radius);
}

void
PlotPoint::drawLine(QPainter * const painter, PlotPoint const& other, QColor const& color, bool const& drawYRange) const
{
    if (drawYRange)
    {
        // draw lower trapez
        {
            QPainterPath path;
            path.moveTo(x, y);
            path.lineTo(x, yRange.first);
            path.lineTo(other.x, other.yRange.first);
            path.lineTo(other.x, other.y);
            path.lineTo(x, y);
            painter->setBrush(QColor(205, 20, 20, 70));
            painter->setPen(Qt::NoPen);
            painter->fillPath(path, QColor(205, 20, 20, 70));
            painter->setPen(QColor(205, 20, 20, 140));
            painter->setBrush(Qt::NoBrush);
            painter->drawLine(other.x, other.yRange.first, x, yRange.first);
        }

        // draw upper trapez
        {
            QPainterPath path;
            path.moveTo(x, y);
            path.lineTo(x, yRange.second);
            path.lineTo(other.x, other.yRange.second);
            path.lineTo(other.x, other.y);
            path.lineTo(x, y);
            painter->setBrush(QColor(20, 20, 205, 70));
            painter->setPen(Qt::NoPen);
            painter->fillPath(path, QColor(20, 20, 205, 70));
            painter->setPen(QColor(20, 20, 205, 140));
            painter->setBrush(Qt::NoBrush);
            painter->drawLine(other.x, other.yRange.second, x, yRange.second);
        }
    }

    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(color, 2));
    painter->drawLine(x, y, other.x, other.y);
}