#include <QtCore>

#pragma once

/**
 * Templates for date expressions.
 */
namespace templates 
{
    constexpr static char const * const FIRST_OF_MONTH { "FOM" };
    constexpr static char const * const FIRST_WORKDAY_OF_MONTH { "FWOM" };
    constexpr static char const * const LAST_OF_MONTH { "LOM" };
    constexpr static char const * const LAST_WORKDAY_OF_MONTH { "LWOM" };
    constexpr static char const * const LAST_OF_MONTH_OR_NEXT_WORKDAY { "LOMNW" };

    namespace weekdays 
    {
        constexpr static char const * const MONDAY { "Monday" };
        constexpr static char const * const TUESDAY { "Tuesday" };
        constexpr static char const * const WEDNESDAY { "Wednesday" };
        constexpr static char const * const THURSDAY { "Thursday" };
        constexpr static char const * const FRIDAY { "Friday" };
        constexpr static char const * const SATURDAY { "Saturday" };
        constexpr static char const * const SUNDAY { "Sunday" };
    }
}

/**
 * Class to create dates from date templates, like 'first of month'.
 */
class DateFactory
{
    public:
        /**
         * Constructor.
         *
         * \param templateString    Template string. Contains a template:: item or date.
         */
        DateFactory(QString const& templateString);
        DateFactory() = delete;
        /**
         * Destructor.
         */
        ~DateFactory() = default;

        /**
         * Build a date from the template.
         *
         * \param now   The date to take as point of reference, for example to
         *              get year and month for 'first of month'.
         * \return      A date constructed using the template.
         */
        QDate build(QDate const& now) const;

    protected:
        /**
         * Get first day of month for given date.
         *
         * \param       Date
         * \return      First of month for month in date
         */
        QDate firstOfMonth(QDate const&) const;

        /**
         * Get first workday of month for given date.
         *
         * \param       Date
         * \return      First workday (1st or next Monday) of month for month in date
         */
        QDate firstWorkdayOfMonth(QDate const&) const;

        /**
         * Get last day of month for given date.
         *
         * \param       Date
         * \return      Last of month for month in date
         */
        QDate lastOfMonth(QDate const&) const;

        /**
         * Get last workday of month for given date.
         *
         * \param       Date
         * \return      Last workday (last or last Friday) of month for month in date
         */
        QDate lastWorkdayOfMonth(QDate const&) const;

        /**
         * Get last of month if is workday, else first workday of next month.
         *
         * \param       Date
         * \return      Last day of month for month in date, or next workday
         */
        QDate lastOfMonthOrNextWorkday(QDate const&) const;

        /**
         * Set the weekday to the passed one.
         *
         * \param       Date
         * \param       Day of week (1..7) to set
         * \return      Date, but weekday set to passed DOW in same week
         */
        QDate setWeekday(QDate const&, int const&) const;

    private:
        /**
         * Template string.
         */
        QString const templateString;

};
