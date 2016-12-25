//
// Created by max on 08/10/16.
//

#include "CumulativePlotLine.h"

CumulativePlotLine::CumulativePlotLine(std::vector<std::pair<QDate const, std::tuple<double, double, double>>> const& vec,
                   int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin)
: points(vec), drawMinMax(true)
{
    // ctor
    plotPoints_ = buildPoints(pixelsPerDay, height, leftMargin, topMargin);
}

CumulativePlotLine::~CumulativePlotLine()
{
    // dtor
    if (plotPoints_ != nullptr) delete plotPoints_;
}

void
CumulativePlotLine::plot(QPainter * const painter) const
{
    for (size_t i = 0; i < plotPoints_->size()-1; ++i)
    {
        PlotPoint& start = plotPoints_->at(i);
        PlotPoint& end = plotPoints_->at(i+1);

        // line first
        start.drawLine(painter, end, ResourceHandler::getInstance()->getColor("plot line green"), drawMinMax);
        // then start point
        start.paint(painter);
    }
    // paint last
    plotPoints_->back().paint(painter);
}

std::vector<PlotPoint> *
CumulativePlotLine::buildPoints(int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin)
{
    std::vector<PlotPoint> * vec = new std::vector<PlotPoint>;
    double minVal, maxVal;
    bool first = true;

    // get ranges
    for (auto const& point : points)
    {
        double const minimal = std::get<1>(point.second);
        double const maximal = std::get<2>(point.second);
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
        double const val = std::get<0>(point.second);
        double const minimal = std::get<1>(point.second);
        double const maximal = std::get<2>(point.second);
        int const x = (*dtiConverter_)(point.first);
        int const y =   (*vScaler_)(val);
        int const min = (*vScaler_)(minimal);
        int const max = (*vScaler_)(maximal);
        PlotPoint p (x, y, 3,
                     (val>0)
                     ? ResourceHandler::getInstance()->getColor("positive numbers blue")
                     : ResourceHandler::getInstance()->getColor("negative numbers red"));
        p.setYRange(min, max);
        vec->push_back(p);
    }

    int const minX = (*dtiConverter_)(xRange_.first);
    int const maxX = (*dtiConverter_)(xRange_.second);
    int const minY = (*vScaler_)(yRange_.first);
    int const maxY = (*vScaler_)(yRange_.second);
    boundingRect_.setCoords(minX, minY, maxX, maxY);

    return vec;
}
