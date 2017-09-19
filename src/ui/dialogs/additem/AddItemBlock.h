//
// Created by max on 28/03/17.
//

#pragma once


#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "AddItemRow.h"
#include "../../../data/RecurrentItemTemplate.h"

class AddItemBlock : public QWidget
{
    Q_OBJECT
public:
    AddItemBlock();
    ~AddItemBlock() = default;

    bool allRowsValid() const;
    std::vector<std::tuple<QString, QString, int>> getAllContents() const;

    void populate(std::list<RecurrentSubitem> const& lstSubs);

protected slots:
    void newRow();
    void childContentChanged();

signals:
    void contentChanged();
    void dialogNeedsResize();

private:
    QVBoxLayout * mainLayout;
    QVBoxLayout * rowLayout;
    std::vector<AddItemRow *> rows;
    QPushButton * addRowButton;
};



