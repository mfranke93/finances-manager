//
// Created by max on 08/10/16.
//

#include "PlotLine.h"

PlotLine::PlotLine()
: drawMinMax(true)
{
    // ctor
}

PlotLine::~PlotLine()
{
    // dtor
}

void
PlotLine::addPoint(QDate const& date, double const& value, double const& min, double const& max)
{
    points.push_back(std::make_pair(date, std::make_tuple(value, min, max)));
}

void
PlotLine::addPoints(std::vector<std::pair<QDate const, std::tuple<double, double, double>>> const& vec)
{
    for (auto it : vec)
    {
        points.push_back(it);
    }
}

void
PlotLine::setDtiConverter(DateToIntConverter const& dtiConverter)
{
    this->dtiConverter = dtiConverter;
}

void
PlotLine::setVerticalScaler(VerticalScaler const& vs)
{
    vScaler = vs;
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
    for (auto const& point : points)
    {
        double val = std::get<0>(point.second);
        double minimal = std::get<1>(point.second);
        double maximal = std::get<2>(point.second);
        PlotPoint p (dtiConverter(point.first), vScaler(val), 3,
                     (val>0)
                     ? ResourceHandler::getInstance()->getColor("positive numbers blue")
                     : ResourceHandler::getInstance()->getColor("negative numbers red"));
        p.setYRange(vScaler(minimal), vScaler(maximal));
        vec->push_back(p);
    }
    return vec;
}