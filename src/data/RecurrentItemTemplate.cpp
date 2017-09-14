#include "RecurrentItemTemplate.h"

RecurrentItem
RecurrentItemTemplate::build(QDate const& date) const
{
    RecurrentItem item;
    item.date = dateFactory.build(date);
    item.name = nameFactory.build(item.date);   // use actual date here
    item.recipientId = recipientId;
    item.categoryId = categoryId;
    item.price = price;

    return item;
}

