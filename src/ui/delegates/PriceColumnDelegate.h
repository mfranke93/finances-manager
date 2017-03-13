//
// Created by max on 23/12/16.
//

#pragma once

#include <QtWidgets/QAbstractItemDelegate>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QStyledItemDelegate>
#include <QPainter>

class PriceColumnDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter * painter, QStyleOptionViewItem const& option, QModelIndex const& index) const override;

};



