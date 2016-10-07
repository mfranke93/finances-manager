//
// Created by max on 07/10/16.
//

#include "PlotArea.h"

PlotArea::PlotArea(QWidget * parent)
: QWidget(parent)
{
    reloadData();

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
    for (int x = DAY_WIDTH+marginLeft; x < width+marginLeft; x += DAY_WIDTH)
    {
        painter.drawLine(x, marginTop, x, height+marginTop);
    }
    constexpr double Y_LINES = 50;
    constexpr double Y_LABELS = 200;
    for (double y = Y_LINES * floor(minimum/Y_LINES); y <= Y_LINES * ceil(maximum/Y_LINES); y += Y_LINES)
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

    // plot
    painter.setPen(QColor(240,30,30));
    painter.setBrush(QColor(50, 0, 255));
    int x = marginLeft;
    int y = int(scale(cumulativeSums[0].second));
    painter.fillRect(x-2, y-2, 4, 4, QColor(50, 0, 255));

    // next
    for (size_t i = 0; i < cumulativeSums.size()-1; ++i)
    {
        int newx = x + DAY_WIDTH;
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
    cumulativeSums.clear();

    double sum = 0.0;
    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec("SELECT date, price FROM Item ORDER BY date ASC;");
    QDate lastDate;
    bool first = true;
    while (query.next())
    {
        QDate d = query.value("date").toDate();
        if (first)
        {
            first = false;
            lastDate = d;
        }
        double price = query.value("price").toDouble();
        if (lastDate != d)
        {
            cumulativeSums.push_back(std::make_pair(d, sum));
        }
        sum += price;
        lastDate = d;
    }
    cumulativeSums.push_back(std::make_pair(lastDate, sum));

    setMinimumWidth(DAY_WIDTH * (cumulativeSums.size() - 1));
    repaint();
}
