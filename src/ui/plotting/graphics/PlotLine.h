//
// Created by max on 08/10/16.
//


#pragma once

#include "Plottable.h"
#include "PlotPoint.h"
#include <QtCore/QDate>
#include <data/ResourceHandler.h>
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
    void addPoint(QDate const& date, double const& value, double const& min, double const& max);
    void addPoints(std::vector<std::pair<QDate const, std::tuple<double, double, double>>> const& vec);
    void setDtiConverter(DateToIntConverter const&);
    void setVerticalScaler(VerticalScaler const&);
    inline void setDrawMinMax(bool const& b) { drawMinMax = b; };

    QRect const& boundingRect() const override { return boundingRect_; };

protected:
    std::vector<PlotPoint> * buildPoints() const;

private:
    std::vector<std::pair<QDate const, std::tuple<double,double,double>>> points;
    DateToIntConverter dtiConverter;
    VerticalScaler vScaler;
    bool drawMinMax;

    mutable QRect boundingRect_;
};


