//
// Created by max on 25/12/16.
//

#include "RangeConverter.h"

template<>
int
RangeConverter<QDate, int>::operator()(QDate const& date) const
{
    qint64 const totalDifference = fromEnd.toJulianDay() - fromStart.toJulianDay();
    qint64 const difference = date.toJulianDay() - fromStart.toJulianDay();
    qreal const quotient = static_cast<qreal>(difference) / static_cast<qreal>(totalDifference);
    int const targetTotalDifference = toEnd - toStart;
    qreal const scaledQuotient = static_cast<qreal>(targetTotalDifference) * quotient;
    int const scaledToTargetRange = static_cast<int>(scaledQuotient);
    return scaledToTargetRange + toStart;
};

std::ostream& operator<< (std::ostream& out, RangeConverter<QDate, int>& rc)
{
    out << "RangeConverter<QDate, int> [" << rc.fromStart.toString().toStdString() << ", " << rc.fromEnd.toString().toStdString()
        << "] -> ["  << rc.toStart << ", " << rc.toEnd << "]";
    return out;
}

std::ostream& operator<< (std::ostream& out, RangeConverter<double, int>& rc)
{
    out << "RangeConverter<double, int> [" << rc.fromStart << ", " << rc.fromEnd
        << "] -> ["  << rc.toStart << ", " << rc.toEnd << "]";
    return out;
}
