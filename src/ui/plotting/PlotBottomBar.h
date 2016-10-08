//
// Created by max on 08/10/16.
//


#pragma once

#include "PlotLine.h"
#include "Plottable.h"

class PlotBottomBar : public Plottable
{
public:
    PlotBottomBar(int const& bottomMargin, int const& leftMargin, int const& offset, std::pair<QDate const, QDate const> dateRange);
    PlotBottomBar() = delete;
    ~PlotBottomBar() = default;
    PlotBottomBar(PlotBottomBar const&) = delete;
    PlotBottomBar& operator= (PlotBottomBar const&) = delete;

    void plot(QPainter * const) const override;
    void setDtiConverter(DateToIntConverter const& dti) { this->dtiConverter = dti; };
private:
    int const bottomMargin;
    int const leftMargin;
    /**
     * offset from top of painting area
     */
    int const offset;

    DateToIntConverter dtiConverter;

    std::pair<QDate const, QDate const> dateRange;
};


