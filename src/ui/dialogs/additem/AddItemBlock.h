//
// Created by max on 28/03/17.
//

#pragma once


#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include "AddItemRow.h"

class AddItemBlock : public QWidget
{
    Q_OBJECT
public:
    AddItemBlock();
    ~AddItemBlock() = default;

    bool allRowsValid() const;
    std::vector<std::tuple<QString, QString, int>> getAllContents() const;

    void populate(QString const&, QString const&, int const&);

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



