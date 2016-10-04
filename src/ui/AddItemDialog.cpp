//
// Created by max on 03/10/16.
//

#include <QtSql/QSqlQuery>
#include "AddItemDialog.h"

AddItemDialog::AddItemDialog(QWidget * parent, Qt::WindowFlags const& f)
: QDialog(parent, f)
{
    setWindowTitle(tr("Test"));
    resize(500, 200);

    mainLayout = new QVBoxLayout;
    itemLayout = new QHBoxLayout;
    itemName = new QLineEdit;
    itemLayout->addWidget(itemName);
    category = new QComboBox;
    itemLayout->addWidget(category);
    recipient = new QComboBox;
    itemLayout->addWidget(recipient);
    mainLayout->addItem(itemLayout);
    dateEdit = new QCalendarWidget;
    mainLayout->addWidget(dateEdit);

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));
    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(this->cancel);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(this->ok);
    mainLayout->addItem(bottomLayout);

    this->setLayout(mainLayout);

    this->connect(this->cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->connect(this->ok, SIGNAL(clicked()), this, SLOT(accept()));

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
    query.exec();

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

    QSqlQuery query ("SELECT id, name FROM Recipient;");
    query.exec();

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();

        this->recipient->addItem(name, QVariant(id));
    }
}