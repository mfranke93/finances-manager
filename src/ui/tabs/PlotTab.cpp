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

    zoomInButton = new QPushButton("+");
    zoomOutButton = new QPushButton("-");
    bottomButtonLayout->addWidget(zoomOutButton);
    bottomButtonLayout->addWidget(zoomInButton);

    enableMinMaxDrawingButton = new QPushButton("Draw min/max");
    enableMinMaxDrawingButton->setCheckable(true);
    enableMinMaxDrawingButton->setChecked(plotArea->isPaintMinMax());
    bottomButtonLayout->addStretch(1);
    bottomButtonLayout->addWidget(enableMinMaxDrawingButton);

    repaintButton = new QPushButton("Repaint");
    bottomButtonLayout->addStretch(3);
    bottomButtonLayout->addWidget(repaintButton);

    mainLayout->addWidget(plotAreaWrapper);
    mainLayout->addItem(bottomButtonLayout);

    setLayout(mainLayout);

    connect(repaintButton, SIGNAL(clicked()), this, SLOT(onDataChanged()));

    connect(zoomInButton, SIGNAL(clicked()), plotArea, SLOT(incrementZoomLevel()));
    connect(zoomOutButton, SIGNAL(clicked()), plotArea, SLOT(decrementZoomLevel()));
    connect(plotArea, SIGNAL(canIncrementZoomLevel(bool)), zoomInButton, SLOT(setEnabled(bool)));
    connect(plotArea, SIGNAL(canDecrementZoomLevel(bool)), zoomOutButton, SLOT(setEnabled(bool)));
    connect(enableMinMaxDrawingButton, SIGNAL(toggled(bool)), plotArea, SLOT(setPaintMinMax(bool)));
}

void
PlotTab::onDataChanged()
{
    plotArea->reloadData();
}