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

MainWindow::MainWindow()
{
    setLayout(new QVBoxLayout);
    tabs = new QTabWidget;
    layout()->addWidget(tabs);

    tabs->addTab(new TableTab(this), "Table");
    tabs->addTab(new PlotTab(this), "Plot");
    tabs->addTab(new ChartTab, "Chart");
}

MainWindow::~MainWindow()
{
    // dtor
}

