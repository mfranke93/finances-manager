//
// Created by max on 07/10/16.
//

#include <data/ResourceHandler.h>
#include <ui/plotting/graphics/PlotLineFactory.h>
#include "PlotArea.h"
#include "ui/plotting/graphics/CumulativePlotLine.h"
#include "PlotBottomBar.h"
#include "PlotLeftAxis.h"
#include "PlotGrid.h"

int const PlotArea::zoomLevels [] = { 2, 5, 8, 12, 20, 32 };

PlotArea::PlotArea(QWidget * parent)
: QWidget(parent),
  zoomLevel(3)
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void
PlotArea::paintEvent(QPaintEvent * evt) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));
    painter.fillRect(this->rect().adjusted(marginLeft, marginTop, -marginRight - 1, -marginBottom - 1),
                     QColor(255, 255, 255));

    // scaling factors
    int height = this->size().height() - marginBottom - marginTop;

    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec(buildQuery()); //"SELECT date, price FROM Item ORDER BY date ASC;");
    PlotLineFactory lineFactory;
    std::shared_ptr<PlotElement> p = lineFactory.buildPlotElementFromData(
            query,
            zoomLevels[zoomLevel],
            height, marginLeft, marginTop,
            dateRange,
            PlotType::DAILY_PEAKS
    );
    minimum = p->yRange().first;
    maximum = p->yRange().second;

    // scaling function
    auto scale = p->verticalScaler();
    auto dtiConverter = p->dtiConverter();

    // draw grid
    PlotGrid pg(p->xRange(), p->yRange(), dtiConverter, scale);
    pg.plot(&painter);

    // draw y axis labeling: every 200 €
    PlotLeftAxis la(marginLeft, marginTop, height, std::make_pair(minimum, maximum), scale);
    la.plot(&painter);

    // draw x axis labeling: first, last, first of each month
    PlotBottomBar b(marginBottom, marginLeft, this->height(),
                    p->xRange(),
                    dtiConverter);
    b.plot(&painter);

    // plot
    p->plot(&painter);
}

QString
PlotArea::buildQuery() const
{
    QString query;
    query += "SELECT Item.date as date, Item.price as price ";
    query += "FROM Item ";
    if (filters.size() > 0)
    {
        query += "JOIN Category On Category.id = Item.catid ";
        query += "WHERE Category.name IN (";
        for (size_t i = 0; i < filters.size()-1; ++i)
        {
            query += "'";
            query += filters[i];
            query += "', ";
        }
        query += "'";
        query += filters.back();
        query += "') ";
    }
    {
        // date range
        query += "AND Item.date >= ";
        query += "'";
        query += dateRange.first.toString("yyyy-MM-dd");
        query += "' ";
        query += "AND Item.date <= ";
        query += "'";
        query += dateRange.second.toString("yyyy-MM-dd");
        query += "' ";
    }
    query += "ORDER BY date ASC;";

    return query;
}

void
PlotArea::reloadData()
{
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
    qint64 const days = dateRange.first.daysTo(dateRange.second);
    setMinimumWidth(dayWidth() * int(days-1) + marginLeft + marginRight + 5);
}

void
PlotArea::mouseMoveEvent(QMouseEvent * evt)
{
    double d = getYValue(evt->pos().y());
    QDate date = getXValue(evt->pos().x());
    char buf [50];
    sprintf(buf, "%s, %.2f", date.toString("dd.MM.yyyy").toStdString().c_str(), d);
    setToolTip(buf);
}

double
PlotArea::getYValue(int const& posY) const
{
    const int height = this->size().height();
    const double scale = static_cast<double>(posY)/ static_cast<double>(height);
    // value is highest at top, but the y values get larger further down
    const double actualScale = 1.0 - scale;
    const double val = actualScale * (maximum - minimum);
    return val + minimum;
}

QDate
PlotArea::getXValue(int const& posX) const
{
    const int width = this->size().width();
    const double scale = static_cast<double>(posX)/ static_cast<double>(width);
    const qint64 minDate = dateRange.first.toJulianDay();
    const qint64 maxDate = dateRange.second.toJulianDay();
    const double val = scale * (maxDate - minDate);
    const qint64 actualVal = static_cast<qint64>(val + minDate);
    return QDate::fromJulianDay(actualVal);
}