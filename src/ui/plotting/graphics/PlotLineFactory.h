//
// Created by max on 25/12/16.
//

#pragma once

#include "PlotElement.h"
#include "CumulativePlotLine.h"
#include <QString>
#include <QVariant>

enum class PlotType
{
    CUMULATIVE,
    CUMULATIVE_WITH_MINMAX,
    DAILY_PEAKS
};

class PlotLineFactory
{
public:
    PlotLineFactory() = default;
    ~PlotLineFactory() = default;

    std::shared_ptr<PlotElement> buildPlotElementFromData(
        QSqlQuery& resultsQuery,
        int const& pixelsPerDay,
        int const& height, int const& leftMargin, int const& topMargin,
        std::pair<QDate, QDate> const& dateRange,
        PlotType const& plotType
    ) const;
protected:
    std::shared_ptr<CumulativePlotLine> buildCumulativePlotLine(
            QSqlQuery& resultsQuery,
            int const& pixelsPerDay,
            int const& height, int const& leftMargin, int const& topMargin,
            std::pair<QDate, QDate> const& dateRange
    ) const;
};



