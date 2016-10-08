//
// Created by max on 08/10/16.
//

#include "PlotLine.h"
#include "PlotPoint.h"

PlotLine::PlotLine()
{
    // ctor
}

PlotLine::~PlotLine()
{
    // dtor
}

void
PlotLine::addPoint(QDate const& date, double const& value)
{
    points.push_back(std::make_pair(date, value));
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
        start.drawLine(painter, end, QColor(20, 205, 100));
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
        vec->push_back(PlotPoint(dtiConverter(point.first), vScaler(point.second), 3, (point.second>0)?QColor(20, 100, 205):QColor(205, 20, 20)));
    }
    return vec;
}