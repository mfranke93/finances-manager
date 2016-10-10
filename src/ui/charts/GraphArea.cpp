//
// Created by max on 10/10/16.
//

#include <iostream>
#include "GraphArea.h"

GraphArea::GraphArea()
: range(0,0)
{
    // ctor
}

void
GraphArea::paintEvent(QPaintEvent * evt)
{
    QPainter painter (this);

    painter.fillRect(this->rect(), QColor("white"));

    painter.setPen(QColor(180,180,180));
    for (double d = 200*(ceil(range.first/200)); d <= range.second; d += 200)
    {
        int const y = scale(d) + yOffset;
        painter.drawLine(0, y, width(), y);
    }

    for (auto& it : bars)
    {
        it.second.paint(&painter);
        painter.setPen(QColor("black"));
        QFont f ("Monospace", 8);
        painter.setFont(f);
        painter.drawText(it.second.boundingRect().x() -5, it.second.boundingRect().bottom() + 15, it.first);
    }
}

void
GraphArea::resizeEvent(QResizeEvent * evt)
{
    QWidget::resizeEvent(evt);
    emit rebuildBars();
}

void
GraphArea::rebuildBars()
{
    // rebuild bounding rects
    int const numBars = int(bars.size());
    int widthPerBar = width()/numBars;
    if (widthPerBar > 120) widthPerBar = 120;
    heightPerBar = height() - 60;
    int const xOffset = 20;
    yOffset = 20;

    scale = [&](double const& d) -> int
    {
        double const scalingFactor = (d - range.first)/(range.second-range.first);
        return int(heightPerBar - scalingFactor * heightPerBar);
    };

    int currentX = 0;
    for (auto& it : bars)
    {
        it.second.setPriceScaler(scale);
        it.second.setBoundingRect(QRect(currentX+xOffset/2, yOffset, widthPerBar - xOffset, heightPerBar));

        currentX += widthPerBar;
    }
}

void
GraphArea::addBar(QString const& name, double const& min, double const& max)
{
    BarGraph graph;
    graph.setPriceScaler(scale);
    graph.setBoundingRect(QRect(0, 0, 50, 200));
    graph.setColors(QColor(120, 120, 240), QColor(240, 120, 120));
    graph.setRange(min, max);
    if (min < range.first) range.first = min;
    if (max > range.second) range.second = max;

    bars.push_back(std::make_pair(name, graph));

    emit rebuildBars();
}