#include <algorithm>
#include <map>
#include <vector>

#include "Filters.h"

#pragma once

template<typename AggregatorFn,
    typename RangeFilter,
    typename range_t = typename std::result_of<RangeFilter(RawItem const&)>::type,
    typename agg_t   = typename std::result_of<AggregatorFn(std::vector<RawItem> const&)>::type>
std::map<range_t, agg_t>
aggregate(std::vector<RawItem> items,
        AggregatorFn agg,
        RangeFilter filter)
{
    std::map<range_t, std::vector<RawItem>> grouped_values {};
    std::map<range_t, agg_t> aggregated_values {};

    // sort values into range bins
    std::for_each(items.begin(), items.end(),
            [&grouped_values,&filter](RawItem& item)
            {
                auto r = filter(item);
                grouped_values[r].push_back(item);
            });

    // aggregate values by bin
    using pair_type = typename decltype(grouped_values)::value_type;
    std::for_each(grouped_values.begin(), grouped_values.end(),
            [&aggregated_values,&agg](pair_type const& item)
            {
                auto a = agg(item.second);
                aggregated_values[item.first] = a;
            });

    return aggregated_values;
}

struct sum_of_price
{
    double
    operator()(std::vector<RawItem> const&) const;
};

struct group_by_month
{
    QDate
    operator()(RawItem const&) const;
};
