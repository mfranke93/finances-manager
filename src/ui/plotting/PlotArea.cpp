//
// Created by max on 07/10/16.
//

#include "PlotArea.h"
#include "PlotLine.h"
#include "PlotBottomBar.h"
#include "PlotLeftAxis.h"

int const PlotArea::zoomLevels [] = { 5, 8, 12, 20, 32, 50, 64, 80, 100 };

PlotArea::PlotArea(QWidget * parent)
: QWidget(parent),
  zoomLevel(5)
{
    reloadData();
    setMouseTracking(true);

    connect(DbHandler::getInstance(), SIGNAL(itemDataChanged()), this, SLOT(reloadData()));
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
    double minimum = cumulativeSums[0].second;
    double maximum = minimum;
    int height = this->size().height() - marginBottom - marginTop;
    int width = this->size().width() - marginLeft - marginRight;
    for (auto it : cumulativeSums)
    {
        if (it.second < minimum) minimum = it.second;
        if (it.second > maximum) maximum = it.second;
    }

    // pad margins
    maximum += 20.0;
    minimum -= 20.0;

    // scaling function
    auto scale = [&](double const& d) -> int { return int(marginTop + height - (d-minimum)/(maximum-minimum)*height); };

    // draw grid
    painter.setPen(QColor(200, 200, 200));
    for (int x = dayWidth()+marginLeft; x < width+marginLeft; x += dayWidth())
    {
        painter.drawLine(x, marginTop, x, height+marginTop);
    }
    constexpr double Y_LINES = 50;
    constexpr double Y_LABELS = 200;
    for (double y = Y_LINES * ceil(minimum/Y_LINES); y <= Y_LINES * ceil(maximum/Y_LINES); y += Y_LINES)
    {
        if (int(y)%int(Y_LABELS) == 0)
        {
            painter.setPen(QColor(100, 100, 100));
        }
        else
        {
            painter.setPen(QColor(200, 200, 200));
        }
        painter.drawLine(marginLeft, scale(y), marginLeft+width, scale(y));
    }

    // draw y axis labeling: every 200 €
    PlotLeftAxis la (marginLeft, marginTop, height, std::make_pair(minimum, maximum));
    la.setVerticalScaler(scale);
    la.plot(&painter);

    // draw x axis labeling: first, last, first of each month
    auto dtiConverter = [&](QDate const& d) -> int
    {
        return int(d.toJulianDay() - cumulativeSums[0].first.toJulianDay())*dayWidth() + marginLeft;
    };
    PlotBottomBar b (marginBottom, marginLeft, this->height(), std::make_pair(cumulativeSums.begin()->first, cumulativeSums.back().first));
    b.setDtiConverter(dtiConverter);
    b.plot(&painter);

    // plot
    PlotLine p;
    p.setDtiConverter(dtiConverter);
    p.setVerticalScaler(scale);
    for (auto it : cumulativeSums) p.addPoint(it.first, it.second);
    p.plot(&painter);
}

void
PlotArea::reloadData()
{
    // TODO: externalize
    cumulativeSums.clear();

    std::map<QDate, double> accumPerDay;

    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec("SELECT date, price FROM Item ORDER BY date ASC;");
    while (query.next())
    {
        QDate d = query.value("date").toDate();
        double price = query.value("price").toDouble();

        if (accumPerDay.find(d) == accumPerDay.end())
        {
            accumPerDay[d] = price;
        }
        else
        {
            accumPerDay[d] += price;
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
        if (accumPerDay.find(d) != accumPerDay.end())
        {
            sum += accumPerDay[d];
        }
        cumulativeSums.push_back(std::make_pair(d, sum));
    }

    // iterate over dates

    checkZoomLevel();
    repaint();
}

void
PlotArea::incrementZoomLevel()
{
    if (zoomLevel < maxZoomLevel) ++zoomLevel;
    checkZoomLevel();
    repaint();
}

void
PlotArea::decrementZoomLevel()
{
    if (zoomLevel > 0) --zoomLevel;
    checkZoomLevel();
    repaint();
}

void
PlotArea::checkZoomLevel()
{
    emit canIncrementZoomLevel(zoomLevel<maxZoomLevel);
    emit canDecrementZoomLevel(zoomLevel>0);
    setMinimumWidth(dayWidth() * (cumulativeSums.size()-1) + marginLeft + marginRight + 5);
}

void
PlotArea::mouseMoveEvent(QMouseEvent * evt)
{
    char buf [20];
    sprintf(buf, "Hello @ %d, %d", evt->pos().x(), evt->pos().y());
    setToolTip(buf);
}