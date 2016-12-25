//
// Created by max on 09/10/16.
//


#pragma once


#include "ui/plotting/graphics/Plottable.h"
#include "ui/plotting/graphics/PlotLine.h"

class PlotGrid : public Plottable
{
public:
    PlotGrid() = delete;
    ~PlotGrid() = default;
    PlotGrid(std::pair<QDate const, QDate const> const& dateRange,
             std::pair<double const, double const> const& priceRange,
             DateToIntConverter const& dti,
             VerticalScaler const& vs);

    void plot(QPainter * const) const override;

    QRect const& boundingRect() const override { return boundingRect_; };
private:

    std::pair<QDate const, QDate const> const dateRange;
    std::pair<double const, double const> const priceRange;
    DateToIntConverter dtiConverter;
    VerticalScaler vScaler;

    QRect const boundingRect_;
};


