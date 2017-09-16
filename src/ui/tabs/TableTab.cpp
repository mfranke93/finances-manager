//
// Created by max on 06/10/16.
//

#include "TableTab.h"

TableTab::TableTab(QWidget * parent)
: QWidget(parent)
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
    this->createFromTemplate = new QPushButton(tr("Create from template"));
    bottom->addWidget(this->createFromTemplate);
    lay->addItem(bottom);
    this->setLayout(lay);

    this->connect(this->reload, SIGNAL(clicked()), this->table, SLOT(onPressReload()) );
    this->connect(this->create, SIGNAL(clicked()), SLOT(onPressCreate()));
    connect(createFromTemplate, &QPushButton::clicked, this, &TableTab::onPressCreateFromTemplate);
    this->connect(DbHandler::getInstance(), SIGNAL(itemDataChanged()), this->table, SLOT(onPressReload()));
}


TableTab::~TableTab()
{
    if (this->table != nullptr)
        delete this->table;
}

void
TableTab::onPressCreate()
{
    std::shared_ptr<RecurrentItem> dummy;
    showAddItemDialog(dummy);
}

void
TableTab::onPressCreateFromTemplate()
{
    auto temp = SelectRecurrentItemTemplateDialog::getTemplate();
    if (temp) showAddItemDialog(temp);
}

void
TableTab::showAddItemDialog(std::shared_ptr<RecurrentItem> recurrent)
{
    DbHandler::getInstance()->getDatabase().transaction();
    AddItemDialog d (this, Qt::Dialog);
    if (recurrent) d.populate(std::move(recurrent));
    d.setModal(true);
    d.show();
    d.onNeedResize();
    d.exec();

    int result = d.result();
    if (result == QDialog::Accepted)
    {
        if (!DbHandler::getInstance()->commit())
        {
            std::fprintf(stderr, "Could not commit to %s\n%s",
                         DbHandler::getInstance()->getDatabase().connectionName().toStdString().c_str(),
                         DbHandler::getInstance()->getDatabase().lastError().text().toStdString().c_str());
        }
    }
    else if (result == QDialog::Rejected)
    {
        // rollback
        if (!DbHandler::getInstance()->getDatabase().rollback())
        {
            std::fprintf(stderr, "Could not rollback %s\n",
                         DbHandler::getInstance()->getDatabase().connectionName().toStdString().c_str());
        }
    }
    else
    {
        std::fprintf(stderr, "Unknown result value: %d\n", result);
    }
}

