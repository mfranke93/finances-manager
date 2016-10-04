//
// Created by max on 30/09/16.
//

#include <QtWidgets/QHBoxLayout>
#include "main_window.h"
#include "AddItemDialog.h"

MainWindow::MainWindow()
{
    QVBoxLayout * lay = new QVBoxLayout;
    QHBoxLayout * bottom = new QHBoxLayout;
    this->table = new ExpenditureView;
    lay->addWidget(this->table);
    this->reload=new QPushButton(tr("Reload"));
    bottom->addWidget(this->reload);
    bottom->addStretch(1);
    this->create = new QPushButton(tr("Create"));
    bottom->addWidget(this->create);
    lay->addItem(bottom);
    this->setLayout(lay);

    this->connect(this->reload, SIGNAL(clicked()), this->table, SLOT(onPressReload()) );
    this->connect(this->create, SIGNAL(clicked()), SLOT(onPressCreate()));
}

MainWindow::~MainWindow()
{
    if (this->table != nullptr)
        delete this->table;
}

void
MainWindow::onPressCreate()
{
    AddItemDialog d (this, Qt::Dialog);
    d.setModal(true);
    d.exec();

    int result = d.result();
    if (result == QDialog::Accepted)
    {
        // TODO: make dbhandler class
        // do the thing
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        if (!db.commit())
        {
            fprintf(stderr, "Could not commit to %s\n", db.connectionName().toStdString().c_str());
        }
    }
    else if (result == QDialog::Rejected)
    {
        // rollback
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        if (!db.rollback())
        {
            fprintf(stderr, "Could not rollback %s\n", db.connectionName().toStdString().c_str());
        }
    }
    else
    {
        printf("Unknown result value: %d\n", result);
    }
}
