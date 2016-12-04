//
// Created by max on 01/12/16.
//

#pragma once

#include <QDate>
#include "DateFilter.h"

class DateRangeFilter: public DateFilter
{
    Q_OBJECT
public:
    explicit DateRangeFilter(std::pair<QDate, QDate> const&) throw(std::invalid_argument);
    explicit DateRangeFilter(QDate const&, QDate const&) throw(std::invalid_argument);
    DateRangeFilter() = delete;
    ~DateRangeFilter() = default;

    void setRange(std::pair<QDate, QDate> const&) throw(std::invalid_argument);
    void setRange(QDate const&, QDate const&) throw(std::invalid_argument);

    std::pair<QDate, QDate> const& range() const;

    bool contains(QDate const&) const override;
    QString asSqlWhere(QString const&) const override;

private:
    std::pair<QDate, QDate> range_;
};



