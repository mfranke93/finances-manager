#include <QtWidgets>
#include <QtCharts>

#pragma once

class ChartArea : public QChart
{
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:
    // TODO: This does not compile as std::optional. Why?
    bool isValid = false;
    qreal pressScenePos;
};
