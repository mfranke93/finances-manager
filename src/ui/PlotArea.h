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

#define DAY_WIDTH 50


class PlotArea : public QWidget
{
    Q_OBJECT

public:
    PlotArea(QWidget * parent);
    ~PlotArea() = default;

public slots:
    void reloadData();
    virtual void paintEvent(QPaintEvent * evt) override;


private:
    std::vector<std::pair<QDate, double>> cumulativeSums;
    const int marginBottom = 20;
    const int marginTop = 5;
    const int marginRight = 5;
    const int marginLeft = 60;
};


