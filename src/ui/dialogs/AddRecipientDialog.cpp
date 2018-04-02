//
// Created by max on 05/10/16.
//

#include <iostream>
#include <data/DbHandler.h>
#include "AddRecipientDialog.h"

AddRecipientDialog::AddRecipientDialog(QWidget * /*parent*/, Qt::WindowFlags const& /*f*/)
{
    setWindowTitle(tr("Add recipient"));
    resize(300, 150);

    mainLayout = new QVBoxLayout;
    layout1 = new QHBoxLayout;
    layout2 = new QHBoxLayout;

    name = new QLineEdit;
    isOnline = new QCheckBox("online");
    layout1->addWidget(name, 6);
    layout1->addSpacing(5);
    layout1->addWidget(isOnline, 1);
    mainLayout->addItem(layout1);

    address = new QTextEdit;
    mainLayout->addWidget(address);

    cancel = new QPushButton("Cancel");
    ok = new QPushButton("Ok");
    layout2->addWidget(cancel);
    layout2->addStretch(1);
    layout2->addWidget(ok);
    mainLayout->addItem(layout2);

    setLayout(mainLayout);

    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ok, SIGNAL(clicked()), this, SLOT(onPressOkay()));
}

void
AddRecipientDialog::onPressOkay()
{
    QString const name = this->name->text();
    QString const address = this->address->document()->toPlainText();
    bool const isOnline = this->isOnline->isChecked();

    if (!DbHandler::getInstance()->insertNewRecipient(name, address, isOnline))
    {
        std::cerr << "Could not add recipient!" << std::endl;
        reject();
    }

    accept();
}
