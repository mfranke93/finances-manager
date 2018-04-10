//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHBoxLayout>
#include <data/DbHandler.h>
#include "MainWindow.h"
#include "ui/dialogs/AddItemDialog.h"
#include "ui/tabs/TableTab.h"
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
    tabs->addTab(new QtChartTab, "&QtCharts");
}

MainWindow::~MainWindow()
{
    // dtor
}

