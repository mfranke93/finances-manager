//
// Created by max on 08/10/16.
//


#pragma once

#include "Plottable.h"
#include "PlotPoint.h"
#include "PlotElement.h"
#include <QtCore/QDate>
#include <data/ResourceHandler.h>
#include <functional>
#include <memory>

class CumulativePlotLine : public PlotElement
{
public:
    CumulativePlotLine() = delete;
    CumulativePlotLine(std::vector<std::pair<QDate const, std::tuple<double, double, double>>> const& vec,
             int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin);
    ~CumulativePlotLine();

    CumulativePlotLine(CumulativePlotLine const&) = default;
    CumulativePlotLine& operator= (CumulativePlotLine const&) = delete;

    void plot(QPainter * const) const override;
    inline void setDrawMinMax(bool const& b) { drawMinMax = b; };

    QRect const& boundingRect() const override { return boundingRect_; };
    std::pair<QDate, QDate> const& xRange() const override { return xRange_; };
    std::pair<double, double> const& yRange() const override { return yRange_; };
    std::shared_ptr<DateToIntConverter> dtiConverter() const override { return dtiConverter_; };
    std::shared_ptr<VerticalScaler> verticalScaler() const override { return vScaler_; };

protected:
    std::vector<PlotPoint> * buildPoints(int const&, int const&, int const&, int const&);

private:
    std::vector<std::pair<QDate const, std::tuple<double,double,double>>> points;
    std::vector<PlotPoint> * plotPoints_;
    std::shared_ptr<DateToIntConverter> dtiConverter_;
    std::shared_ptr<VerticalScaler> vScaler_;
    bool drawMinMax;

    mutable std::pair<QDate, QDate> xRange_;
    mutable std::pair<double, double> yRange_;
    mutable QRect boundingRect_;
};


