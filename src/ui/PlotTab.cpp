//
// Created by max on 06/10/16.
//

#include "PlotTab.h"

PlotTab::PlotTab(QWidget * parent)
: QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    bottomButtonLayout = new QHBoxLayout;

    plotAreaWrapper = new QScrollArea;
    plotArea = new PlotArea(plotAreaWrapper);
    plotAreaWrapper->setWidget(plotArea);
    plotAreaWrapper->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    plotAreaWrapper->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    plotAreaWrapper->setWidgetResizable(true);

    repaintButton = new QPushButton("Repaint");
    bottomButtonLayout->addStretch(1);
    bottomButtonLayout->addWidget(repaintButton);

    mainLayout->addWidget(plotAreaWrapper);
    mainLayout->addItem(bottomButtonLayout);

    setLayout(mainLayout);

    connect(repaintButton, SIGNAL(clicked()), this, SLOT(onDataChanged()));
}

void
PlotTab::onDataChanged()
{
    plotArea->reloadData();
}