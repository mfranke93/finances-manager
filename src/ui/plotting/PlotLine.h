//
// Created by max on 08/10/16.
//


#pragma once

#include "Plottable.h"
#include "PlotPoint.h"
#include <QtCore/QDate>
#include <functional>

typedef std::function<int(QDate const&)> DateToIntConverter;
typedef std::function<int(double const&)> VerticalScaler;

class PlotLine : public Plottable
{
public:
    PlotLine();
    ~PlotLine();

    PlotLine(PlotLine const&) = default;
    PlotLine& operator= (PlotLine const&) = delete;

    void plot(QPainter * const) const override;
    void addPoint(QDate const& date, double const& value);
    void setDtiConverter(DateToIntConverter const&);
    void setVerticalScaler(VerticalScaler const&);

protected:
    std::vector<PlotPoint> * buildPoints() const;

private:
    std::vector<std::pair<QDate const, double>> points;
    DateToIntConverter dtiConverter;
    VerticalScaler vScaler;

};


