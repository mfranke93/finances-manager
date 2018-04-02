//
// Created by max on 10/01/17.
//

#include <QtWidgets/QTableView>
#include <ui/delegates/RecipientNameDelegate.h>
#include <ui/delegates/RecipientAddressDelegate.h>
#include <data/DbHandler.h>
#include "SearchRecipientDialog.h"
#include "AddRecipientDialog.h"

SearchRecipientDialog::SearchRecipientDialog()
{
    toplevelLayout = new QVBoxLayout;
    addOkayLayout = new QHBoxLayout;

    searchBar = new QLineEdit;

    searchResultScrollView = new QScrollArea;

    cancelButton = new QPushButton("Cancel");
    addButton = new QPushButton("Add");
    okayButton = new QPushButton("Okay");

    toplevelLayout->addWidget(searchBar);
    toplevelLayout->addWidget(searchResultScrollView);
    toplevelLayout->addItem(addOkayLayout);

    addOkayLayout->addWidget(cancelButton);
    addOkayLayout->addStretch(1);
    addOkayLayout->addWidget(addButton);
    addOkayLayout->addStretch(1);
    addOkayLayout->addWidget(okayButton);

    setLayout(toplevelLayout);
    setMinimumSize(600, 600);
    setWindowTitle("Find recipient");

    okayButton->setEnabled(false);

    /* Search result table */
    searchResultTable = new QTableView;
    searchResultTable->setModel(&store);
    searchResultTable->setColumnHidden(0, true);
    searchResultTable->setColumnHidden(3, true);
    searchResultTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    searchResultTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    searchResultTable->setShowGrid(false);
    searchResultTable->horizontalHeader()->setVisible(false);
    searchResultTable->verticalHeader()->setVisible(false);
    searchResultTable->resizeColumnsToContents();
    searchResultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    searchResultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    searchResultTable->setItemDelegateForColumn(1, new RecipientNameDelegate);
    searchResultTable->setItemDelegateForColumn(2, new RecipientAddressDelegate);
    searchResultTable->setAlternatingRowColors(true);
    searchResultScrollView->setViewport(searchResultTable);

    /* Signals */
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onClickCancel()));
    connect(okayButton, SIGNAL(clicked()), this, SLOT(onClickOkay()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    connect(this, SIGNAL(okayButtonEnabled(bool)), okayButton, SLOT(setEnabled(bool)));
    connect(searchResultTable->selectionModel(), SIGNAL(selectionChanged(QItemSelection const&, QItemSelection const&)),
            SLOT(onRowInTableSelected(QItemSelection const&, QItemSelection const&)));
    connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(searchBarContentChanged(QString)));
}

void
SearchRecipientDialog::onClickCancel()
{
    this->reject();
}

void
SearchRecipientDialog::onClickAdd()
{
    AddRecipientDialog d (this, Qt::Dialog);
    d.setModal(true);
    d.exec();

    int const result = d.result();

    if (result == QDialog::Accepted)
    {
        // we do not even need to do anything here
        // because the object store reloads after
        // the db is changed.

        // TODO: set added as selected
    }
    else if (result == QDialog::Rejected)
    {
    }
    else
    {
        std::cerr << "Undefined result state for QDialog: " << result << std::endl;
    }

    // reset search
    searchBar->clear();
}

void
SearchRecipientDialog::onClickOkay()
{
    if (_recId >= 0)
    {
        this->accept();
    }
    else
    {
        std::fprintf(stderr, "No recipient selected. Button should not be clickable.");
    }
}

void
SearchRecipientDialog::recipientIdChanged(int recid)
{
    this->_recId = recid;

    emit okayButtonEnabled(recid>=0);
}

void
SearchRecipientDialog::searchBarContentChanged(QString content)
{
    store.search(content);
    searchResultTable->resizeColumnsToContents();
    searchResultTable->repaint();
    recipientIdChanged(-1);
}

void
SearchRecipientDialog::onRowInTableSelected(QItemSelection const& newSelection, QItemSelection const& /*oldSelection*/)
{
    recipientIdChanged(newSelection.indexes().front().data().toInt());
}
