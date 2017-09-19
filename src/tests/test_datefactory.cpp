#include "../third_party/catch/catch.hpp"
#include "../data/DateFactory.h"
#include "helpers.h"

TEST_CASE("DateFactory::build(QDate const&)", "[data]")
{
    SECTION("First of month")
    {
        QString const expr ("FOM");
        DateFactory const d (expr);

        auto testMonth = [&d](int year, int month, int daysInMonth) -> void
        {
            QDate should (year, month, 1);
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate date = d.build(QDate(year, month, day));
                REQUIRE(date == should);
            }
        };

        testMonth(2017, 9, 30);
        testMonth(2017, 12, 31);
        testMonth(2017, 2, 28);
        testMonth(2016, 2, 29);
    }

    SECTION("First workday of month")
    {
        QString const expr ("FWOM");
        DateFactory const d (expr);

        auto testMonth = [&d](int year, int month, int daysInMonth, int firstWorkday) -> void
        {
            QDate should (year, month, firstWorkday);
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate date = d.build(QDate(year, month, day));
                REQUIRE(date == should);
            }
        };

        testMonth(2017, 1, 31, 2);
        testMonth(2017, 2, 28, 1);
        testMonth(2017, 3, 31, 1);
        testMonth(2017, 4, 30, 3);
        testMonth(2017, 5, 31, 1);
        testMonth(2017, 6, 30, 1);
        testMonth(2017, 7, 31, 3);
        testMonth(2017, 8, 31, 1);
        testMonth(2017, 9, 30, 1);
        testMonth(2017, 10, 31, 2);
        testMonth(2017, 11, 30, 1);
        testMonth(2017, 12, 31, 1);
        testMonth(2016, 2, 29, 1);
    }

    SECTION("Last of month")
    {
        QString const expr ("LOM");
        DateFactory const d (expr);

        auto testMonth = [&d](int year, int month, int daysInMonth) -> void
        {
            QDate should (year, month, daysInMonth);
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate date = d.build(QDate(year, month, day));
                REQUIRE(date == should);
            }
        };

        testMonth(2017, 1, 31);
        testMonth(2017, 2, 28);
        testMonth(2017, 3, 31);
        testMonth(2017, 4, 30);
        testMonth(2017, 5, 31);
        testMonth(2017, 6, 30);
        testMonth(2017, 7, 31);
        testMonth(2017, 8, 31);
        testMonth(2017, 9, 30);
        testMonth(2017, 10, 31);
        testMonth(2017, 11, 30);
        testMonth(2017, 12, 31);
        testMonth(2016, 2, 29);
    }

    SECTION("Last workday of month")
    {
        QString const expr ("LWOM");
        DateFactory const d (expr);

        auto testMonth = [&d](int year, int month, int daysInMonth, int lastWorkday) -> void
        {
            QDate should (year, month, lastWorkday);
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate date = d.build(QDate(year, month, day));
                REQUIRE(date == should);
            }
        };

        testMonth(2017, 1, 31, 31);
        testMonth(2017, 2, 28, 28);
        testMonth(2017, 3, 31, 31);
        testMonth(2017, 4, 30, 28);
        testMonth(2017, 5, 31, 31);
        testMonth(2017, 6, 30, 30);
        testMonth(2017, 7, 31, 31);
        testMonth(2017, 8, 31, 31);
        testMonth(2017, 9, 30, 29);
        testMonth(2017, 10, 31, 31);
        testMonth(2017, 11, 30, 30);
        testMonth(2017, 12, 31, 29);
        testMonth(2016, 2, 29, 29);
    }

    SECTION("Last day of month or next workday")
    {
        QString const expr ("LOMNW");
        DateFactory const d (expr);

        auto testMonth = [&d](int year, int month, int daysInMonth, int shouldYear, int shouldMonth, int shouldDay) -> void
        {
            QDate should (shouldYear, shouldMonth, shouldDay);
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate date = d.build(QDate(year, month, day));
                REQUIRE(date == should);
            }
        };

        testMonth(2017, 1, 31, 2017, 1, 31);
        testMonth(2017, 2, 28, 2017, 2, 28);
        testMonth(2017, 3, 31, 2017, 3, 31);
        testMonth(2017, 4, 30, 2017, 5, 1);
        testMonth(2017, 5, 31, 2017, 5, 31);
        testMonth(2017, 6, 30, 2017, 6, 30);
        testMonth(2017, 7, 31, 2017, 7, 31);
        testMonth(2017, 8, 31, 2017, 8, 31);
        testMonth(2017, 9, 30, 2017, 10, 2);
        testMonth(2017, 10, 31, 2017, 10, 31);
        testMonth(2017, 11, 30, 2017, 11, 30);
        testMonth(2017, 12, 31, 2018, 1, 1);
        testMonth(2016, 2, 29, 2016, 2, 29);
    }

    SECTION("By day number")
    {
        auto testMonth = [](int year, int month, int daysInMonth) -> void
        {
            for (int day = 1; day <= daysInMonth; ++day)
            {
                QDate should (year, month, day);
                QString const expr = QString::number(day);
                DateFactory d (expr);
                for (int day2 = 1; day2 <= daysInMonth; ++day2)
                {
                    QDate now (year, month, day2);
                    REQUIRE(d.build(now) == should);
                }
            }
        };

        testMonth(2017, 1, 31);
        testMonth(2017, 2, 28);
        testMonth(2017, 3, 31);
        testMonth(2017, 4, 30);
        testMonth(2017, 5, 31);
        testMonth(2017, 6, 30);
        testMonth(2017, 7, 31);
        testMonth(2017, 8, 31);
        testMonth(2017, 9, 30);
        testMonth(2017, 10, 31);
        testMonth(2017, 11, 30);
        testMonth(2017, 12, 31);
        testMonth(2016, 2, 29);
    }

    SECTION("Set weekday")
    {
        auto testWeekday = [](int year, int month, int day, QString expr, int yshould, int mshould, int dshould) -> void
        {
            QDate should (yshould, mshould, dshould);
            QDate now (year, month, day);
            DateFactory d (expr);
            REQUIRE(d.build(now) == should);
        };

        testWeekday(2017, 9, 19, "Monday", 2017, 9, 18);
        testWeekday(2017, 9, 19, "Tuesday", 2017, 9, 19);
        testWeekday(2017, 9, 19, "Wednesday", 2017, 9, 20);
        testWeekday(2017, 9, 19, "Thursday", 2017, 9, 21);
        testWeekday(2017, 9, 19, "Friday", 2017, 9, 22);
        testWeekday(2017, 9, 19, "Saturday", 2017, 9, 23);
        testWeekday(2017, 9, 19, "Sunday", 2017, 9, 24);
    }
}
