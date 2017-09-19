//
// Created by max on 25/12/16.
//

#include "../third_party/catch/catch.hpp"
#include "../data/RangeConverter.h"
#include "helpers.h"

TEST_CASE("RangeConverter<double, int>", "[data]")
{
    SECTION("Without offsets")
    {
        std::pair<double, double> inRange = std::make_pair(0.0, 20.0);
        std::pair<int, int> outRange = std::make_pair(0, 20);

        VerticalScaler scaler (inRange, outRange);

        REQUIRE(7 == scaler(7.0));
        REQUIRE(20 == scaler(20.0));
        REQUIRE(0 == scaler(0.0));
    }

    SECTION("With input offset")
    {
        std::pair<double, double> inRange = std::make_pair(10.0, 20.0);
        std::pair<int, int> outRange = std::make_pair(0, 20);

        VerticalScaler scaler (inRange, outRange);

        REQUIRE(14 == scaler(17.0));
        REQUIRE(20 == scaler(20.0));
        REQUIRE(0 == scaler(10.0));
    }

    SECTION("With output offset")
    {
        std::pair<double, double> inRange = std::make_pair(0.0, 10.0);
        std::pair<int, int> outRange = std::make_pair(10, 20);

        VerticalScaler scaler (inRange, outRange);

        REQUIRE(14 == scaler(4.0));
        REQUIRE(20 == scaler(10.0));
        REQUIRE(10 == scaler(0.0));
    }

    SECTION("With offsets")
    {
        std::pair<double, double> inRange = std::make_pair(-10.0, 10.0);
        std::pair<int, int> outRange = std::make_pair(10, 50);

        VerticalScaler scaler (inRange, outRange);

        REQUIRE(35 == scaler(2.5));
        REQUIRE(10 == scaler(-10.0));
        REQUIRE(50 == scaler(10.0));
    }
}

TEST_CASE("RangeConverter<QDate, int>", "[data]")
{
    SECTION("First test")
    {
        QDate const first (2016, 01, 01);
        QDate const second (2016, 01, 14);
        std::pair<QDate, QDate> inRange = std::make_pair(first, second);
        std::pair<int, int> outRange = std::make_pair(1, 14);

        DateToIntConverter dti (inRange, outRange);

        {
            QDate a (2016, 01, 01);
            REQUIRE(1 == dti(a));
        }

        {
            QDate a (2016, 01, 05);
            REQUIRE(5 == dti(a));
        }

        {
            QDate a (2016, 01, 14);
            REQUIRE(14 == dti(a));
        }

        {
            QDate a (2016, 01, 01);
            REQUIRE(1 == dti(a));
        }
    }
}
