#include "SelectRecurrentItemTemplateDialog.h"

SelectRecurrentItemTemplateDialog::SelectRecurrentItemTemplateDialog(std::shared_ptr<std::map<QString, RecurrentItemTemplate>> ptr)
: QDialog(nullptr, Qt::Dialog), store(ptr), ptr(ptr)
{
    auto layout = new QVBoxLayout;
    auto scroll = new QScrollArea;

    auto table = new QTableView;
    table->setModel(&store);
    table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    table->setShowGrid(false);
    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->resizeColumnsToContents();
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->setAlternatingRowColors(true);
    scroll->setViewport(table);

    layout->addWidget(scroll);

    auto cancelLayout = new QHBoxLayout;
    auto cancelButton = new QPushButton;
    cancelButton->setText("Cancel");
    cancelLayout->addWidget(cancelButton, 1);
    cancelLayout->addStretch(1);
    layout->addItem(cancelLayout);

    setLayout(layout);

    setMinimumSize(300, 400);

    setWindowTitle("Select recurrent item template");

    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SelectRecurrentItemTemplateDialog::onRowInTableSelected);
    connect(cancelButton, &QPushButton::clicked,
            this, &SelectRecurrentItemTemplateDialog::reject);
}

std::shared_ptr<RecurrentItem>
SelectRecurrentItemTemplateDialog::getTemplate()
{
    auto templateMap = DbHandler::getInstance()->getRecurringTemplates();
    SelectRecurrentItemTemplateDialog d (templateMap);
    d.setModal(true);
    d.exec();

    int const result = d.result();
    if (result == QDialog::Accepted)
    {
        RecurrentItemTemplate t = d.ptr->at(d.curSelection);
        return t.build(QDate::currentDate());
    }

    return std::shared_ptr<RecurrentItem>();
}


void
SelectRecurrentItemTemplateDialog::onRowInTableSelected(QItemSelection newSelection, QItemSelection /*oldSelection*/)
{
    curSelection = newSelection.indexes().front().data().toString();
    accept();
}
