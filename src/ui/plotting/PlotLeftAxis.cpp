//
// Created by max on 09/10/16.
//

#include "PlotLeftAxis.h"

PlotLeftAxis::PlotLeftAxis(int const& leftMargin, int const& topMargin, int const& innerHeight,
                           std::pair<double const, double const> const& range)
: leftMargin(leftMargin), topMargin(topMargin), innerHeight(innerHeight), range(range)
{
    // ctor
}

void
PlotLeftAxis::setVerticalScaler(VerticalScaler const& verticalScaler)
{
    this->vScaler = verticalScaler;
}

void
PlotLeftAxis::plot(QPainter * const painter) const
{
    char buf [10];
    int const x = 5;
    int step = 200;
    // find lowest denomination of step
    int y = int(ceil(range.first/step))*step;

    QColor red = QColor(205, 20, 20);
    QColor black = QColor(0,0,0);
    painter->setFont(QFont("Monospace", 8));
    while (y <= int(range.second))
    {
        painter->setPen((y>=0)?black:red);
        sprintf(buf, "%4d €", y);
        QString label (buf);
        painter->drawText(x, vScaler(y)+5, label);

        y += step;
    }
}
