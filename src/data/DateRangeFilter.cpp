//
// Created by max on 01/12/16.
//

#include "DateRangeFilter.h"

DateRangeFilter::DateRangeFilter(std::pair<QDate, QDate> const& range)
: range_(range)
{
    // ctor
    if (range.second.toJulianDay() < range.first.toJulianDay())
    {
        QString s = range.second.toString("yyyy-MM-dd");
        s += " is before ";
        s += range.first.toString("yyyy-MM-dd");
        s += ", but is given as end point.";
        throw std::invalid_argument(s.toStdString());
    }
}

DateRangeFilter::DateRangeFilter(QDate const& from, QDate const& to)
: DateRangeFilter(std::make_pair(from, to))
{
    // ctor
}

DateRangeFilter::DateRangeFilter()
: range_(std::make_pair(QDate(), QDate()))
{

}

DateRangeFilter::DateRangeFilter(DateRangeFilter const& other)
: range_(other.range_)
{}

void
DateRangeFilter::setRange(std::pair<QDate, QDate> const& range)
throw(std::invalid_argument)
{
    if (range.second.toJulianDay() < range.first.toJulianDay())
    {
        QString s = range.second.toString("yyyy-MM-dd");
        s += " is before ";
        s += range.first.toString("yyyy-MM-dd");
        s += ", but is given as end point.";
        throw std::invalid_argument(s.toStdString());
    }
    range_ = range;
}

void
DateRangeFilter::setRange(QDate const& from, QDate const& to)
throw(std::invalid_argument)
{
    setRange(std::make_pair(from, to));
}

std::pair<QDate, QDate> const&
DateRangeFilter::range() const
{
    return range_;
}

bool
DateRangeFilter::contains(QDate const& d) const
{
    if (d.toJulianDay() < range_.first.toJulianDay()) return false;
    if (d.toJulianDay() > range_.second.toJulianDay()) return false;
    return true;
}

QString
DateRangeFilter::asSqlWhere(QString const& field_name) const
{
    QString s;
    s += field_name;
    s += " >= '";
    s += range_.first.toString("yyyy-MM-dd");
    s += "' AND ";
    s += field_name;
    s += " <= '";
    s += range_.second.toString("yyyy-MM-dd");
    s += "'";
    return s;
}
