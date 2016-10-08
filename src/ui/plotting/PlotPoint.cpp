//
// Created by max on 08/10/16.
//

#include "PlotPoint.h"

PlotPoint::PlotPoint(int const& x, int const& y, double const& radius, const QColor& color)
: x(x), y(y), radius(radius), color(color)
{
    // ctor
}

void
PlotPoint::paint(QPainter * const painter) const
{
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(x-radius, y-radius, 2*radius, 2*radius);
}

void
PlotPoint::drawLine(QPainter * const painter, PlotPoint const& other, QColor const& color) const
{
    painter->setBrush(Qt::NoBrush);
    painter->setPen(color);
    painter->drawLine(x, y, other.x, other.y);
}