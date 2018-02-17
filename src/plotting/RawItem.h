#include <QtCore>

#pragma once

struct RawItem
{
    QDate           date;
    uint32_t        recipientId;
    uint32_t        categoryId;
    double          price;
};

