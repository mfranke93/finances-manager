//
// Created by max on 06/10/16.
//

#include "AddCategoryDialog.h"

AddCategoryDialog::AddCategoryDialog(QWidget * parent, Qt::WindowFlags const& f)
{
    setWindowTitle(tr("Add category"));
    //resize(200, 80);

    mainLayout = new QVBoxLayout;
    bottomLayout = new QHBoxLayout;

    name = new QLineEdit;
    mainLayout->addWidget(name);

    cancel = new QPushButton("Cancel");
    bottomLayout->addWidget(cancel);

    bottomLayout->addStretch(1);

    ok = new QPushButton("OK");
    bottomLayout->addWidget(ok);

    mainLayout->addItem(bottomLayout);
    setLayout(mainLayout);

    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ok, SIGNAL(clicked()), this, SLOT(onClickOkay()));
}

void
AddCategoryDialog::onClickOkay()
{
    QString const name = this->name->text();

    if (!DbHandler::getInstance()->insertNewCategory(name))
    {
        std::cerr << "Could not add category!" << std::endl;
        reject();
    }

    accept();
}