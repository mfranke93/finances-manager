//
// Created by max on 10/10/16.
//

#include "BarGraph.h"

BarGraph::BarGraph()
{
    // ctor
}

void
BarGraph::paint(QPainter * const painter) const
{
    painter->setClipRect(boundingRectangle.adjusted(0,0,0,1));
    painter->setClipping(true);

    int x1 = boundingRectangle.x() + 5;
    int x2 = boundingRectangle.x() + boundingRectangle.width() - 5;

    int y1 = scale(range.second) + boundingRectangle.y();
    int y2 = scale(0.0) + boundingRectangle.y();
    int y3 = scale(range.first) + boundingRectangle.y();

    painter->setBrush(colorPositive);
    painter->setPen(colorPositive.darker());

    painter->drawRect(x1, y1, x2-x1, y2-y1);

    painter->setBrush(colorNegative);
    painter->setPen(colorNegative.darker());
    painter->drawRect(x1, y2, x2-x1, y3-y2);

    painter->setClipping(false);
}

void
BarGraph::setPriceScaler(PriceScaler p)
{
    scale = p;
}

void
BarGraph::setBoundingRect(QRect const& r)
{
    boundingRectangle = r;
}

void
BarGraph::setColors(QColor const& positive, QColor const& negative)
{
    colorPositive = positive;
    colorNegative = negative;
}

void
BarGraph::setRange(double const& min, double const& max)
{
    range.first = min;
    range.second = max;
}

