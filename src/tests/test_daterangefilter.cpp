//
// Created by max on 01/12/16.
//

#include <QDate>
#include "../third_party/catch/catch.hpp"
#include "../data/DateRangeFilter.h"

TEST_CASE("DateRangeFilter::DateRangeFilter(std::pair<QDate, QDate> const&)", "[data]")
{
    SECTION("Constructing with valid values")
    {
        std::pair<QDate, QDate> dateRange = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
        REQUIRE_NOTHROW(DateRangeFilter (dateRange));
    }

    SECTION("Constructing with invalid values")
    {
        std::pair<QDate, QDate> dateRange = std::make_pair(QDate(2018, 12, 24), QDate(2017, 01, 14));
        REQUIRE_THROWS_AS(DateRangeFilter (dateRange), std::invalid_argument);
    }
}

TEST_CASE("DateRangeFilter::DateRangeFilter(QDate const&, QDate const&)", "[data]")
{
    SECTION("Constructing with valid values")
    {
        std::pair<QDate, QDate> dateRange = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
        REQUIRE_NOTHROW(DateRangeFilter (dateRange.first, dateRange.second));
    }

    SECTION("Constructing with invalid values")
    {
        std::pair<QDate, QDate> dateRange = std::make_pair(QDate(2018, 12, 24), QDate(2017, 01, 14));
        REQUIRE_THROWS_AS(DateRangeFilter (dateRange.first, dateRange.second), std::invalid_argument);
        REQUIRE_NOTHROW(DateRangeFilter (dateRange.second, dateRange.first));
    }
}

TEST_CASE("DateRangeFilter::~DateRangeFilter()", "[data]")
{
    SECTION("Deconstructing")
    {
        std::pair<QDate, QDate> dateRange = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
        DateRangeFilter * f = new DateRangeFilter(dateRange);
        REQUIRE_NOTHROW(delete f);
    }
}

TEST_CASE("DateRangeFilter::setRange(std::pair<QDate, QDate> const&)", "[data]")
{
    std::pair<QDate, QDate> dateRangeValid = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
    std::pair<QDate, QDate> dateRangeValid2 = std::make_pair(QDate(2016, 12, 24), QDate(2016, 12, 24));
    std::pair<QDate, QDate> dateRangeInvalid = std::make_pair(QDate(2018, 12, 24), QDate(2017, 01, 14));
    SECTION("Setting with valid values")
    {
        DateRangeFilter f (dateRangeValid);
        REQUIRE_NOTHROW(f.setRange(dateRangeValid));
        REQUIRE_NOTHROW(f.setRange(dateRangeValid2));
    }

    SECTION("Setting with invalid values")
    {
        DateRangeFilter f (dateRangeValid);
        REQUIRE_THROWS_AS(f.setRange(dateRangeInvalid), std::invalid_argument);
    }
}

TEST_CASE("DateRangeFilter::setRange(QDate const&, QDate const&)", "[data]")
{
    std::pair<QDate, QDate> dateRangeValid = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
    std::pair<QDate, QDate> dateRangeValid2 = std::make_pair(QDate(2016, 12, 24), QDate(2016, 12, 24));
    std::pair<QDate, QDate> dateRangeInvalid = std::make_pair(QDate(2018, 12, 24), QDate(2017, 01, 14));
    SECTION("Setting with valid values")
    {
        DateRangeFilter f (dateRangeValid);
        REQUIRE_NOTHROW(f.setRange(dateRangeValid.first, dateRangeValid.second));
        REQUIRE_NOTHROW(f.setRange(dateRangeValid2.first, dateRangeValid2.second));
        REQUIRE_NOTHROW(f.setRange(dateRangeInvalid.second, dateRangeInvalid.first));
    }

    SECTION("Setting with invalid values")
    {
        DateRangeFilter f (dateRangeValid);
        REQUIRE_THROWS_AS(f.setRange(dateRangeValid.second, dateRangeValid.first), std::invalid_argument);
        REQUIRE_THROWS_AS(f.setRange(dateRangeInvalid.first, dateRangeInvalid.second), std::invalid_argument);
    }
}

TEST_CASE("DateRangeFilter::contains(QDate const&) const", "[data]")
{
    std::pair<QDate, QDate> const dateRange = std::make_pair(QDate(2016, 12, 24), QDate(2017, 01, 14));
    QDate const inside1 (2016, 12, 24);
    QDate const inside2 (2016, 12, 25);
    QDate const inside3 (2017, 1, 1);
    QDate const inside4 (2016, 12, 31);
    QDate const inside5 (2017, 1, 14);
    QDate const outside1 (1999, 12, 25);
    QDate const outside2 (2015, 12, 24);
    QDate const outside3 (2016, 12, 23);
    QDate const outside4 (1017, 1, 15);
    QDate outside5 (2200, 12, 25);

    DateRangeFilter f (dateRange);
    REQUIRE(f.contains(inside1));
    REQUIRE(f.contains(inside2));
    REQUIRE(f.contains(inside3));
    REQUIRE(f.contains(inside4));
    REQUIRE(f.contains(inside5));
    REQUIRE_FALSE(f.contains(outside1));
    REQUIRE_FALSE(f.contains(outside2));
    REQUIRE_FALSE(f.contains(outside3));
    REQUIRE_FALSE(f.contains(outside4));
    REQUIRE_FALSE(f.contains(outside5));
}

TEST_CASE("DateRangeFilter::asSqlWhere(QString const&)", "[data]")
{
    SECTION("test1")
    {
        DateRangeFilter f (QDate(2016, 01, 01), QDate(2016, 12, 31));
        QString fieldName ("dateFieldName");

        REQUIRE(f.asSqlWhere(fieldName) == "dateFieldName >= '2016-01-01' AND dateFieldName <= '2016-12-31'");
    }
}
