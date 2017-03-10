//
// Created by max on 13/01/17.
//

#pragma once


#include <vector>
#include <memory>
#include <QtCore/QAbstractItemModel>
#include "RecipientObject.h"

class RecipientObjectStore : public QAbstractTableModel
{
public:
    RecipientObjectStore();
    ~RecipientObjectStore() = default;

    void search(QString searchTerm);

    QVariant data(QModelIndex const&, int) const override;
    inline int rowCount(QModelIndex const&) const override { return mSelectedRecipients.size(); };
    inline int columnCount(QModelIndex const&) const override { return 4; };

protected:
    void buildList();

private:
    std::vector<std::shared_ptr<RecipientObject>> mRecipients;
    std::vector<std::shared_ptr<RecipientObject>> mSelectedRecipients;
};



