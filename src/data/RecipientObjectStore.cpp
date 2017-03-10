//
// Created by max on 13/01/17.
//

#include <QtSql/QSqlDatabase>
#include "RecipientObjectStore.h"
#include "DbHandler.h"

RecipientObjectStore::RecipientObjectStore()
{
    buildList();
}

void
RecipientObjectStore::buildList()
{
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

    std::printf("%d items in list.\n", mRecipients.size());

}

void
RecipientObjectStore::search(QString searchTerm)
{
    if (searchTerm.isEmpty()) mSelectedRecipients = mRecipients;
    mSelectedRecipients = mRecipients;
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
