//
// Created by max on 11/03/17.
//

#pragma once


#include <QtWidgets/QStyledItemDelegate>
#include <QPainter>

class RecipientNameDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter * painter, QStyleOptionViewItem const& option, QModelIndex const& index) const override;
};



