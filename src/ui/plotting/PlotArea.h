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


class PlotArea : public QWidget
{
    Q_OBJECT

public:
    PlotArea(QWidget * parent);
    ~PlotArea() = default;

public slots:
    void reloadData();
    virtual void paintEvent(QPaintEvent * evt) override;
    virtual void mouseMoveEvent(QMouseEvent * evt) override;

    void incrementZoomLevel();
    void decrementZoomLevel();

    inline bool const& isPaintMinMax() { return paintMinMax; };
    inline void setPaintMinMax(bool const& b) { paintMinMax = b; emit repaint(); };

    inline void setCategoryFilters(std::vector<QString> filters)
    {
        this->filters = filters;
    }

    inline void setDateRangeFilters(std::pair<QDate, QDate> dateRange)
    {
        this->dateRange = dateRange;
    }

signals:
    void canDecrementZoomLevel(bool);
    void canIncrementZoomLevel(bool);

protected:
    void checkZoomLevel();

private:
    std::vector<std::pair<QDate const, std::tuple<double, double, double>>> cumulativeSums;
    const int marginBottom = 20;
    const int marginTop = 5;
    const int marginRight = 5;
    const int marginLeft = 60;

    inline int const& dayWidth() const { return zoomLevels[zoomLevel]; }
    QString buildQuery() const;
    int zoomLevel;
    static constexpr int maxZoomLevel = 8;
    static const int zoomLevels [maxZoomLevel+1];

    bool paintMinMax = true;

    std::vector<QString> filters;
    std::pair<QDate, QDate> dateRange;
};


