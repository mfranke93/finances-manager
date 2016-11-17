//
// Created by max on 06/10/16.
//


#pragma once


#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QPushButton>
#include <ui/plotting/PlotCategoryFilter.h>
#include "ui/plotting/PlotArea.h"

class PlotTab : public QWidget
{
    Q_OBJECT

public:
    PlotTab(QWidget * parent);

protected slots:
    void onDataChanged();

private:
    void rebuildCategories();

    QScrollArea * plotAreaWrapper;
    PlotArea * plotArea;

    QPushButton * repaintButton;
    QPushButton * zoomInButton;
    QPushButton * zoomOutButton;
    QPushButton * enableMinMaxDrawingButton;

    PlotCategoryFilter * sideButtons;

    QVBoxLayout * mainLayout;
    QHBoxLayout * allLayout;
    QHBoxLayout * bottomButtonLayout;
};


