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

signals:
    void canDecrementZoomLevel(bool);
    void canIncrementZoomLevel(bool);

protected:
    void checkZoomLevel();

private:
    std::vector<std::pair<QDate, double>> cumulativeSums;
    const int marginBottom = 20;
    const int marginTop = 5;
    const int marginRight = 5;
    const int marginLeft = 60;

    inline int const& dayWidth() const { return zoomLevels[zoomLevel]; }
    int zoomLevel;
    static constexpr int maxZoomLevel = 10;
    static const int zoomLevels [maxZoomLevel+1];
};


