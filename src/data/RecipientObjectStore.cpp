//
// Created by max on 13/01/17.
//

#include <QtSql/QSqlDatabase>
#include "RecipientObjectStore.h"
#include "DbHandler.h"

RecipientObjectStore::RecipientObjectStore()
{
    buildList();
    connect(DbHandler::getInstance(), SIGNAL(itemDataChanged()), this, SLOT(buildList()));
}

void
RecipientObjectStore::buildList()
{
    beginResetModel();
    mRecipients.clear();
    QSqlDatabase db = DbHandler::getInstance()->getDatabase();
    QSqlQuery query (db);
    query.prepare("SELECT id, name, address, online FROM Recipient ORDER BY lower(name), lower(address);");
    bool const b = query.exec();
    if (!b) return;
    while (query.next())
    {
        uint32_t const id = query.value("id").toUInt();
        QString const name = query.value("name").toString();
        QString const address = query.value("address").toString();
        bool const online = query.value("online").toBool();

        mRecipients.push_back(std::make_shared<RecipientObject>(id, name, address, online));
    }
    mSelectedRecipients = mRecipients;
    endResetModel();
}

void
RecipientObjectStore::search(QString searchTerm)
{
    beginResetModel();
    if (searchTerm.isEmpty()) mSelectedRecipients = mRecipients;
    else
    {
        QRegExp re (searchTerm, Qt::CaseSensitivity::CaseInsensitive, QRegExp::FixedString);
        mSelectedRecipients.clear();
        for (auto item : mRecipients)
        {
            if ((-1 != re.indexIn(item->name)) || (-1 != re.indexIn(item->address))) mSelectedRecipients.push_back(item);
        }
    }
    endResetModel();
}

QVariant
RecipientObjectStore::data(QModelIndex const& index, int role) const
{
    int const row = index.row();
    int const col = index.column();

    QVariant var;

    std::shared_ptr<RecipientObject> obj = mSelectedRecipients.at(row);
    switch (col)
    {
        case 0:
            var.setValue(obj->recipientId);
            break;
        case 1:
            var.setValue(obj->name);
            break;
        case 2:
            var.setValue(obj->address);
            break;
        case 3:
            var.setValue(obj->isOnline);
            break;
    }

    return var;
}
