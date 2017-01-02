//
// Created by max on 28/12/16.
//

#pragma once


#include <QtCore/QRect>
#include "Plottable.h"

class PlotBar : public Plottable
{
public:
    PlotBar() = delete;
    PlotBar(QRect const&, QColor const&, QColor const&);
    ~PlotBar() = default;

    void plot(QPainter * const) const override;

    QRect const& boundingRect() const override { return area_; };
private:
    QRect  const area_;
    QColor const frameColor_;
    QColor const areaColor_;
};



