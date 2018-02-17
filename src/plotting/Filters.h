#include <algorithm>

#include "RawItem.h"

#pragma once

namespace detail {
    template<bool equalsOk>
    class DateGreaterThanOrEqual
    {
        public:
        DateGreaterThanOrEqual(QDate border_)
            : border(border_) {};
        ~DateGreaterThanOrEqual() = default;

        bool operator()(RawItem const& other)
        {
            if (equalsOk) return other.date >= border;
            return other.date > border;
        };

        private:
        QDate border;
    };
}

using DateGreaterThan = detail::DateGreaterThanOrEqual<false>;
using DateGreaterEqual = detail::DateGreaterThanOrEqual<true>;
