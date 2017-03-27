//
// Created by max on 07/10/16.
//


#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtCore/QDate>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <data/DbHandler.h>
#include <numeric>
#include <functional>
#include <data/ResourceHandler.h>
#include <ui/plotting/graphics/PlotLineFactory.h>
#include "ui/plotting/graphics/CumulativePlotLine.h"
#include "PlotBottomBar.h"
#include "PlotLeftAxis.h"
#include "PlotGrid.h"

typedef double (* YReverseScaler)(int const&);

class PlotArea : public QWidget
{
    Q_OBJECT

public:
    PlotArea(QWidget * parent, PlotType pType);
    ~PlotArea() = default;

public slots:
    void reloadData();
    virtual void paintEvent(QPaintEvent * evt) override;
    virtual void mouseMoveEvent(QMouseEvent * evt) override;

    void incrementZoomLevel();
    void decrementZoomLevel();

    inline void setCategoryFilters(std::vector<QString> filters)
    {
        this->filters = filters;
    }

    inline void setDateRangeFilters(std::pair<QDate, QDate> dateRange)
    {
        this->dateRange = dateRange;
    }

    void setPlotStyle(int);

signals:
    void canDecrementZoomLevel(bool);
    void canIncrementZoomLevel(bool);
    void repaintFinished();

protected:
    void checkZoomLevel();

private:
    double getYValue(int const&) const;
    QDate getXValue(int const&) const;

    const int marginBottom = 20;
    const int marginTop = 5;
    const int marginRight = 20;
    const int marginLeft = 60;

    inline int const& dayWidth() const { return zoomLevels[zoomLevel]; }
    QString buildQuery() const;
    int zoomLevel;
    static constexpr int maxZoomLevel = 5;
    static const int zoomLevels [maxZoomLevel+1];

    std::vector<QString> filters;
    std::pair<QDate, QDate> dateRange;

    PlotType plotType_;

    double maximum, minimum;

    /**
     * This specifies whether the canvas is painted for the first time.
     * We need this to scroll to the end after painting for the first
     * time.
     */
    bool firstPaintCycle {true};
};


