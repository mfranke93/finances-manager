//
// Created by max on 10/10/16.
//

#include "GraphArea.h"

GraphArea::GraphArea()
: range(0,0)
{
    // ctor
    setMouseTracking(true);
}

void
GraphArea::paintEvent(QPaintEvent * /*evt*/)
{
    QPainter painter (this);

    painter.fillRect(this->rect(), QColor("white"));

    // draw grid and numbers
    QColor red = ResourceHandler::getInstance()->getColor("negative numbers red");
    QColor black = ResourceHandler::getInstance()->getColor("positive numbers blue");
    QColor gray = ResourceHandler::getInstance()->getColor("plot grid grey");
    painter.setFont(QFont("Monospace", 8));
    for (double d = 200*(std::ceil(range.first/200)); d <= range.second; d += 200)
    {
        int const y = scale(d) + yOffset;
        painter.setPen(gray);
        painter.drawLine(xOffsetGlobal, y, width(), y);

        // numbers
        painter.setPen(d<0.0?red:black);
        char buf [10];
        std::sprintf(buf, "%4.0f", d);
        painter.drawText(10, y+5, QString(buf));
    }

    // draw bars
    for (auto& it : bars)
    {
        it.second.paint(&painter);
        painter.setPen(black);
        QFont f ("Monospace", 8);
        painter.setFont(f);
        painter.rotate(-90);
        painter.drawText(
                //it.second.boundingRect().x() -5,
                //it.second.boundingRect().bottom() + 15,
                -it.second.boundingRect().bottom() - 80,
                it.second.boundingRect().x() + 27,
                it.first);
        painter.rotate(90);
    }
}

void
GraphArea::resizeEvent(QResizeEvent * evt)
{
    QWidget::resizeEvent(evt);
    rebuildBars();
}

void
GraphArea::rebuildBars()
{
    // rebuild bounding rects
    int const numBars = int(bars.size());
    widthPerBar = (width() - xOffsetGlobal)/numBars;
    if (widthPerBar > 120) widthPerBar = 120;
    heightPerBar = height() - 100;
    int const xOffset = 20;
    yOffset = 20;

    scale = [&](double const& d) -> int
    {
        double const scalingFactor = (d - range.first)/(range.second-range.first);
        return int(heightPerBar - scalingFactor * heightPerBar);
    };

    int currentX = xOffsetGlobal;
    size_t count = 0;
    for (auto& it : bars)
    {
        it.second.setPriceScaler(scale);
        it.second.setBoundingRect(QRect(currentX+xOffset/2, yOffset, widthPerBar - xOffset, heightPerBar));

        currentX += widthPerBar;

        // colors
        std::pair<QColor, QColor> const colors = ResourceHandler::getInstance()->getRainbowColor(count++, numBars);
        QColor const positive = colors.first;
        QColor const negative = colors.second;
        it.second.setColors(positive, negative);
    }
}

void
GraphArea::addBar(QString const& name, double const& min, double const& max)
{
    BarGraph graph;
    graph.setPriceScaler(scale);
    graph.setBoundingRect(QRect(0, 0, 50, 200));

    graph.setRange(min, max);
    if (min < range.first) range.first = min;
    if (max > range.second) range.second = max;

    bars.push_back(std::make_pair(name, graph));

    rebuildBars();
}

void
GraphArea::reloadEvent()
{
    rebuildBars();
}

void
GraphArea::mouseMoveEvent(QMouseEvent * evt)
{
    auto pair = getBarAt(evt->pos().x());

    QString str;
    str += pair.first;
    str += "\n";

    double const min = pair.second.getRange().first;
    double const max = pair.second.getRange().second;

    char buf [32];
    std::sprintf(buf, "+%.2f\n-%.2f", max, std::abs(min));
    str += buf;

    setToolTip(str);
}

std::pair<QString, BarGraph> const&
GraphArea::getBarAt(int const& posX) const
{
    // save width per bar to instance
    const int withoutOffset = posX - xOffsetGlobal;
    const int index = withoutOffset / widthPerBar;
    return bars.at(index);
}
