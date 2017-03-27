//
// Created by max on 25/12/16.
//

#pragma once

#include "PlotElement.h"
#include "CumulativePlotLine.h"
#include "DailyChangesPlotLine.h"
#include <QString>
#include <QVariant>

enum class PlotType
{
    CUMULATIVE              = 0,
    CUMULATIVE_WITH_MINMAX  = 1,
    DAILY_PEAKS             = 2
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
    std::shared_ptr<DailyChangesPlotLine> buildDailyPeaksPlotLine(
            QSqlQuery& resultsQuery,
            int const& pixelsPerDay,
            int const& height, int const& leftMargin, int const& topMargin,
            std::pair<QDate, QDate> const& dateRange
    ) const;
};



