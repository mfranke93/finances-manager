//
// Created by max on 08/10/16.
//


#pragma once

#include "ui/plotting/graphics/CumulativePlotLine.h"
#include "ui/plotting/graphics/Plottable.h"

class PlotBottomBar : public Plottable
{
public:
    PlotBottomBar(int const& bottomMargin,
                  int const& leftMargin,
                  int const& offset,
                  std::pair<QDate const, QDate const> dateRange,
                  std::shared_ptr<DateToIntConverter> const& dti);
    PlotBottomBar() = delete;
    ~PlotBottomBar() = default;
    PlotBottomBar(PlotBottomBar const&) = delete;
    PlotBottomBar& operator= (PlotBottomBar const&) = delete;

    void plot(QPainter * const) const override;

    QRect const& boundingRect() const override { return boundingRect_; };

protected:
    std::vector<QDate> * calculatePrintedDates(QPainter * const) const;
private:
    int const bottomMargin;
    int const leftMargin;
    /**
     * offset from top of painting area
     */
    int const offset;
    std::pair<QDate const, QDate const> dateRange;

    std::shared_ptr<DateToIntConverter> dtiConverter;


    QRect boundingRect_;
};


