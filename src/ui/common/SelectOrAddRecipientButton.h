//
// Created by max on 11/03/17.
//

#pragma once


#include <QtWidgets/QPushButton>

class SelectOrAddRecipientButton : public QPushButton
{
    Q_OBJECT
public:
    SelectOrAddRecipientButton();
    ~SelectOrAddRecipientButton() = default;

    inline int const& getSelectedRecipientId() const { return mSelectedRecipientId; };

    void setSelectedRecipientId(int const& recId);

signals:
    void selectedRecipientIdChanged();

protected slots:
    void onClick();

private:
    int mSelectedRecipientId = -1;
};



