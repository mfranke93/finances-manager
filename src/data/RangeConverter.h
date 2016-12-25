//
// Created by max on 25/12/16.
//

#pragma once


#include <utility>
#include <QtCore/QDate>
#include <iostream>

template<typename FromType_, typename ToType_>
class RangeConverter
{
public:
    RangeConverter() = delete;
    RangeConverter(RangeConverter const&) = delete;
    RangeConverter& operator= (RangeConverter const&) = delete;
    RangeConverter(std::pair<FromType_, FromType_> const& range, std::pair<ToType_, ToType_> const& targetRange)
            : fromStart(range.first), fromEnd(range.second), toStart(targetRange.first), toEnd(targetRange.second)
    {
    };
    ~RangeConverter() = default;

    ToType_ operator()(FromType_ const& inValue) const
    {
        FromType_ const totalDifference = fromEnd - fromStart;
        FromType_ const difference = inValue - fromStart;
        FromType_ const quotient = difference / totalDifference;
        ToType_ const targetTotalDifference = toEnd - toStart;
        FromType_ const scaledQuotient = static_cast<FromType_>(targetTotalDifference) * quotient;
        ToType_ const scaledToTargetRange = static_cast<ToType_>(scaledQuotient);
        return scaledToTargetRange + toStart;
    }

    friend std::ostream& operator<< (std::ostream& out, RangeConverter<QDate, int>& rc);
    friend std::ostream& operator<< (std::ostream& out, RangeConverter<double, int>& rc);

private:
    FromType_ const fromStart;
    FromType_ const fromEnd;

    ToType_ const toStart;
    ToType_ const toEnd;
};

template<>
int RangeConverter<QDate, int>::operator()(QDate const& inValue) const;

typedef RangeConverter<QDate, int> DateToIntConverter;
typedef RangeConverter<double, int> VerticalScaler;



