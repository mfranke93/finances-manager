#include "aggregation.h"

double
sum_of_price::operator()(std::vector<RawItem> const& items) const
{
    return std::accumulate(items.begin(), items.end(),
            0.0,
            [](double old_sum, RawItem const& r)
            {
                return old_sum + r.price;
            });
}

QDate
group_by_month::operator()(RawItem const& item) const
{
    return QDate(item.date.year(), item.date.month(), 1);
}
