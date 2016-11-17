//
// Created by max on 06/10/16.
//

#include <QtWidgets/QAbstractSlider>
#include <data/ResourceHandler.h>
#include "PlotTab.h"

PlotTab::PlotTab(QWidget * parent)
: QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    allLayout = new QHBoxLayout;
    bottomButtonLayout = new QHBoxLayout;
    sideButtons = new PlotCategoryFilter(this);

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
    auto p = DbHandler::getInstance()->getDateRange();
    dateFilterPane = new DateFilterPane(nullptr, p.first, p.second);
    mainLayout->addWidget(dateFilterPane);

    allLayout->addItem(mainLayout);
    allLayout->addWidget(sideButtons);

    setLayout(allLayout);

    connect(repaintButton, SIGNAL(clicked()), this, SLOT(onDataChanged()));

    connect(zoomInButton, SIGNAL(clicked()), plotArea, SLOT(incrementZoomLevel()));
    connect(zoomOutButton, SIGNAL(clicked()), plotArea, SLOT(decrementZoomLevel()));
    connect(plotArea, SIGNAL(canIncrementZoomLevel(bool)), zoomInButton, SLOT(setEnabled(bool)));
    connect(plotArea, SIGNAL(canDecrementZoomLevel(bool)), zoomOutButton, SLOT(setEnabled(bool)));
    connect(enableMinMaxDrawingButton, SIGNAL(toggled(bool)), plotArea, SLOT(setPaintMinMax(bool)));

    rebuildCategories();
    dateFilterPane->onClickReset();
    onDataChanged();
}

void
PlotTab::rebuildCategories()
{
    sideButtons->clearFilters();

    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec("SELECT name FROM Category ORDER BY name ASC;");
    size_t counter = 1;
    char buf[15];
    while (query.next())
    {
        QString name = query.value("name").toString();
        std::sprintf(buf, "color%02lu.dark", counter++);
        QColor c = ResourceHandler::getInstance()->getColor(QString(buf));

        sideButtons->addFilter(name, c);
    }
}

void
PlotTab::onDataChanged()
{
    dateFilterPane->setValidRange(DbHandler::getInstance()->getDateRange());
    plotArea->setDateRangeFilters(dateFilterPane->getRange());
    plotArea->setCategoryFilters(sideButtons->getSelected());
    plotArea->reloadData();
    plotAreaWrapper->horizontalScrollBar()->setValue(plotAreaWrapper->horizontalScrollBar()->maximum());
}