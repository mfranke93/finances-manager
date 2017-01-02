//
// Created by max on 25/12/16.
//

#pragma once


#include "PlotElement.h"
#include "PlotBar.h"

class DailyChangesPlotLine: public PlotElement
{
    DailyChangesPlotLine() = delete;
    ~DailyChangesPlotLine() = default;
    DailyChangesPlotLine(std::vector<std::pair<QDate const, std::pair<double, double>>> const& values,
                         int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin);

    void plot(QPainter * const) const override;

    QRect const& boundingRect() const override { return boundingRect_; };
    std::pair<QDate, QDate> const& xRange() const override { return xRange_; };
    std::pair<double, double> const& yRange() const override { return yRange_; };
    std::shared_ptr<DateToIntConverter> dtiConverter() const override { return dtiConverter_; };
    std::shared_ptr<VerticalScaler> verticalScaler() const override { return vScaler_; };

protected:
    std::vector<PlotBar> * buildBars(int const& pixelsPerDay, int const& height, int const& leftMargin, int const& topMargin);

private:
    std::vector<std::pair<QDate const, std::pair<double, double>>> points;
    std::vector<PlotBar> * plotBars_;
    std::shared_ptr<DateToIntConverter> dtiConverter_;
    std::shared_ptr<VerticalScaler> vScaler_;

    mutable std::pair<QDate, QDate> xRange_;
    mutable std::pair<double, double> yRange_;
    mutable QRect boundingRect_;
};



