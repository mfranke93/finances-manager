//
// Created by max on 07/10/16.
//

#include "PlotArea.h"
#include "PlotLine.h"
#include "PlotBottomBar.h"
#include "PlotLeftAxis.h"
#include "PlotGrid.h"

int const PlotArea::zoomLevels [] = { 5, 8, 12, 20, 32, 50, 64, 80, 100 };

PlotArea::PlotArea(QWidget * parent)
: QWidget(parent),
  zoomLevel(5)
{
    setMouseTracking(true);
}

void
PlotArea::paintEvent(QPaintEvent * evt)
{
    QPainter painter (this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    painter.fillRect(this->rect().adjusted(marginLeft,marginTop,-marginRight-1,-marginBottom-1), QColor(255,255,255));

    if (cumulativeSums.empty()) return;
    // scaling factors
    double minimum = std::get<0>(cumulativeSums[0].second);
    double maximum = minimum;
    int height = this->size().height() - marginBottom - marginTop;
    for (auto it : cumulativeSums)
    {
        double min = std::get<1>(it.second);
        double max = std::get<2>(it.second);

        if (min < minimum) minimum = min;
        if (max > maximum) maximum = max;
    }

    // pad margins
    maximum += 20.0;
    minimum -= 20.0;

    // scaling function
    auto scale = [&](double const& d) -> int { return int(marginTop + height - (d-minimum)/(maximum-minimum)*height); };
    auto dtiConverter = [&](QDate const& d) -> int
    {
        return int(cumulativeSums[0].first.daysTo(d)) * dayWidth() + marginLeft;
    };

    // draw grid
    PlotGrid pg (std::make_pair(cumulativeSums.begin()->first, cumulativeSums.back().first), std::make_pair(minimum, maximum));
    pg.setDateToIntConverter(dtiConverter);
    pg.setVerticalScaler(scale);
    pg.plot(&painter);

    // draw y axis labeling: every 200 €
    PlotLeftAxis la (marginLeft, marginTop, height, std::make_pair(minimum, maximum));
    la.setVerticalScaler(scale);
    la.plot(&painter);

    // draw x axis labeling: first, last, first of each month
    PlotBottomBar b (marginBottom, marginLeft, this->height(), std::make_pair(cumulativeSums.begin()->first, cumulativeSums.back().first));
    b.setDtiConverter(dtiConverter);
    b.plot(&painter);

    // plot
    PlotLine p;
    p.setDtiConverter(dtiConverter);
    p.setVerticalScaler(scale);
    p.setDrawMinMax(paintMinMax);
    p.addPoints(cumulativeSums);
    p.plot(&painter);
}

void
PlotArea::reloadData()
{
    // TODO: externalize
    cumulativeSums.clear();

    std::map<QDate, std::tuple<double, double, double>> accumPerDay;

    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec("SELECT date, price FROM Item ORDER BY date ASC;");
    while (query.next())
    {
        QDate d = query.value("date").toDate();
        double price = query.value("price").toDouble();

        if (accumPerDay.find(d) == accumPerDay.end())
        {
            double min = price<0?price:0.0;
            double max = price<0?0.0:price;
            accumPerDay[d] = std::make_tuple(price, min, max);
        }
        else
        {
            std::get<0>(accumPerDay[d]) += price;
            if (price >= 0.0)
            {
                std::get<2>(accumPerDay[d]) += price;
            }
            else
            {
                std::get<1>(accumPerDay[d]) += price;
            }
        }
    }
    // find minimum and maximum
    QDate first, last;
    first = accumPerDay.begin()->first;
    last = first;
    for (auto it : accumPerDay)
    {
        if (it.first > last) last = it.first;
        if (it.first < first) first = it.first;
    }
    QDate today = QDate::currentDate();
    if (today > last) last = today;

    double sum = 0.0;
    for (QDate d = first; d <= last; d = d.addDays(1))
    {
        double min = sum;
        double max = sum;
        if (accumPerDay.find(d) != accumPerDay.end())
        {
            // minimum of day: before all positive
            min += std::get<1>(accumPerDay[d]);
            // maximum per day: before all negative
            max += std::get<2>(accumPerDay[d]);
            sum += std::get<0>(accumPerDay[d]);
        }
        cumulativeSums.push_back(std::make_pair(d, std::make_tuple(sum, min, max)));
    }

    // iterate over dates

    checkZoomLevel();
    emit repaint();
}

void
PlotArea::incrementZoomLevel()
{
    if (zoomLevel < maxZoomLevel) ++zoomLevel;
    checkZoomLevel();
    emit repaint();
}

void
PlotArea::decrementZoomLevel()
{
    if (zoomLevel > 0) --zoomLevel;
    checkZoomLevel();
    emit repaint();
}

void
PlotArea::checkZoomLevel()
{
    emit canIncrementZoomLevel(zoomLevel<maxZoomLevel);
    emit canDecrementZoomLevel(zoomLevel>0);
    setMinimumWidth(dayWidth() * int(cumulativeSums.size()-1) + marginLeft + marginRight + 5);
}

void
PlotArea::mouseMoveEvent(QMouseEvent * evt)
{
    char buf [20];
    sprintf(buf, "Hello @ %d, %d", evt->pos().x(), evt->pos().y());
    setToolTip(buf);
}