#include <algorithm>
#include <memory>

#include "RawItem.h"

#pragma once

class RawItemFilter
{
    public:
        virtual bool operator()(RawItem const&) = 0;
};

namespace detail {
    template<bool equalsOk>
    class DateGreaterThanOrEqual : public RawItemFilter
    {
        public:
        DateGreaterThanOrEqual(QDate const& border_)
            : border(border_) { };

        ~DateGreaterThanOrEqual() = default;

        bool operator()(RawItem const& other) override
        {
            if (equalsOk) return other.date >= border;
            return other.date > border;
        };

        private:
        QDate border;
    };

    template<bool equalsOk>
    class DateLessThanOrEqual : public RawItemFilter
    {
        public:
        DateLessThanOrEqual(QDate const& border_)
            : border(border_) { };
        ~DateLessThanOrEqual() = default;

        bool operator()(RawItem const& other) override
        {
            if (equalsOk) return other.date <= border;
            return other.date < border;
        };

        private:
        QDate border;
    };
}

using DateGreaterThan = detail::DateGreaterThanOrEqual<false>;
using DateGreaterEqual = detail::DateGreaterThanOrEqual<true>;
using DateLessThan = detail::DateLessThanOrEqual<false>;
using DateLessEqual = detail::DateLessThanOrEqual<true>;

class DisjunctionFilter : public RawItemFilter
{
    public:
        DisjunctionFilter() = default;
        ~DisjunctionFilter() = default;

        bool operator()(RawItem const&) override;

        void clear();
        void addFilter(std::shared_ptr<RawItemFilter>);

    private:
        std::vector<std::shared_ptr<RawItemFilter>> filters;
};
