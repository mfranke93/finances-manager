#include <QtCore>

#include "DateToStringFactory.h"

#pragma once

class RecurrentItemNameFactory
{
    public:
        explicit RecurrentItemNameFactory(QString const& templateString)
            : templateString(templateString) {};
        RecurrentItemNameFactory() = delete;

        ~RecurrentItemNameFactory() = default;

        QString build(QDate const& date) const;

    private:
        QString const templateString;

};
