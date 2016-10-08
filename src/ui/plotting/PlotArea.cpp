//
// Created by max on 07/10/16.
//

#include "PlotArea.h"

int const PlotArea::zoomLevels [] = { 1, 2, 5, 8, 12, 20, 32, 50, 64, 80, 100 };

PlotArea::PlotArea(QWidget * parent)
: QWidget(parent),
  zoomLevel(7)
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
    auto scale = [&](double const& d) -> double { return marginTop + height - (d-minimum)/(maximum-minimum)*height; };

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
    painter.setFont(QFont("Monospace", 8));
    painter.setPen(QColor(0,0,0));
    for (double y = Y_LABELS * floor(minimum/Y_LABELS); y <= Y_LABELS * ceil(maximum/Y_LABELS); y += Y_LABELS)
    {
        char buf [10];
        sprintf(buf, "%4.0f €", y);
        QString label (buf);
        painter.drawText(5, int(scale(y))+5, label);
    }

    // draw x axis labeling: first, last, first of each month
    auto datePaint = [&](QDate const& d, int const& offset, bool const& firstOfMonth = false) -> void
    {
        painter.drawText(offset, this->size().height()-5, d.toString(firstOfMonth?"dd.MM.":"dd."));
    };
    for (size_t i = 0; i < cumulativeSums.size(); ++i)
    {
        bool first = cumulativeSums[i].first.day() == 1;
        datePaint(cumulativeSums[i].first, dayWidth() * i + marginLeft - (first?14:5), first);
    }

    // plot
    painter.setPen(QColor(240,30,30));
    painter.setBrush(QColor(50, 0, 255));
    int x = marginLeft;
    int y = int(scale(cumulativeSums[0].second));
    painter.fillRect(x-2, y-2, 4, 4, QColor(50, 0, 255));

    // next
    for (size_t i = 0; i < cumulativeSums.size()-1; ++i)
    {
        int newx = x + dayWidth();
        int newy = int(scale(cumulativeSums[i+1].second));
        painter.drawLine(x, y, newx, newy);
        painter.fillRect(newx-2, newy-2, 4, 4, QColor(50, 0, 255));
        x = newx;
        y = newy;
    }
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