#include <QtWidgets>

#include "../../data/DbHandler.h"
#include "../../data/RecurrentItemTemplate.h"

#pragma once

class TemplateStore : public QAbstractTableModel
{
    public:
    TemplateStore(std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr)
        : m_ptr(ptr) {};

    QVariant data(QModelIndex const& idx, int role) const override
        {
            int const row = idx.row();

            QVariant var;

            int curRow = 0;
            auto it = m_ptr->begin();
            while (curRow++ != row) ++it;

            var.setValue(it->first);
            return var;
        };
    inline int rowCount(QModelIndex const&) const override { return m_ptr->size(); };
    inline int columnCount(QModelIndex const&) const override { return 1; };

    private:
    std::shared_ptr<std::map<QString, RecurrentItemTemplate>> m_ptr;
};

class SelectRecurrentItemTemplateDialog : public QDialog
{
    public:
        static std::shared_ptr<RecurrentItem> getTemplate();

        SelectRecurrentItemTemplateDialog(std::shared_ptr<std::map<QString, RecurrentItemTemplate>>);

    protected slots:
        void onRowInTableSelected(QItemSelection newSelection, QItemSelection oldSelection);

    private:
        TemplateStore store;
        std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr;
        QString curSelection;
};
