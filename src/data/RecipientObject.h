//
// Created by max on 13/01/17.
//

#pragma once


#include <QtCore/QString>

struct RecipientObject
{
    uint32_t recipientId;
    QString name;
    QString address;
    bool isOnline;

    RecipientObject(uint32_t const& recipientId, QString const& name, QString const& address, bool const& isOnline)
    : recipientId(recipientId), name(name), address(address), isOnline(isOnline) {};
};



