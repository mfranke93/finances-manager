#include "../third_party/catch/catch.hpp"
#include "../data/DateToStringFactory.h"

TEST_CASE("DateToStringFactory::build(QString const&, QDate const&)", "[data]")
{
    DateToStringFactory f;
    QString format;
    auto test = [&f, &format](QDate date, QString expectedOut) -> void
    {
        REQUIRE(f.build(format, date) == expectedOut);
    };

    SECTION("Day of month")
    {
        SECTION("\"d\"")
        {
            format = "d";

            test(QDate(2017, 12, 1), "1");
            test(QDate(2017, 12, 12), "12");
            test(QDate(2017, 12, 31), "31");
            test(QDate(1995, 4, 9), "9");
        }

        SECTION("\"day\"")
        {
            format = "day";

            test(QDate(2017, 12, 1), "1");
            test(QDate(2017, 12, 12), "12");
            test(QDate(2017, 12, 31), "31");
            test(QDate(1995, 4, 9), "9");
        }

        SECTION("\"dd\"")
        {
            format = "dd";

            test(QDate(2017, 12, 1), "01");
            test(QDate(2017, 12, 12), "12");
            test(QDate(2017, 12, 31), "31");
            test(QDate(1995, 4, 9), "09");
        }
    }

    SECTION("Month")
    {
        SECTION("\"m\"")
        {
            format = "m";

            test(QDate(2016, 12, 21), "12");
            test(QDate(2013, 4, 2), "4");
            test(QDate(2017, 4, 12), "4");
            test(QDate(2001, 2, 28), "2");
            test(QDate(2001, 10, 28), "10");
        }

        SECTION("\"mm\"")
        {
            format = "mm";

            test(QDate(2016, 12, 21), "12");
            test(QDate(2013, 4, 2), "04");
            test(QDate(2017, 4, 12), "04");
            test(QDate(2001, 2, 28), "02");
            test(QDate(2001, 10, 28), "10");
        }

        SECTION("\"mmm\"")
        {
            format = "mmm";

            test(QDate(2016, 12, 21), "Dec");
            test(QDate(2013, 4, 2), "Apr");
            test(QDate(2017, 4, 12), "Apr");
            test(QDate(2001, 2, 28), "Feb");
            test(QDate(2001, 10, 28), "Oct");
        }

        SECTION("\"month\"")
        {
            format = "month";

            test(QDate(2016, 12, 21), "December");
            test(QDate(2013, 4, 2), "April");
            test(QDate(2017, 4, 12), "April");
            test(QDate(2001, 2, 28), "February");
            test(QDate(2001, 10, 28), "October");
        }
    }

    SECTION("Year")
    {
        SECTION("\"yy\"")
        {
            format = "yy";

            test(QDate(2012, 3, 14), "12");
            test(QDate(2011, 12, 9), "11");
            test(QDate(2010, 11, 12), "10");
            test(QDate(2003, 7, 1), "03");
            test(QDate(1999, 5, 4), "99");
            test(QDate(2004, 12, 31), "04");
        }

        SECTION("\"yyyy\"")
        {
            format = "yyyy";

            test(QDate(2012, 3, 14), "2012");
            test(QDate(2011, 12, 9), "2011");
            test(QDate(2010, 11, 12), "2010");
            test(QDate(2003, 7, 1), "2003");
            test(QDate(1999, 5, 4), "1999");
            test(QDate(2004, 12, 31), "2004");
        }

        SECTION("\"year\"")
        {
            format = "year";

            test(QDate(2012, 3, 14), "2012");
            test(QDate(2011, 12, 9), "2011");
            test(QDate(2010, 11, 12), "2010");
            test(QDate(2003, 7, 1), "2003");
            test(QDate(1999, 5, 4), "1999");
            test(QDate(2004, 12, 31), "2004");
        }
    }

    SECTION("Week-dependent year")
    {
        SECTION("\"wy\"")
        {
            format = "wy";

            test(QDate(2012, 3, 14), "12");
            test(QDate(2011, 12, 9), "11");
            test(QDate(2010, 11, 12), "10");
            test(QDate(2003, 7, 1), "03");
            test(QDate(1999, 5, 4), "99");
            test(QDate(2004, 12, 31), "04");
            test(QDate(2000, 1, 1), "99");      // ISO 8601
            test(QDate(2002, 12, 31), "03");    // ISO 8601
        }

        SECTION("\"wyyy\"")
        {
            format = "wyyy";

            test(QDate(2012, 3, 14), "2012");
            test(QDate(2011, 12, 9), "2011");
            test(QDate(2010, 11, 12), "2010");
            test(QDate(2003, 7, 1), "2003");
            test(QDate(1999, 5, 4), "1999");
            test(QDate(2004, 12, 31), "2004");
            test(QDate(2000, 1, 1), "1999");    // ISO 8601
            test(QDate(2002, 12, 31), "2003");  // ISO 8601
        }
    }

    SECTION("Week")
    {
        SECTION("\"w\"")
        {
            format = "w";

            test(QDate(2012, 3, 14), "11");
            test(QDate(2011, 12, 9), "49");
            test(QDate(2010, 11, 12), "45");
            test(QDate(2003, 7, 1), "27");
            test(QDate(1999, 2, 4), "5");
            test(QDate(1999, 1, 8), "1");
            test(QDate(2004, 12, 31), "53");
            test(QDate(2000, 1, 1), "52");      // ISO 8601
            test(QDate(2002, 12, 31), "1");     // ISO 8601
        }

        SECTION("\"ww\"")
        {
            format = "ww";

            test(QDate(2012, 3, 14), "11");
            test(QDate(2011, 12, 9), "49");
            test(QDate(2010, 11, 12), "45");
            test(QDate(2003, 7, 1), "27");
            test(QDate(1999, 2, 4), "05");
            test(QDate(1999, 1, 8), "01");
            test(QDate(2004, 12, 31), "53");
            test(QDate(2000, 1, 1), "52");       // ISO 8601
            test(QDate(2002, 12, 31), "01");     // ISO 8601
        }
    }

    SECTION("Day of week")
    {
        SECTION("\"wd\"")
        {
            format = "wd";

            test(QDate(2017, 9, 11), "Mo");
            test(QDate(2017, 9, 12), "Tu");
            test(QDate(2017, 9, 13), "We");
            test(QDate(2017, 9, 14), "Th");
            test(QDate(2017, 9, 15), "Fr");
            test(QDate(2017, 9, 16), "Sa");
            test(QDate(2017, 9, 17), "Su");
        }

        SECTION("\"wdd\"")
        {
            format = "wdd";

            test(QDate(2017, 9, 11), "Mon");
            test(QDate(2017, 9, 12), "Tue");
            test(QDate(2017, 9, 13), "Wed");
            test(QDate(2017, 9, 14), "Thu");
            test(QDate(2017, 9, 15), "Fri");
            test(QDate(2017, 9, 16), "Sat");
            test(QDate(2017, 9, 17), "Sun");
        }

        SECTION("\"weekday\"")
        {
            format = "weekday";

            test(QDate(2017, 9, 11), "Monday");
            test(QDate(2017, 9, 12), "Tuesday");
            test(QDate(2017, 9, 13), "Wednesday");
            test(QDate(2017, 9, 14), "Thursday");
            test(QDate(2017, 9, 15), "Friday");
            test(QDate(2017, 9, 16), "Saturday");
            test(QDate(2017, 9, 17), "Sunday");
        }
    }
}
