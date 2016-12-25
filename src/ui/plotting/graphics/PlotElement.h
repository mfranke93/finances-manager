//
// Created by max on 25/12/16.
//

#pragma once

#include <functional>
#include <memory>
#include "Plottable.h"
#include "../../../data/RangeConverter.h"

class PlotElement: public Plottable
{
    virtual std::pair<QDate, QDate> const& xRange() const = 0;
    virtual std::pair<double, double> const& yRange() const = 0;
    virtual std::shared_ptr<DateToIntConverter> dtiConverter() const = 0;
    virtual std::shared_ptr<VerticalScaler> verticalScaler() const = 0;
};

