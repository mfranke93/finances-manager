#include "ItemTemplateTableModel.h"

ItemTemplateTableModel::ItemTemplateTableModel(std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr)
{
    for (auto& it : *ptr) values.push_back(it.first);
}

Qt::ItemFlags 
ItemTemplateTableModel::flags(QModelIndex const& idx) const
{
    auto flags = QAbstractTableModel::flags(idx);
    flags &= ~Qt::ItemIsEditable;
    flags &= ~Qt::ItemIsUserCheckable;
    return flags;
}

QVariant 
ItemTemplateTableModel::data(QModelIndex const& idx, int role) const 
{
    if (role == Qt::DisplayRole)
    {
        QVariant var;
        size_t const row = static_cast<size_t>(idx.row());
        if (row < values.size()) var.setValue(values[row]);
        return var;
    }

    return QVariant();
}
