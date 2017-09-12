#include "DateFactory.h"

DateFactory::DateFactory(QString const& templateString)
: templateString(templateString)
{
    // ctor
}

QDate
DateFactory::build(QDate const& now) const
{
    if (templateString == templates::FIRST_OF_MONTH)
    {
        return firstOfMonth(now);
    }

    if (templateString == templates::FIRST_WORKDAY_OF_MONTH)
    {
        return firstWorkdayOfMonth(now);
    }

    if (templateString == templates::LAST_OF_MONTH)
    {
        return lastOfMonth(now);
    }

    if (templateString == templates::LAST_WORKDAY_OF_MONTH)
    {
        return lastWorkdayOfMonth(now);
    }

    if (templateString == templates::LAST_OF_MONTH_OR_NEXT_WORKDAY)
    {
        return lastOfMonthOrNextWorkday(now);
    }

    // assume date
    bool okay;
    int dayOfMonth = templateString.toInt(&okay);
    if (okay)
    {
        return QDate (now.year(), now.month(), dayOfMonth);
    }

    std::fprintf(stderr, "Could not parse template %s or no such day: %d",
            templateString.toStdString().c_str(), dayOfMonth);
    return now;
}


QDate
DateFactory::firstOfMonth(QDate const& now)  const
{
    return QDate (now.year(), now.month(), 1);
}

QDate
DateFactory::firstWorkdayOfMonth(QDate const& now)  const
{
    QDate const fom = firstOfMonth(now);
    int const dow = fom.dayOfWeek();
    if (dow > 5) return fom.addDays(8-dow); // +2 if sat, +1 if sun
    return fom;
}

QDate
DateFactory::lastOfMonth(QDate const& now)  const
{
    return QDate (now.year(), now.month(), now.daysInMonth());
}

QDate
DateFactory::lastWorkdayOfMonth(QDate const& now)  const
{
    QDate const lom = lastOfMonth(now);
    int const dow = lom.dayOfWeek();
    if (dow > 5) return lom.addDays(5-dow); // -2 if sunday, -1 if saturday
    else return lom;
}

QDate
DateFactory::lastOfMonthOrNextWorkday(QDate const& now)  const
{
    QDate const lom = lastOfMonth(now);
    int const dow = lom.dayOfWeek();
    if (dow > 5) return lom.addDays(8-dow); // +1 if sunday, +2 if saturday
    else return lom;
}

