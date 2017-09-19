#include <QtCore>
#include <iostream>

std::ostream&
operator<< (std::ostream& stream, QDate const& date);

std::ostream&
operator<< (std::ostream& stream, QString const& str);
