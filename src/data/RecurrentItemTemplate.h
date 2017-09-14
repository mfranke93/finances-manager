#include <QtCore>
#include "DateFactory.h"
#include "RecurrentItemNameFactory.h"

#pragma once

struct RecurrentItem
{
    QString name;
    QDate date;
    size_t recipientId;
    size_t categoryId;
    QString price;
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
        RecurrentItemTemplate(QString const& nameTemplate,
                QString const& dateTemplate,
                size_t const& recipientId,
                size_t const& categoryId,
                QString const& price)
            : nameFactory(nameTemplate),
              dateFactory(dateTemplate),
              recipientId(recipientId),
              categoryId(categoryId),
              price(price) {};
        ~RecurrentItemTemplate() = default;
        RecurrentItemTemplate(RecurrentItemTemplate const&) = default;
        RecurrentItemTemplate& operator= (RecurrentItemTemplate const&) = default;

        RecurrentItem build(QDate const& date) const;

    private:
        RecurrentItemNameFactory const nameFactory;;
        DateFactory const dateFactory;
        size_t  const recipientId;
        size_t const categoryId;
        QString const price;
};
