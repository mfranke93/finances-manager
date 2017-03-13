//
// Created by max on 11/03/17.
//

#include <data/ResourceHandler.h>
#include "RecipientAddressDelegate.h"

void
RecipientAddressDelegate::paint(QPainter * painter, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    painter->save();

    QString const str = index.data().toString();
    painter->setFont(ResourceHandler::getInstance()->getRecipientAddressFont());
    painter->setPen(QColor("black"));
    painter->drawText(option.rect.adjusted(5, 0, 0, 0), Qt::AlignmentFlag::AlignVCenter | Qt::AlignmentFlag::AlignLeft,
                      str);

    painter->restore();
}
