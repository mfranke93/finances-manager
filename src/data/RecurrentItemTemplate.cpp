#include "RecurrentItemTemplate.h"

RecurrentItemTemplate::RecurrentItemTemplate( 
        std::list<QString> const& nameTemplates,
        QString const& dateTemplate,
        size_t const& recipientId,
        std::list<size_t> const& categoryIds,
        std::list<QString> const& prices)
: dateFactory(dateTemplate), recipientId(recipientId)
{
    // FIXME do not assert same-size lists
    auto nt = nameTemplates.cbegin();
    auto ci = categoryIds.cbegin();
    auto ps = prices.cbegin();

    while(nt != nameTemplates.cend())
    {
        RecurrentItemNameFactory f (*nt);
        size_t categoryId = *ci;
        QString price = *ps;

        auto tup = std::make_tuple(f, categoryId, price);

        subitemFactory.push_back(tup);

        ++nt; ++ci; ++ps;
    }
}

std::shared_ptr<RecurrentItem>
RecurrentItemTemplate::build(QDate const& date) const
{
    auto item = std::make_shared<RecurrentItem>();
    QDate const realdate = dateFactory.build(date);
    item->date = realdate;
    item->recipientId = recipientId;

    for (auto& it : subitemFactory)
    {
        RecurrentSubitem si;
        si.name = std::get<0>(it).build(realdate);   // use actual date here
        si.categoryId = std::get<1>(it);
        si.price = std::get<2>(it);

        item->subitems.push_back(si);
    }

    return item;
}

