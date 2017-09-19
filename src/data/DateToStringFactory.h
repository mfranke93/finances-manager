#include <QtCore>
#include <memory>
#include <functional>

#pragma once

/**
 * Class for getting formatted strings from date format fragments.
 */
class DateToStringFactory
{
    public: 
        /**
         * Constructor.
         */
        DateToStringFactory();

        /**
         * Destructor.
         */
        ~DateToStringFactory() = default;

        /**
         * Builder method.
         *
         * Takes a format argument. The format argument may be one of following:
         *
         *      d               Day of month
         *      day             Day of month
         *      dd              Day of month, zero padded
         *      m               Month
         *      mm              Month, zero padded
         *      mmm             Month, first three letters of name
         *      month           Month, full name
         *      yy              Year, last two digits
         *      yyyy            Year
         *      wy              Year of calendar week according to ISO 8601, last two digits
         *      wyyy            Year of calendar week according to ISO 8601
         *      w               Week of year according to ISO 8601
         *      ww              Week of year according to ISO 8601, zero padded
         *      wd              Day of week, first two letters
         *      wdd             Day of week, first three letters
         *      weekday         Day of week
         *
         *  ISO 8601 defines that the first Thursday of the year is always in
         *  week 1. By this definition, the first Friday to Saturday of a year
         *  may well be in the last year's last week, as well as the last
         *  Monday to Wednesday of a year may well be in next year's first
         *  week. This makes the "wy" and "wyyy" arguments necessary.
         *
         *  \param format       Format string
         *  \param date         Date to format from
         *  \return             String format of date given
         *
         */
        QString build(QString const& format, QDate const& date) const;

        /**
         * Transform a date instance according to the transformation string passed. 
         *
         * Examples for the transformation strings are
         *      +1m             Add one month (keep day of month if possible).
         *      -2d             Subtract two days
         *      +1w             Add one week (7 days)
         *
         * \param date              Date to transform, in place
         * \param transformation    Transformation string
         * \return                  Transformed date
         */
        QDate transform(QDate const& date, QString const& transformation) const;

    private:
        /**
         * Mapping from format arguments to functions to create QStrings.
         */
        std::unique_ptr<std::map<QString, std::function<QString(QDate const&)>>> mapping;
};
