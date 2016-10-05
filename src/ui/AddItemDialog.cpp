//
// Created by max on 03/10/16.
//

#include <QtSql/QSqlQuery>
#include <data/DbHandler.h>
#include "AddItemDialog.h"

AddItemDialog::AddItemDialog(QWidget * parent, Qt::WindowFlags const& f)
: QDialog(parent, f)
{
    setWindowTitle(tr("Test"));
    resize(500, 200);

    mainLayout = new QVBoxLayout;
    lineEditLayout = new QHBoxLayout;
    recipientCategoryLayout = new QGridLayout;
    bottomLayout = new QHBoxLayout;

    itemName = new QLineEdit;
    price = new QLineEdit;
    price->setValidator(new QDoubleValidator(-10000, 10000, 2));
    lineEditLayout->addWidget(itemName, 10);
    lineEditLayout->addWidget(price, 1);

    recipientLabel = new QLabel("Recipient");
    recipient = new QComboBox;
    newRecipient = new QPushButton("+");
    newRecipient->setMaximumWidth(30);
    recipientCategoryLayout->addWidget(recipientLabel, 0, 0);
    recipientCategoryLayout->addWidget(recipient, 0, 1);
    recipientCategoryLayout->addWidget(newRecipient, 0, 2);

    categoryLabel = new QLabel("Category");
    category = new QComboBox;
    newCategory = new QPushButton("+");
    newCategory->setMaximumWidth(30);
    recipientCategoryLayout->addWidget(categoryLabel, 1, 0);
    recipientCategoryLayout->addWidget(category, 1, 1);
    recipientCategoryLayout->addWidget(newCategory, 1, 2);

    recipientCategoryLayout->setHorizontalSpacing(5);

    dateEdit = new QCalendarWidget;

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    bottomLayout->addWidget(this->cancel);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(this->ok);

    mainLayout->addItem(lineEditLayout);
    mainLayout->addItem(recipientCategoryLayout);
    mainLayout->addWidget(dateEdit);
    mainLayout->addItem(bottomLayout);

    this->setLayout(mainLayout);

    this->connect(this->cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->connect(this->ok, SIGNAL(clicked()), this, SLOT(onClickOkay()));

    this->rebuildCategoryContents();
    this->rebuildRecipientContents();
}

AddItemDialog::~AddItemDialog()
{
    // do not manually delete members, Qt does that for us
}

void
AddItemDialog::rebuildCategoryContents()
{
    this->category->clear();

    QSqlQuery query ("SELECT id, name FROM Category;");
    DbHandler::getInstance()->getDatabase().exec();

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();

        this->category->addItem(name, QVariant(id));
    }
}

void
AddItemDialog::rebuildRecipientContents()
{
    this->recipient->clear();

    QSqlQuery query ("SELECT id, name, address FROM Recipient;");
    DbHandler::getInstance()->getDatabase().exec();

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString address = query.value("address").toString();
        if (!address.isEmpty())
        {
            name += "\n" + address;
            name.replace("\n", ", ");
        }

        this->recipient->addItem(name, QVariant(id));
    }
}

void
AddItemDialog::onClickOkay()
{
    QString const name = this->itemName->text();
    if (name.isEmpty())
    {
        return;
    }

    int const recipientId = this->recipient->currentData().toInt();
    int const categoryId = this->category->currentData().toInt();
    QString const price = this->price->text();
    QDate date = this->dateEdit->selectedDate();

    if (DbHandler::getInstance()->insertNewItem(name, recipientId, date, price, categoryId))
    {
        accept();
    }
}