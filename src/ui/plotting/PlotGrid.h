//
// Created by max on 09/10/16.
//


#pragma once


#include "Plottable.h"
#include "PlotLine.h"

class PlotGrid : public Plottable
{
public:
    PlotGrid() = delete;
    ~PlotGrid() = default;
    PlotGrid(std::pair<QDate const, QDate const> const& dateRange, std::pair<double const, double const> const& priceRange);

    inline void setVerticalScaler(VerticalScaler const& vs) { vScaler = vs; };
    inline void setDateToIntConverter(DateToIntConverter const& dti) { dtiConverter = dti; };

    void plot(QPainter * const) const override;
private:
    VerticalScaler vScaler;
    DateToIntConverter dtiConverter;

    std::pair<QDate const, QDate const> const dateRange;
    std::pair<double const, double const> const priceRange;
};


