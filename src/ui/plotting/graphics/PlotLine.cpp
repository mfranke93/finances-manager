//
// Created by max on 08/10/16.
//

#include "PlotLine.h"

PlotLine::PlotLine(std::vector<std::pair<QDate const, std::tuple<double, double, double>>> const& vec,
                   DateToIntConverter const& dti, VerticalScaler const& vs)
: points(vec), dtiConverter(dti), vScaler(vs), drawMinMax(true)
{
    // ctor
}

PlotLine::~PlotLine()
{
    // dtor
}

void
PlotLine::plot(QPainter * const painter) const
{
    std::vector<PlotPoint> * vec = buildPoints();

    for (size_t i = 0; i < vec->size()-1; ++i)
    {
        PlotPoint& start = vec->at(i);
        PlotPoint& end = vec->at(i+1);

        // line first
        start.drawLine(painter, end, ResourceHandler::getInstance()->getColor("plot line green"), drawMinMax);
        // then start point
        start.paint(painter);
    }
    // paint last
    vec->back().paint(painter);

    delete vec;
}

std::vector<PlotPoint> *
PlotLine::buildPoints() const
{
    std::vector<PlotPoint> * vec = new std::vector<PlotPoint>;
    int minX, minY, maxX, maxY;
    bool first = true;
    for (auto const& point : points)
    {
        double const val = std::get<0>(point.second);
        double const minimal = std::get<1>(point.second);
        double const maximal = std::get<2>(point.second);

        int const x = dtiConverter(point.first);
        int const y = vScaler(val);
        int const min = vScaler(minimal);
        int const max = vScaler(maximal);

        if (first || min < minY) minY = min;
        if (first || max > maxY) maxY = max;
        if (first || x < minX) minX = x;
        if (first || x > maxX) maxX = x;

        PlotPoint p (x, y, 3,
                     (val>0)
                     ? ResourceHandler::getInstance()->getColor("positive numbers blue")
                     : ResourceHandler::getInstance()->getColor("negative numbers red"));
        p.setYRange(min, max);
        vec->push_back(p);

        first = false;
    }

    boundingRect_.setCoords(minX, minY, maxX, maxY);

    return vec;
}