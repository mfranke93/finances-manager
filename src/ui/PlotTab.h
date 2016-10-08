//
// Created by max on 06/10/16.
//


#pragma once


#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QPushButton>
#include "PlotArea.h"

class PlotTab : public QWidget
{
    Q_OBJECT

public:
    PlotTab(QWidget * parent);

protected slots:
    void onDataChanged();

private:
    QScrollArea * plotAreaWrapper;
    PlotArea * plotArea;

    QPushButton * repaintButton;
    QPushButton * zoomInButton;
    QPushButton * zoomOutButton;

    QVBoxLayout * mainLayout;
    QHBoxLayout * bottomButtonLayout;
};


