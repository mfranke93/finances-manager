//
// Created by max on 11/03/17.
//

#include <ui/dialogs/SearchRecipientDialog.h>
#include <data/DbHandler.h>
#include "SelectOrAddRecipientButton.h"

SelectOrAddRecipientButton::SelectOrAddRecipientButton()
{
    setText("Click to select recipient");
    setStyleSheet("color: grey; frame: none;");
    setFlat(true);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClick()));
}

void
SelectOrAddRecipientButton::onClick()
{
    SearchRecipientDialog srd;
    srd.exec();

    if ((mSelectedRecipientId = srd.getSelectedRecId()) >= 0)
    {
        // turn black
        setText(DbHandler::getInstance()->getRecipientStringFromId(mSelectedRecipientId));
        setStyleSheet("color: black; frame: none;");
    }
    else
    {
        setText("Click to select recipient");
        setStyleSheet("color: grey; frame: none;");
    }

    emit selectedRecipientIdChanged();
}
