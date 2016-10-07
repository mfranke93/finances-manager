//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHBoxLayout>
#include <data/DbHandler.h>
#include "MainWindow.h"
#include "AddItemDialog.h"
#include "TableTab.h"
#include "PlotTab.h"

MainWindow::MainWindow()
{
    setLayout(new QVBoxLayout);
    tabs = new QTabWidget;
    layout()->addWidget(tabs);

    tabs->addTab(new TableTab(this), "Table");
    tabs->addTab(new PlotTab(this), "Plot");
}

MainWindow::~MainWindow()
{
    // dtor
}

