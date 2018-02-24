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
CompoundFilter::clear()
{
    filters.clear();
}

void
CompoundFilter::addFilter(std::shared_ptr<RawItemFilter> filter)
{
    filters.push_back(filter);
}

bool
ConjunctionFilter::operator()(RawItem const& item)
{
    return std::all_of(filters.begin(),
            filters.end(),
            [item](std::shared_ptr<RawItemFilter> filter) -> bool
            {
                if (!filter) return false;
                return (*filter)(item);
            });
}

NegationFilter::NegationFilter(std::shared_ptr<RawItemFilter> filter_)
:   filter(filter_)
{}

bool
NegationFilter::operator()(RawItem const& item)
{
    return !(*filter)(item);
}
