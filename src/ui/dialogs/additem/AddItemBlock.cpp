//
// Created by max on 28/03/17.
//

#include "AddItemBlock.h"

AddItemBlock::AddItemBlock()
: QWidget()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(1);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout = new QVBoxLayout;
    rowLayout->setSpacing(1);
    rowLayout->setContentsMargins(0, 0, 0, 0);

    AddItemRow * row = new AddItemRow(this);
    rowLayout->addWidget(row);
    rows.push_back(row);

    addRowButton = new QPushButton("+");
    addRowButton->setMaximumWidth(20);
    QHBoxLayout * layout1 = new QHBoxLayout;
    layout1->addWidget(addRowButton, 1);
    layout1->addStretch(9);

    mainLayout->addItem(rowLayout);
    mainLayout->addItem(layout1);

    setLayout(mainLayout);

    connect(addRowButton, SIGNAL(clicked()), this, SLOT(newRow()));
    connect(row, SIGNAL(contentChanged()), this, SLOT(childContentChanged()));
}

bool
AddItemBlock::allRowsValid() const
{
    auto func = [](AddItemRow * row) -> bool { return row->rowValid(); };
    return std::all_of(rows.begin(), rows.end(), func);
}

void
AddItemBlock::newRow()
{
    AddItemRow * row = new AddItemRow(this);
    rowLayout->addWidget(row);
    rows.push_back(row);
    row->show();
    connect(row, SIGNAL(contentChanged()), this, SLOT(childContentChanged()));
    emit contentChanged();
    emit dialogNeedsResize();
}

void
AddItemBlock::childContentChanged()
{
    emit contentChanged();
}

std::vector<std::tuple<QString, QString, int>>
AddItemBlock::getAllContents() const
{
    std::vector<std::tuple<QString, QString, int>> vec;
    for (auto const& row : rows) vec.push_back(row->getValues());
    return vec;
}
