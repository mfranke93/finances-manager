//
// Created by max on 23/12/16.
//

#include <cmath>
#include <data/ResourceHandler.h>
#include "PriceColumnDelegate.h"

void
PriceColumnDelegate::paint(QPainter * painter, QStyleOptionViewItem const& option, QModelIndex const& index) const
{
    painter->save();

    qreal const val = index.data().toReal();
    bool neg = (val < 0.0);
    char buf [10];
    std::sprintf(buf, "%s%7.2f", neg?"-":" ", std::fabs(val));

    if (neg)
    {
        painter->setPen(ResourceHandler::getInstance()->getColor("negative numbers red"));
    }
    painter->drawText(option.rect, Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter ,QString(buf));
    painter->restore();
}
