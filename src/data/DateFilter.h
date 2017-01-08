//
// Created by max on 01/12/16.
//

#pragma once


#include <QtCore/QObject>

class DateFilter: public QObject
{
public:
    virtual bool contains(QDate const&) const = 0;
    virtual QString asSqlWhere(QString const&) const = 0;
signals:
    void changed();
};



