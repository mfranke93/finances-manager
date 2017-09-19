#include "helpers.h"

std::ostream&
operator<< (std::ostream& stream, QDate const& date)
{
    stream << date.toString().toStdString();
    return stream;
}

std::ostream&
operator<< (std::ostream& stream, QString const& str)
{
    stream << "\"" << str.toStdString() << "\"";
    return stream;
}
