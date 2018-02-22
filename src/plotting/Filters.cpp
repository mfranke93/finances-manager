#include "Filters.h"

bool
DisjunctionFilter::operator()(RawItem const& item)
{
    return std::any_of(filters.begin(),
            filters.end(),
            [item](std::shared_ptr<RawItemFilter> filter) -> bool
            {
                if (!filter) return false;
                return (*filter)(item);
            });
}

void
DisjunctionFilter::clear()
{
    filters.clear();
}

void
DisjunctionFilter::addFilter(std::shared_ptr<RawItemFilter> filter)
{
    filters.push_back(filter);
}
