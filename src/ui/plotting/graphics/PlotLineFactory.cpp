//
// Created by max on 25/12/16.
//

#include "PlotLineFactory.h"

std::shared_ptr<PlotElement>
PlotLineFactory::buildPlotElementFromData(QSqlQuery& resultsQuery, int const& pixelsPerDay, int const& height,
                                          int const& leftMargin, int const& topMargin,
                                          std::pair<QDate, QDate> const& dateRange, PlotType const& plotType) const
{
    switch (plotType)
    {
        case PlotType::CUMULATIVE:
        case PlotType::CUMULATIVE_WITH_MINMAX:
        {
            std::shared_ptr<CumulativePlotLine> pl = buildCumulativePlotLine(resultsQuery, pixelsPerDay, height, leftMargin, topMargin, dateRange);
            pl->setDrawMinMax(plotType == PlotType::CUMULATIVE_WITH_MINMAX);
            return pl;
        }
        case PlotType::DAILY_PEAKS:
        {
            return buildDailyPeaksPlotLine(resultsQuery, pixelsPerDay, height, leftMargin, topMargin, dateRange);
        }
        default:
        {
            throw std::invalid_argument("o");
        }
    }
}

std::shared_ptr<CumulativePlotLine>
PlotLineFactory::buildCumulativePlotLine(QSqlQuery& resultsQuery, int const& pixelsPerDay, int const& height,
                                         int const& leftMargin, int const& topMargin, std::pair<QDate,QDate> const& dateRange) const
{
    std::vector<std::pair<QDate const, std::tuple<double, double, double>>> cumulativeSums;
    std::map<QDate, std::tuple<double, double, double>> accumPerDay;

    while (resultsQuery.next())
    {
        QDate d = resultsQuery.value("date").toDate();
        double price = resultsQuery.value("price").toDouble();

        if (accumPerDay.find(d) == accumPerDay.end())
        {
            double min = price<0?price:0.0;
            double max = price<0?0.0:price;
            accumPerDay[d] = std::make_tuple(price, min, max);
        }
        else
        {
            std::get<0>(accumPerDay[d]) += price;
            if (price >= 0.0)
            {
                std::get<2>(accumPerDay[d]) += price;
            }
            else
            {
                std::get<1>(accumPerDay[d]) += price;
            }
        }
    }
    // find minimum and maximum
    QDate first, last;
    first = dateRange.first;
    last = dateRange.second;
    for (auto it : accumPerDay)
    {
        if (it.first > last) last = it.first;
        if (it.first < first) first = it.first;
    }

    double sum = 0.0;
    for (QDate d = first; d <= last; d = d.addDays(1))
    {
        double min = sum;
        double max = sum;
        if (accumPerDay.find(d) != accumPerDay.end())
        {
            // minimum of day: before all positive
            min += std::get<1>(accumPerDay[d]);
            // maximum per day: before all negative
            max += std::get<2>(accumPerDay[d]);
            sum += std::get<0>(accumPerDay[d]);
        }
        cumulativeSums.push_back(std::make_pair(d, std::make_tuple(sum, min, max)));
    }

    std::shared_ptr<CumulativePlotLine> pl = std::make_shared<CumulativePlotLine>(cumulativeSums, pixelsPerDay, height, leftMargin, topMargin);

    return pl;
}

std::shared_ptr<DailyChangesPlotLine>
PlotLineFactory::buildDailyPeaksPlotLine(QSqlQuery& resultsQuery, int const& pixelsPerDay, int const& height,
                                         int const& leftMargin, int const& topMargin,
                                         std::pair<QDate, QDate> const& dateRange) const
{
    std::map<QDate, std::pair<double, double>> accumPerDay;
    std::vector<std::pair<QDate const, std::pair<double, double>>> peaksPerDay;

    while (resultsQuery.next())
    {
        QDate d = resultsQuery.value("date").toDate();
        double price = resultsQuery.value("price").toDouble();

        if (accumPerDay.find(d) == accumPerDay.end())
        {
            double min = price<0?price:0.0;
            double max = price<0?0.0:price;
            accumPerDay[d] = std::make_pair(min, max);
        }
        else
        {
            if (price >= 0.0)
            {
                std::get<1>(accumPerDay[d]) += price;
            }
            else
            {
                std::get<0>(accumPerDay[d]) += price;
            }
        }
    }
    // find minimum and maximum
    QDate first, last;
    first = dateRange.first;
    last = dateRange.second;
    for (auto it : accumPerDay)
    {
        if (it.first > last) last = it.first;
        if (it.first < first) first = it.first;
    }

    for (QDate d = first; d <= last; d = d.addDays(1))
    {
        double min = 0.0;
        double max = 0.0;
        if (accumPerDay.find(d) != accumPerDay.end())
        {
            // minimum of day: before all positive
            min = std::get<0>(accumPerDay[d]);
            // maximum per day: before all negative
            max = std::get<1>(accumPerDay[d]);
        }
        peaksPerDay.push_back(std::make_pair(d, std::make_pair(min, max)));
    }

    std::shared_ptr<DailyChangesPlotLine> pl = std::make_shared<DailyChangesPlotLine>(
            peaksPerDay, pixelsPerDay, height, leftMargin, topMargin
    );

    return pl;
}
