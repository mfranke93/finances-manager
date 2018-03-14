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

class MonthFilter : public RawItemFilter
{
    public:
        MonthFilter(int year, int month);
        virtual ~MonthFilter() = default;

        bool operator()(RawItem const&) override;

    private:
        DateGreaterEqual    currentMonth;
        DateLessThan        nextMonth;
};

class CompoundFilter : public RawItemFilter
{
    public:
        CompoundFilter() = default;
        virtual ~CompoundFilter() = default;

        void clear();
        void addFilter(std::shared_ptr<RawItemFilter>);

    protected:
        std::vector<std::shared_ptr<RawItemFilter>> filters;
};

class DisjunctionFilter : public CompoundFilter
{
    public:
        DisjunctionFilter() = default;
        ~DisjunctionFilter() = default;

        bool operator()(RawItem const&) override;
};

class ConjunctionFilter : public CompoundFilter
{
    public:
        ConjunctionFilter() = default;
        ~ConjunctionFilter() = default;

        bool operator()(RawItem const&) override;
};

class NegationFilter : public RawItemFilter
{
    public:
        NegationFilter(std::shared_ptr<RawItemFilter>);
        ~NegationFilter() = default;

        bool operator()(RawItem const&) override;

    private:
        std::shared_ptr<RawItemFilter> filter;
};
