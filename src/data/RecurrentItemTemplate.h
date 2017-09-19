#include <QtCore>
#include "DateFactory.h"
#include "RecurrentItemNameFactory.h"

#pragma once

struct RecurrentSubitem
{
    RecurrentSubitem() : name(""), categoryId(0), price("0.00") {};
    RecurrentSubitem(RecurrentSubitem const& other)
        : name(other.name), categoryId(other.categoryId), price(other.price) {};
    RecurrentSubitem(RecurrentSubitem&& other)
        : name(other.name), categoryId(other.categoryId), price(other.price) {};
    QString name;
    size_t categoryId;
    QString price;
};

struct RecurrentItem
{
    RecurrentItem() : date(QDate()), recipientId(0), subitems() {};
    RecurrentItem(RecurrentItem const&) = delete;
    RecurrentItem(RecurrentItem&&) = delete;
    QDate date;
    size_t recipientId;
    std::list<RecurrentSubitem> subitems;
};

/**
 * Recurrent item templates need these fields:
 *  - Templated name (for example with %m field)
 *  - Date that gets created by some rule (template string in db?)
 *  - RecipientId
 *  - Price
 */
class RecurrentItemTemplate
{
    public:
        RecurrentItemTemplate(std::list<QString> const& nameTemplate,
                QString const& dateTemplate,
                size_t const& recipientId,
                std::list<size_t> const& categoryId,
                std::list<QString> const& price);
        ~RecurrentItemTemplate() = default;
        RecurrentItemTemplate(RecurrentItemTemplate const&) = default;
        RecurrentItemTemplate& operator= (RecurrentItemTemplate const&) = default;

        std::shared_ptr<RecurrentItem> build(QDate const& date) const;

    private:
        DateFactory const dateFactory;
        size_t  const recipientId;
        std::list<std::tuple<
            RecurrentItemNameFactory,
            size_t,
            QString
                >> subitemFactory;
};
