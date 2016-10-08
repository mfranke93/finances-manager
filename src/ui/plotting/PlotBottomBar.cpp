//
// Created by max on 08/10/16.
//

#include "PlotBottomBar.h"

PlotBottomBar::PlotBottomBar(int const& bottomMargin,
                             int const& leftMargin,
                             int const& offset,
                             std::pair<QDate const, QDate const> dateRange)
: bottomMargin(bottomMargin), leftMargin(leftMargin), offset(offset), dateRange(dateRange)
{
    // ctor
}

void
PlotBottomBar::plot(QPainter * const painter) const
{
    // TODO: omit dates if too little space between points
    int const y = offset - bottomMargin + 5;

    painter->setFont(QFont("Monospace", 8));
    painter->setPen(QColor(0,0,0));

    for (QDate d = dateRange.first; d <= dateRange.second; d = d.addDays(1))
    {
        painter->drawText(dtiConverter(d)-15, y, d.toString("dd.MM."));
    }
}