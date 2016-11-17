//
// Created by max on 16/11/16.
//

#include <QtWidgets/QPushButton>
#include <QtCore/QVariant>
#include "PlotCategoryFilter.h"

PlotCategoryFilter::PlotCategoryFilter(QWidget * parent)
: QWidget(parent)
{
    mainArea = new QScrollArea;
    mainLayout = new QVBoxLayout;
    scrollAreaLayout = new QVBoxLayout;

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    scrollAreaLayout->setSpacing(0);
    scrollAreaLayout->setContentsMargins(0,0,0,0);
    scrollAreaLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
    mainLayout->addWidget(mainArea);
    mainArea->setLayout(scrollAreaLayout);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    setMaximumWidth(100);
}

void
PlotCategoryFilter::clearFilters()
{
    for (auto const& widget : widgets)
    {
        mainArea->layout()->removeWidget(widget);
    }

    widgets.clear();
}

void
PlotCategoryFilter::addFilter(QString const& name, QColor const& color)
{
    QPushButton * button = new QPushButton(name);
    button->setCheckable(true);

    char buf [256];
    std::sprintf(buf, "QPushButton { background-color: rgb(180,180,180); }\nQPushButton:checked { background-color: rgb(%d,%d,%d); }",
        color.red(), color.green(), color.blue()
    );
    button->setStyleSheet(QString(buf));
    //QPalette pal = button->palette();
    //pal.setColor(QPalette::Button, color);
    //button->setAutoFillBackground(true);
    //button->setPalette(pal);
    //button->update();
    button->setChecked(true);

    widgets.push_back(button);
    mainArea->layout()->addWidget(button);
}

std::vector<QString>
PlotCategoryFilter::getSelected() const
{
    std::vector<QString> vec;
    for (QPushButton* const& w : widgets)
    {
        if (w->isChecked())
        {
            vec.push_back(w->text());
        }
    }

    return vec;
}