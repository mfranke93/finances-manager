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
    painter->setRenderHint(QPainter::Antialiasing, false);
    QPen pen (frameColor_, 1, Qt::SolidLine, Qt::SquareCap, Qt::PenJoinStyle::MiterJoin);
    pen.setMiterLimit(10);
    painter->setPen(pen);
    painter->setBrush(areaColor_);
    painter->drawRect(area_);
    painter->setRenderHint(QPainter::Antialiasing);
}
