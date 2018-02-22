#include <algorithm>

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
        DateGreaterThanOrEqual(QDate border_)
            : border(border_) {};
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
        DateLessThanOrEqual(QDate border_)
            : border(border_) {};
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
