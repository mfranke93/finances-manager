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
    setMinimumSize(500, 200);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::MinimumExpanding);

    mainLayout = new QVBoxLayout;
    bottomLayout = new QHBoxLayout;

    addItemBlock = new AddItemBlock;
    addItemBlock->setParent(this);

    recipientLabel = new QLabel("Recipient");
    selectOrAddRecipientButton = new SelectOrAddRecipientButton;

    dateEdit = new QCalendarWidget;
    dateEdit->setMinimumSize(480, 150);
    dateEdit->setParent(this);

    ok = new QPushButton(tr("OK"));
    ok->setEnabled(false);
    cancel = new QPushButton(tr("Cancel"));
    bottomLayout->addWidget(this->cancel);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(this->ok);

    mainLayout->addWidget(addItemBlock);
    mainLayout->addWidget(selectOrAddRecipientButton);
    mainLayout->addWidget(dateEdit);
    mainLayout->addItem(bottomLayout);

    this->setLayout(mainLayout);

    this->connect(this->cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->connect(this->ok, SIGNAL(clicked()), this, SLOT(onClickOkay()));

    /* check if can click okay when values here change */
    this->connect(this->addItemBlock, SIGNAL(contentChanged()), this, SLOT(checkCanAddItem()));
    this->connect(this->selectOrAddRecipientButton, SIGNAL(selectedRecipientIdChanged()), this, SLOT(checkCanAddItem()));

    this->connect(this->addItemBlock, SIGNAL(dialogNeedsResize()), this, SLOT(onNeedResize()));
}

AddItemDialog::~AddItemDialog()
{
    // do not manually delete members, Qt does that for us
}

void
AddItemDialog::onClickOkay()
{
    bool success;

    for (std::tuple<QString, QString, int> const& values : addItemBlock->getAllContents())
    {
        QString const name = std::get<0>(values);
        if (name.isEmpty() || this->selectOrAddRecipientButton->getSelectedRecipientId() < 0)
        {
            std::fprintf(stderr, "Name empty or no recipient selected:\n%s, %d.\n",
                    name.toStdString().c_str(), selectOrAddRecipientButton->getSelectedRecipientId());
            return;
        }

        int const recipientId = this->selectOrAddRecipientButton->getSelectedRecipientId();
        int const categoryId = std::get<2>(values);
        QString const price = std::get<1>(values);
        QDate date = this->dateEdit->selectedDate();

        success = DbHandler::getInstance()->insertNewItem(name, recipientId, date, price, categoryId);
        if (!success) reject();
    }
    accept();
}

void
AddItemDialog::checkCanAddItem()
{
    bool const b = (this->addItemBlock->allRowsValid())
                && (this->selectOrAddRecipientButton->getSelectedRecipientId() >= 0);

    this->ok->setEnabled(b);
}

void
AddItemDialog::onNeedResize()
{
    resize(sizeHint());
}

void
AddItemDialog::populate(std::unique_ptr<RecurrentItem>&& recurrent)
{
    if (recurrent)
    {
        addItemBlock->populate(recurrent->name, recurrent->price, recurrent->categoryId);
        dateEdit->setSelectedDate(recurrent->date);
        selectOrAddRecipientButton->setSelectedRecipientId(recurrent->recipientId);

        checkCanAddItem();
    }
    else
    {
        std::fprintf(stderr, "populate() called with non-active unique_ptr!\n");
    }
}
