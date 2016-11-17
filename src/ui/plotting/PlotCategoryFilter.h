//
// Created by max on 16/11/16.
//

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>

class PlotCategoryFilter : public QWidget {
public:
    PlotCategoryFilter() = delete;
    PlotCategoryFilter(PlotCategoryFilter const&) = delete;
    PlotCategoryFilter& operator= (PlotCategoryFilter const&) = delete;
    PlotCategoryFilter(QWidget * parent);
    ~PlotCategoryFilter() = default;

    void clearFilters();
    void addFilter(QString const& name, QColor const& color);

    std::vector<QString> getSelected() const;

private:
    QVBoxLayout * mainLayout;
    QScrollArea * mainArea;
    QVBoxLayout * scrollAreaLayout;

    std::vector<QPushButton *> widgets;
};


