//
// Created by max on 25/12/16.
//

#include <data/ResourceHandler.h>
#include "DailyChangesPlotLine.h"

void
DailyChangesPlotLine::plot(QPainter * const painter) const
{
    for (PlotBar const& bar : *plotBars_)
    {
        bar.plot(painter);
    }
}

DailyChangesPlotLine::DailyChangesPlotLine(std::vector<std::pair<QDate const, std::pair<double, double>>> const& values,
                                           int const& pixelsPerDay, int const& height, int const& leftMargin,
                                           int const& topMargin)
: points(values)
{
    // ctor
    plotBars_ = buildBars(pixelsPerDay, height, leftMargin, topMargin);
}

std::vector<PlotBar> *
DailyChangesPlotLine::buildBars(int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin)
{
    std::vector<PlotBar> * bars = new std::vector<PlotBar>;


    double minVal, maxVal;
    bool first = true;

    // get ranges
    for (auto const& point : points)
    {
        double const minimal = std::get<0>(point.second);
        double const maximal = std::get<1>(point.second);
        if (first || minimal < minVal) minVal = minimal;
        if (first || maximal > maxVal) maxVal = maximal;
        first = false;
    }

    xRange_.first = points.front().first;
    xRange_.second = points.back().first;
    yRange_.first = minVal-50.0;
    yRange_.second = maxVal+50.0;

    // scalers
    int const width = static_cast<int>(points.size()) * pixelsPerDay;
    dtiConverter_ = std::make_shared<DateToIntConverter>(xRange_, std::make_pair(leftMargin, width+leftMargin));
    vScaler_ = std::make_shared<VerticalScaler>(yRange_, std::make_pair(height+topMargin, topMargin));  // coords top to bottom

    for (auto const& point : points)
    {
        constexpr double val {0};
        double const minimal = std::get<0>(point.second);
        double const maximal = std::get<1>(point.second);
        int const x = (*dtiConverter_)(point.first);
        int const y =   (*vScaler_)(val);
        int const min = (*vScaler_)(minimal);
        int const max = (*vScaler_)(maximal);

        std::printf("%d %d %d %d\n", x, y, min, max);
        QRect rectPositive (x-2, max, 4, y-max);
        QRect rectNegative (x-2, y, 4, min-y);

        PlotBar barPositive (rectPositive, ResourceHandler::getInstance()->getColor("plot positive line blue"),
            ResourceHandler::getInstance()->getColor("plot positive area blue"));
        PlotBar barNegative (rectNegative, ResourceHandler::getInstance()->getColor("plot negative line red"),
                             ResourceHandler::getInstance()->getColor("plot negative area red"));

        bars->push_back(barPositive);
        bars->push_back(barNegative);
    }

    int const minX = (*dtiConverter_)(xRange_.first);
    int const maxX = (*dtiConverter_)(xRange_.second);
    int const minY = (*vScaler_)(yRange_.first);
    int const maxY = (*vScaler_)(yRange_.second);
    boundingRect_.setCoords(minX, minY, maxX, maxY);

    return bars;
}

