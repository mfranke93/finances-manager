#include <QtWidgets>

#include "../../data/DbHandler.h"
#include "../../data/RecurrentItemTemplate.h"
#include "ItemTemplateTableModel.h"

#pragma once


class SelectRecurrentItemTemplateDialog : public QDialog
{
    public:
        static std::shared_ptr<RecurrentItem> getTemplate();

        SelectRecurrentItemTemplateDialog(std::shared_ptr<std::map<QString, RecurrentItemTemplate>>);

    protected slots:
        void onRowInTableSelected(QItemSelection newSelection, QItemSelection oldSelection);

    private:
        ItemTemplateTableModel store;
        std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr;
        QString curSelection;
};
