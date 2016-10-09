//
// Created by max on 09/10/16.
//


#pragma once


#include "Plottable.h"
#include "PlotLine.h"

class PlotLeftAxis : public Plottable
{
public:
    PlotLeftAxis(int const& leftMargin, int const& topMargin, int const& innerHeight,
                 std::pair<double const, double const> const& range);

    PlotLeftAxis() = delete;

    PlotLeftAxis(PlotLeftAxis const&) = delete;

    PlotLeftAxis& operator=(PlotLeftAxis const&) = delete;

    ~PlotLeftAxis() = default;

    void setVerticalScaler(VerticalScaler const&);

    void plot(QPainter * const) const override;

private:
    VerticalScaler vScaler;
    int const leftMargin;
    int const topMargin;
    int const innerHeight;
    std::pair<double const, double const> const range;
};


