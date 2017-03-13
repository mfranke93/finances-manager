//
// Created by max on 11/03/17.
//

#include <data/ResourceHandler.h>
#include "RecipientNameDelegate.h"

void
RecipientNameDelegate::paint(QPainter * painter, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    painter->save();

    QString const str = index.data().toString();
    painter->setFont(ResourceHandler::getInstance()->getRecipientNameFont());
    painter->setPen(QColor("black"));
    painter->drawText(option.rect.adjusted(0, 0, -5, 0), Qt::AlignmentFlag::AlignVCenter | Qt::AlignmentFlag::AlignRight,
            str);

    painter->restore();
}
