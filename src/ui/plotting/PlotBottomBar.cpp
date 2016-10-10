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

    std::vector<QDate> * vec = calculatePrintedDates(painter);
    for (QDate const& d : *vec)
    {
        painter->drawText(dtiConverter(d)-15, y+5, d.toString("dd.MM."));
    }
    delete vec;
}

std::vector<QDate> *
PlotBottomBar::calculatePrintedDates(QPainter * const painter) const
{
    std::vector<QDate> * vec = new std::vector<QDate>;
    // take random date as we use monospaced font anyways
    QString sample ("12.04.");
    QRect boundingRectangle = painter->fontMetrics().boundingRect(sample);
    int distTwoDates = dtiConverter(dateRange.first.addDays(1)) - dtiConverter(dateRange.first);

    double quot = double(distTwoDates) / double(boundingRectangle.width());
    int factor = 1;

    while (factor * quot < 1.2) ++factor;

    // take first date, first of each month, last
    /**
     * steps:
     * each day, first of each week, first of each month
     */
    // TODO: first of month when stepping through weeks
    if (factor == 1)
    {
        for (QDate d = dateRange.first; d <= dateRange.second; d = d.addDays(1)) vec->push_back(d);
    }
    else if (factor <= 7)
    {
        vec->push_back(dateRange.first);
        for (QDate d = dateRange.first.addDays(1); d <= dateRange.second; d = d.addDays(1))
        {
            if (d.dayOfWeek() == 1)
            {
                if (dateRange.first.daysTo(d) >= factor)
                {
                    if (d.daysTo(dateRange.second) >= factor)
                    {
                        vec->push_back(d);
                    }
                }
            }
        }
        vec->push_back(dateRange.second);
    }
    else
    {
        vec->push_back(dateRange.first);
        for (QDate d = dateRange.first.addDays(1); d <= dateRange.second; d = d.addDays(1))
        {
            if (d.day() == 1)
            {
                if (dateRange.first.daysTo(d) >= factor)
                {
                    if (d.daysTo(dateRange.second) >= factor)
                    {
                        vec->push_back(d);
                    }
                }
            }
        }
        vec->push_back(dateRange.second);
    }

    return vec;
}