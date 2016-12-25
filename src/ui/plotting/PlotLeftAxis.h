//
// Created by max on 09/10/16.
//


#pragma once


#include "ui/plotting/graphics/Plottable.h"
#include "ui/plotting/graphics/PlotLine.h"

class PlotLeftAxis : public Plottable
{
public:
    PlotLeftAxis(int const& leftMargin, int const& topMargin, int const& innerHeight,
                 std::pair<double const, double const> const& range, VerticalScaler const& verticalScaler);

    PlotLeftAxis() = delete;

    PlotLeftAxis(PlotLeftAxis const&) = delete;

    PlotLeftAxis& operator=(PlotLeftAxis const&) = delete;

    ~PlotLeftAxis() = default;

    void plot(QPainter * const) const override;

    QRect const& boundingRect() const override { return boundingRect_; };
private:
    int const leftMargin;
    int const topMargin;
    int const innerHeight;
    std::pair<double const, double const> const range;
    VerticalScaler vScaler;

    QRect boundingRect_;
};


