//
// Created by max on 10/01/17.
//

#include <QtWidgets/QTableView>
#include "SearchRecipientDialog.h"

SearchRecipientDialog::SearchRecipientDialog()
{
    toplevelLayout = new QVBoxLayout;
    searchbarLayout = new QHBoxLayout;
    addOkayLayout = new QHBoxLayout;

    searchBar = new QLineEdit;
    searchButton = new QPushButton("Search");

    searchResultScrollView = new QScrollArea;

    cancelButton = new QPushButton("Cancel");
    addButton = new QPushButton("Add");
    okayButton = new QPushButton("Okay");

    toplevelLayout->addItem(searchbarLayout);
    toplevelLayout->addWidget(searchResultScrollView);
    toplevelLayout->addItem(addOkayLayout);

    searchbarLayout->addWidget(searchBar, 5);
    searchbarLayout->addWidget(searchButton, 1);

    addOkayLayout->addWidget(cancelButton);
    addOkayLayout->addStretch(1);
    addOkayLayout->addWidget(addButton);
    addOkayLayout->addStretch(1);
    addOkayLayout->addWidget(okayButton);

    setLayout(toplevelLayout);
    setMinimumSize(400, 600);
    setWindowTitle("Find recipient");

    okayButton->setEnabled(false);
    searchButton->setEnabled(false);

    /* Signals */
    connect(searchButton, SIGNAL(clicked()), this, SLOT(onClickSearch()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onClickCancel()));
    connect(okayButton, SIGNAL(clicked()), this, SLOT(onClickOkay()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(onClickAdd()));
    // TODO selected index change
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
    // TODO
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
SearchRecipientDialog::onClickSearch()
{
    // TODO
    store.search(searchBar->text());
    QTableView * view = new QTableView;
    view->setModel(&store);
    searchResultScrollView->setViewport(view);
    view->setColumnHidden(0, true);
    view->setColumnHidden(3, true);
    view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    view->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    view->setShowGrid(false);
    view->horizontalHeader()->setVisible(false);
    view->verticalHeader()->setVisible(false);
    view->resizeColumnsToContents();
    view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    repaint();
}

void
SearchRecipientDialog::recipientIdChanged(int recid)
{
    this->_recId = recid;

    this->okayButton->setEnabled(recid>=0);
}

void
SearchRecipientDialog::searchBarContentChanged(QString content)
{
    // TODO update filtering

    this->searchButton->setEnabled(!content.isEmpty());
}
