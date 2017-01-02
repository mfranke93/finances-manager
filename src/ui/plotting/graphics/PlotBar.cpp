//
// Created by max on 28/12/16.
//

#include "PlotBar.h"

PlotBar::PlotBar(QRect const& rect, QColor const& frame, QColor const& area)
: area_(rect), frameColor_(frame), areaColor_(area)
{
    // ctor
}

void
PlotBar::plot(QPainter * const painter) const
{
    painter->setPen(frameColor_);
    painter->setBrush(areaColor_);
    painter->drawRect(area_);
}
