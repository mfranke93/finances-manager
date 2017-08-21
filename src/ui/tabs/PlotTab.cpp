//
// Created by max on 06/10/16.
//

#include <QtWidgets/QAbstractSlider>
#include <data/ResourceHandler.h>
#include <ui/plotting/graphics/PlotLineFactory.h>
#include <data/SettingsManager.h>
#include "PlotTab.h"

PlotTab::PlotTab(QWidget * parent)
: QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    allLayout = new QHBoxLayout;
    bottomButtonLayout = new QHBoxLayout;
    sideButtons = new PlotCategoryFilter(this);

    plotAreaWrapper = new QScrollArea;
    plotArea = new PlotArea(plotAreaWrapper, SettingsManager::getInstance()->defaultPlottype());
    plotAreaWrapper->setWidget(plotArea);
    plotAreaWrapper->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    plotAreaWrapper->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    plotAreaWrapper->setWidgetResizable(true);

    zoomInButton = new QPushButton("+");
    zoomOutButton = new QPushButton("-");
    bottomButtonLayout->addWidget(zoomOutButton);
    bottomButtonLayout->addWidget(zoomInButton);

    plotStyleComboBox = new QComboBox();
    {
        plotStyleComboBox->addItem("Cumulative");
        plotStyleComboBox->addItem("Cumulative with min/max");
        plotStyleComboBox->addItem("Peaks");
    }
    /* cumulative with min/max selected */
    plotStyleComboBox->setCurrentIndex(static_cast<int>(SettingsManager::getInstance()->defaultPlottype()));
    bottomButtonLayout->addStretch(1);
    bottomButtonLayout->addWidget(plotStyleComboBox);

    repaintButton = new QPushButton("Repaint");
    bottomButtonLayout->addStretch(3);
    bottomButtonLayout->addWidget(repaintButton);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addItem(bottomButtonLayout);
    mainLayout->addWidget(plotAreaWrapper);
    auto p = DbHandler::getInstance()->getDateRange();
    dateFilterPane = new DateFilterPane(nullptr, p.first, p.second);

    bottomLayout->addSpacing(30);
    bottomLayout->addWidget(dateFilterPane);

    mainLayout->addItem(bottomLayout);
    allLayout->addItem(mainLayout);
    allLayout->addWidget(sideButtons);

    setLayout(allLayout);

    connect(repaintButton, SIGNAL(clicked()), this, SLOT(onDataChanged()));

    connect(zoomInButton, SIGNAL(clicked()), plotArea, SLOT(incrementZoomLevel()));
    connect(zoomOutButton, SIGNAL(clicked()), plotArea, SLOT(decrementZoomLevel()));
    connect(plotArea, SIGNAL(canIncrementZoomLevel(bool)), zoomInButton, SLOT(setEnabled(bool)));
    connect(plotArea, SIGNAL(canDecrementZoomLevel(bool)), zoomOutButton, SLOT(setEnabled(bool)));
    connect(plotStyleComboBox, SIGNAL(currentIndexChanged(int)), plotArea, SLOT(setPlotStyle(int)));

    connect(DbHandler::getInstance(), SIGNAL(dateRangeChanged(std::pair<QDate, QDate>)),
            dateFilterPane, SLOT(onDateRangeChanged(std::pair<QDate, QDate>)));
    connect(dateFilterPane, SIGNAL(dateRangeChanged()), this, SLOT(onDataChanged()));

    connect(plotArea, SIGNAL(repaintFinished()), this, SLOT(onRepaintFinished()));

    rebuildCategories();
    dateFilterPane->onClickReset();
    onDataChanged();
}

void
PlotTab::rebuildCategories()
{
    sideButtons->clearFilters();

    size_t const range = []() -> size_t
    {
        QSqlQuery query (DbHandler::getInstance()->getDatabase());
        query.exec("SELECT COUNT(name) AS count FROM Category;");
        if (query.next())
        {
            return query.value("count").toInt();
        }
        else
        {
            throw 1;
        }
    }();

    QSqlQuery query (DbHandler::getInstance()->getDatabase());
    query.exec("SELECT name FROM Category ORDER BY name ASC;");
    size_t index = 0;
    while (query.next())
    {
        std::pair<QColor, QColor> const pair = ResourceHandler::getInstance()->getRainbowColor(index++, range);
        QColor const c = pair.first;
        QString const name = query.value("name").toString();
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
}

void
PlotTab::onRepaintFinished()
{
    plotAreaWrapper->horizontalScrollBar()->setValue(plotAreaWrapper->horizontalScrollBar()->maximum());
}
