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
    query.prepare("SELECT Recipient.id AS RecipientId, "
                        "Recipient.name AS RecipientName, "
                        "Recipient.address AS RecipientAddress, "
                        "Recipient.online AS RecipientOnline, "
                        "COUNT(*) AS times_visited "
                        "FROM Recipient "
                        "LEFT JOIN Item ON Item.recid = Recipient.id "
                        "GROUP BY Recipient.id "
                        "ORDER BY times_visited DESC;");

    bool const b = query.exec();
    if (!b)
    {
        std::cerr << query.lastError().text().toStdString() << std::endl;
        return;
    }
    while (query.next())
    {
        uint32_t const id = query.value("RecipientId").toUInt();
        QString const name = query.value("RecipientName").toString();
        QString const address = query.value("RecipientAddress").toString();
        bool const online = query.value("RecipientOnline").toBool();

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
RecipientObjectStore::data(QModelIndex const& index, int /*role*/) const
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
