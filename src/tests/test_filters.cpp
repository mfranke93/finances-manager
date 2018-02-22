#include "../third_party/catch/catch.hpp"
#include "../plotting/Filters.h"
#include "helpers.h"

TEST_CASE("DateGreaterThanOrEqual<>::operator()(QDate const&)", "[plotting]")
{
    std::vector<RawItem> items = {
        { QDate(2017, 1, 1), 22, 71, 99.26 },
        { QDate(2017, 1, 2), 32, 22, 12.18 },
        { QDate(2017, 1, 3), 19, 27, 15.87 },
        { QDate(2017, 1, 4), 25, 18, 19.54 },
        { QDate(2017, 1, 5), 22, 12, 50.11 },
        { QDate(2017, 1, 6), 25, 54, 74.13 },
        { QDate(2017, 1, 7), 24, 39, 17.16 },
        { QDate(2017, 1, 8), 20, 22, 05.36 },
        { QDate(2017, 1, 9), 14, 11, 63.92 },
        { QDate(2017, 1, 10), 10, 18, 56.0 },
        { QDate(2017, 1, 11), 15, 77, 57.06 },
        { QDate(2017, 1, 12), 12, 74, 11.61 },
        { QDate(2017, 1, 13), 13, 27, 90.11 },
        { QDate(2017, 1, 14), 12, 19, 67.77 },
        { QDate(2017, 1, 15), 12, 90, 54.21 },
        { QDate(2017, 1, 16), 43, 15, 20.17 },
        { QDate(2017, 1, 17), 46, 26, 59.47 },
        { QDate(2017, 1, 18), 26, 14, 11.60 },
        { QDate(2017, 1, 19), 14, 28, 76.70 },
        { QDate(2017, 1, 20), 16, 61, 8.91 }
    };

    SECTION("Greater than")
    {
        std::vector<RawItem> output {};
        DateGreaterThan gt ( QDate(2017, 1, 11) );
        std::copy_if(items.begin(), items.end(), std::back_inserter(output), gt);

        REQUIRE(std::all_of(output.begin(), output.end(), [](RawItem const& i) -> bool
                    { return i.date.day() > 11; }));
        REQUIRE(output.size() == 9);
    }

    SECTION("Greater equal")
    {
        std::vector<RawItem> output {};
        DateGreaterEqual ge ( QDate(2017, 1, 11) );
        std::copy_if(items.begin(), items.end(), std::back_inserter(output), ge);

        REQUIRE(std::all_of(output.begin(), output.end(), [](RawItem const& i) -> bool
                    { return i.date.day() > 10; }));
        REQUIRE(output.size() == 10);
    }
}

TEST_CASE("DateLessThanOrEqual<>::operator()(QDate const&)", "[plotting]")
{
    std::vector<RawItem> items = {
        { QDate(2017, 1, 1), 22, 71, 99.26 },
        { QDate(2017, 1, 2), 32, 22, 12.18 },
        { QDate(2017, 1, 3), 19, 27, 15.87 },
        { QDate(2017, 1, 4), 25, 18, 19.54 },
        { QDate(2017, 1, 5), 22, 12, 50.11 },
        { QDate(2017, 1, 6), 25, 54, 74.13 },
        { QDate(2017, 1, 7), 24, 39, 17.16 },
        { QDate(2017, 1, 8), 20, 22, 05.36 },
        { QDate(2017, 1, 9), 14, 11, 63.92 },
        { QDate(2017, 1, 10), 10, 18, 56.0 },
        { QDate(2017, 1, 11), 15, 77, 57.06 },
        { QDate(2017, 1, 12), 12, 74, 11.61 },
        { QDate(2017, 1, 13), 13, 27, 90.11 },
        { QDate(2017, 1, 14), 12, 19, 67.77 },
        { QDate(2017, 1, 15), 12, 90, 54.21 },
        { QDate(2017, 1, 16), 43, 15, 20.17 },
        { QDate(2017, 1, 17), 46, 26, 59.47 },
        { QDate(2017, 1, 18), 26, 14, 11.60 },
        { QDate(2017, 1, 19), 14, 28, 76.70 },
        { QDate(2017, 1, 20), 16, 61, 8.91 }
    };

    SECTION("Less than")
    {
        std::vector<RawItem> output {};
        DateLessThan lt ( QDate(2017, 1, 11) );
        std::copy_if(items.begin(), items.end(), std::back_inserter(output), lt);

        REQUIRE(std::all_of(output.begin(), output.end(), [](RawItem const& i) -> bool
                    { return i.date.day() < 11; }));
        REQUIRE(output.size() == 10);
    }

    SECTION("Less equal")
    {
        std::vector<RawItem> output {};
        DateLessEqual le ( QDate(2017, 1, 11) );
        std::copy_if(items.begin(), items.end(), std::back_inserter(output), le);

        REQUIRE(std::all_of(output.begin(), output.end(), [](RawItem const& i) -> bool
                    { return i.date.day() < 12; }));
        REQUIRE(output.size() == 11);
    }
}

