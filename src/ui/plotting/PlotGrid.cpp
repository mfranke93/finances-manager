//
// Created by max on 09/10/16.
//

#include <cmath>
#include "PlotGrid.h"

PlotGrid::PlotGrid(std::pair<QDate const, QDate const> const& dateRange,
                   std::pair<double const, double const> const& priceRange,
                   DateToIntConverter const& dti,
                   VerticalScaler const& vs)
: dateRange(dateRange), priceRange(priceRange), dtiConverter(dti), vScaler(vs),
  boundingRect_(QPoint(dti(dateRange.first), vs(priceRange.second)),
                QPoint(dti(dateRange.second), vs(priceRange.first)))
{
    // ctor
}

void PlotGrid::plot(QPainter * const painter) const
{
    int const yBot = vScaler(priceRange.first);
    int const yTop = vScaler(priceRange.second);
    int const xBot = dtiConverter(dateRange.first);
    int const xTop = dtiConverter(dateRange.second);

    int const yStep = 50;
    int const yMajor = 200;

    QPen minorPen (QColor(220, 220, 220));
    minorPen.setWidthF(0.5);
    QPen majorPen (QColor(160, 160, 160));
    majorPen.setWidthF(0.7);
    QPen zeroLine (QColor(80,80,80));
    zeroLine.setWidthF(1.0);

    // horizontal lines
    int y = int(std::ceil(priceRange.first/yStep))*yStep;
    while (y <= int(priceRange.second))
    {
        int const coordY = vScaler(y);
        if (y == 0) painter->setPen(zeroLine);
        else if (y%yMajor == 0) painter->setPen(majorPen);
        else painter->setPen(minorPen);
        painter->drawLine(xBot, coordY, xTop, coordY);
        y += yStep;
    }

    // vertical lines
    for (QDate d = dateRange.first; d <= dateRange.second; d = d.addDays(1))
    {
        int const x = dtiConverter(d);
        if (d.day() == 1) painter->setPen(zeroLine);
        else if (d.dayOfWeek() == 1) painter->setPen(majorPen);
        else painter->setPen(minorPen);
        painter->drawLine(x, yBot, x, yTop);
    }
}