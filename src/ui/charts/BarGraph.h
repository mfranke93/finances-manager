//
// Created by max on 10/10/16.
//


#pragma once


#include <QtGui/QPainter>
#include <functional>
#include <QtGui/QPaintEvent>

typedef std::function<int(double const&)> PriceScaler;

class BarGraph
{
public:
    bool valid() { return bool(scale);}
    BarGraph();
    ~BarGraph() = default;

    BarGraph(BarGraph const&) = default;
    BarGraph& operator= (BarGraph const&) = delete;

    void paint(QPainter * const) const;

    void setPriceScaler(PriceScaler);

    void setRange(double const&, double const&);

    void setColors(QColor const&, QColor const&);

    void setBoundingRect(QRect const&);

    QRect& boundingRect() { return this->boundingRectangle; };

    inline std::pair<double, double> const& getRange() const
    {
        return range;
    };

private:
    PriceScaler scale;
    std::pair<double, double> range;
    QRect boundingRectangle;
    QColor colorPositive, colorNegative;
};


