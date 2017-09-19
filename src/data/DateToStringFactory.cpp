#include "DateToStringFactory.h"

DateToStringFactory::DateToStringFactory()
{
    mapping = std::unique_ptr<std::map<QString, std::function<QString(QDate const&)>>>(new std::map<QString, std::function<QString(QDate const&)>>());

    // {m} means month number without leading 0
    mapping->emplace(QString("m"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.month());
            });

    // {mm} means month number with leading 0
    mapping->emplace(QString("mm"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.month(), 2, 10, QChar('0'));
            });

    // {mmm} means short month name
    mapping->emplace(QString("mmm"),
            [](QDate const& date) -> QString
            {
                return QDate::shortMonthName(date.month());
            });

    // {month} means full month name
    mapping->emplace(QString("month"),
            [](QDate const& date) -> QString
            {
                return QDate::longMonthName(date.month());
            });

    // {yy} means last two digits of year
    mapping->emplace(QString("yy"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.year() % 100, 2, 10, QChar('0'));
            });

    // {year} or {yyyy} means all digits of year
    {
        auto f = [](QDate const& date) -> QString
        {
            return QString("%1").arg(date.year());
        };
        mapping->emplace(QString("yyyy"), f);
        mapping->emplace(QString("year"), f);
    }

    // {d} or {day} means day of month without leading 0s
    {
        auto f = [](QDate const& date) -> QString
        {
            return QString("%1").arg(date.day());
        };
        mapping->emplace(QString("d"), f);
        mapping->emplace(QString("day"), f);
    }

    // {dd} means day of month with leading 0s
    mapping->emplace(QString("dd"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.day(), 2, 10, QChar('0'));
            });

    // {w} means week without leading 0s
    mapping->emplace(QString("w"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.weekNumber());
            });

    // {ww} means week with leading 0s
    mapping->emplace(QString("ww"),
            [](QDate const& date) -> QString
            {
                return QString("%1").arg(date.weekNumber(), 2, 10, QChar('0'));
            });

    // {wy} means last two digits of year in respect to the calendar week
    mapping->emplace(QString("wy"),
            [](QDate const& date) -> QString
            {
                int year;
                date.weekNumber(&year);
                return QString("%1").arg(year % 100, 2, 10, QChar('0'));
            });

    // {wyyy} means year in respect to the calendar week
    mapping->emplace(QString("wyyy"),
            [](QDate const& date) -> QString
            {
                int year;
                date.weekNumber(&year);
                return QString("%1").arg(year);
            });

    // {year} or {yyyy} means all digits of year
    {
        auto f = [](QDate const& date) -> QString
        {
            int year;
            date.weekNumber(&year);
            return QString("%1").arg(year);
        };
        mapping->emplace(QString("YYYY"), f);
        mapping->emplace(QString("YEAR"), f);
    }

    // {wd} means weekday, first two letters
    mapping->emplace(QString("wd"),
            [](QDate const& date) -> QString
            {
                QString dayName = QDate::shortDayName(date.dayOfWeek());
                dayName.truncate(2);
                return dayName;
            });

    // {wdd} means weekday, first two letters
    mapping->emplace(QString("wdd"),
            [](QDate const& date) -> QString
            {
                return QDate::shortDayName(date.dayOfWeek());
            });

    // {weekday} means weekday, first two letters
    mapping->emplace(QString("weekday"),
            [](QDate const& date) -> QString
            {
                return QDate::longDayName(date.dayOfWeek());
            });
}

QString
DateToStringFactory::build(QString const& format, QDate const& date) const
{
    QStringList lst = format.split(QString(","));
    QString fmt = lst.front();
    lst.pop_front();

    QDate d (date);
    for (QString const& s : lst)
    {
        d = transform(d, s);
    }

    auto it = mapping->find(fmt);
    if (it == mapping->end())
    {
        return QString("err: '") + format + "'";
    }

    return (it->second)(d);
}

QDate
DateToStringFactory::transform(QDate const& date, QString const& transformation) const
{
    QRegExp rx ("^([+-]\\d+)([dwmy])$");
    int idx = rx.indexIn(transformation);
    if (idx == -1)
    {
        std::fprintf(stderr, "Could not parse transformation: \"%s\"\n",
                transformation.toStdString().c_str());
    }
    QString count = rx.cap(1);
    QString unit  = rx.cap(2);

    int offset = count.toInt();
    if (unit == QString("d"))
    {
        return date.addDays(offset);
    }
    else if (unit == QString("w"))
    {
        return date.addDays(7*offset);
    }
    else if (unit == QString("m"))
    {
        return date.addMonths(offset);
    }
    else if (unit == QString("y"))
    {
        return date.addYears(offset);
    }
    else
    {
        std::fprintf(stderr, "Could not parse transformation: \"%s\"\n",
                transformation.toStdString().c_str());
        return date;
    }
}