TEST_CASE("DisjunctionFilter::operator()(QDate const&)", "[plotting]")
{
    std::vector<RawItem> items = {
        { QDate(2017, 1, 1), 22, 71, 99.26 },
        { QDate(2017, 1, 2), 32, 22, 12.18 },
        { QDate(2017, 1, 3), 19, 27, 15.87 },
        { QDate(2017, 1, 4), 25, 18, 19.54 },
        { QDate(2017, 1, 5), 22, 12, 50.11 },
        { QDate(2017, 1, 6), 25, 54, 74.13 },
        { QDate(2018, 1, 7), 24, 39, 17.16 },
        { QDate(2018, 1, 8), 20, 22, 05.36 },
        { QDate(2018, 1, 9), 14, 11, 63.92 },
        { QDate(2018, 1, 10), 10, 18, 56.0 },
        { QDate(2018, 1, 11), 15, 77, 57.06 },
        { QDate(2018, 1, 12), 12, 74, 11.61 },
        { QDate(2018, 1, 13), 13, 27, 90.11 },
        { QDate(2018, 1, 14), 12, 19, 67.77 },
        { QDate(2018, 1, 15), 12, 90, 54.21 },
        { QDate(2019, 1, 16), 43, 15, 20.17 },
        { QDate(2019, 1, 17), 46, 26, 59.47 },
        { QDate(2019, 1, 18), 26, 14, 11.60 },
        { QDate(2019, 1, 19), 14, 28, 76.70 },
        { QDate(2019, 1, 20), 16, 61, 8.91 }
    };

    SECTION("Year is not 2018")
    {
        std::vector<RawItem> output {};
        auto a = std::make_shared<DateGreaterThan>(QDate(2018, 12, 31));
        auto b = std::make_shared<DateLessThan>(QDate(2018, 1, 1));

        DisjunctionFilter filter {};
        filter.addFilter(a);
        filter.addFilter(b);

        std::copy_if(items.begin(), items.end(), std::back_inserter(output), filter);

        REQUIRE(std::all_of(output.begin(), output.end(), [](RawItem const& i) -> bool
                    { return i.date.year() != 2018; }));
        REQUIRE(output.size() == 11);
    }

    SECTION("Or tests")
    {
        struct true_type : public RawItemFilter
        {
            bool operator()(RawItem const&) { return true; };
        };
        struct false_type : public RawItemFilter
        {
            bool operator()(RawItem const&) { return false; };
        };
        RawItem dummy {};

        SECTION("true or false")
        {
            DisjunctionFilter f {};
            f.addFilter(std::make_shared<true_type>());
            f.addFilter(std::make_shared<false_type>());

            REQUIRE(f(dummy));
        }

        SECTION("false or false")
        {
            DisjunctionFilter f {};
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());

            REQUIRE(!f(dummy));
        }

        SECTION("9x false or true")
        {
            DisjunctionFilter f {};
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<true_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());
            f.addFilter(std::make_shared<false_type>());

            REQUIRE(f(dummy));
        }
    }
}
