#include <QtWidgets>

#include "../../data/RecurrentItemTemplate.h"

#pragma once

class ItemTemplateTableModel : public QAbstractTableModel
{
    public:
        ItemTemplateTableModel(std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr);

        Qt::ItemFlags flags(QModelIndex const&) const override;
        QVariant data(QModelIndex const& idx, int role) const override;
        int rowCount(QModelIndex const&) const override { return values.size(); };
        int columnCount(QModelIndex const&) const override { return 1; };

    private:
        std::vector<QString> values;
};
