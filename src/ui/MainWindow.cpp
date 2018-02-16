//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHBoxLayout>
#include <data/DbHandler.h>
#include <ui/tabs/ChartTab.h>
#include "MainWindow.h"
#include "ui/dialogs/AddItemDialog.h"
#include "ui/tabs/TableTab.h"
#include "ui/tabs/PlotTab.h"
#include "ui/tabs/QtChartTab.h"
#include <QtWidgets/QMenuBar>
#include <ui/menubar/MenuBar.h>

MainWindow::MainWindow()
{
    setLayout(new QVBoxLayout);
    menuBar = new MenuBar;
    layout()->setMenuBar(menuBar);
    tabs = new QTabWidget;
    layout()->addWidget(tabs);

    tabs->addTab(new TableTab(this), "&Table");
    tabs->addTab(new PlotTab(this), "&Plot");
    tabs->addTab(new ChartTab, "&Chart");

    tabs->addTab(new QtChartTab, "&QtCharts");
}

MainWindow::~MainWindow()
{
    // dtor
}

