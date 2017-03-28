//
// Created by max on 03/10/16.
//

#include <QtSql/QSqlQuery>
#include <data/DbHandler.h>
#include "AddItemDialog.h"
#include "AddRecipientDialog.h"
#include "SearchRecipientDialog.h"

AddItemDialog::AddItemDialog(QWidget * parent, Qt::WindowFlags const& f)
: QDialog(parent, f)
{
    setWindowTitle(tr("Add item"));
    resize(500, 200);

    mainLayout = new QVBoxLayout;
    bottomLayout = new QHBoxLayout;

    addItemRow = new AddItemRow(this);

    recipientLabel = new QLabel("Recipient");
    selectOrAddRecipientButton = new SelectOrAddRecipientButton;

    dateEdit = new QCalendarWidget;

    ok = new QPushButton(tr("OK"));
    ok->setEnabled(false);
    cancel = new QPushButton(tr("Cancel"));
    bottomLayout->addWidget(this->cancel);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(this->ok);

    mainLayout->addWidget(addItemRow);
    mainLayout->addWidget(selectOrAddRecipientButton);
    mainLayout->addWidget(dateEdit);
    mainLayout->addItem(bottomLayout);

    this->setLayout(mainLayout);

    this->connect(this->cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->connect(this->ok, SIGNAL(clicked()), this, SLOT(onClickOkay()));

    /* check if can click okay when values here change */
    this->connect(this->addItemRow, SIGNAL(contentChanged()), this, SLOT(checkCanAddItem()));
    this->connect(this->selectOrAddRecipientButton, SIGNAL(selectedRecipientIdChanged()), this, SLOT(checkCanAddItem()));
}

AddItemDialog::~AddItemDialog()
{
    // do not manually delete members, Qt does that for us
}

void
AddItemDialog::onClickOkay()
{
    std::tuple<QString, QString, int> const values = addItemRow->getValues();

    QString const name = std::get<0>(values);
    if (name.isEmpty() || this->selectOrAddRecipientButton->getSelectedRecipientId() < 0)
    {
        return;
    }

    int const recipientId = this->selectOrAddRecipientButton->getSelectedRecipientId();
    int const categoryId = std::get<2>(values);
    QString const price = std::get<1>(values);
    QDate date = this->dateEdit->selectedDate();

    if (DbHandler::getInstance()->insertNewItem(name, recipientId, date, price, categoryId))
    {
        accept();
    }
}

void
AddItemDialog::checkCanAddItem()
{
    bool const b = (this->addItemRow->rowValid())
                && (this->selectOrAddRecipientButton->getSelectedRecipientId() >= 0);

    this->ok->setEnabled(b);
}
