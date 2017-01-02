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
#include <ui/common/DateFilterPane.h>
#include "ui/plotting/PlotArea.h"

class PlotTab : public QWidget
{
    Q_OBJECT

public:
    PlotTab(QWidget * parent);

signals:
    void plotTypeChanged(PlotType);

protected slots:
    void onDataChanged();

private:
    void rebuildCategories();

    QScrollArea * plotAreaWrapper;
    PlotArea * plotArea;

    QPushButton * repaintButton;
    QPushButton * zoomInButton;
    QPushButton * zoomOutButton;
    QComboBox   * plotStyleComboBox;

    PlotCategoryFilter * sideButtons;
    DateFilterPane * dateFilterPane;

    QVBoxLayout * mainLayout;
    QHBoxLayout * allLayout;
    QHBoxLayout * bottomLayout;
    QHBoxLayout * bottomButtonLayout;
};


