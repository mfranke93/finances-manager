//
// Created by max on 06/10/16.
//


#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "data/DbHandler.h"

class AddCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    AddCategoryDialog(QWidget * parent, Qt::WindowFlags const& f);
    ~AddCategoryDialog() = default;

protected slots:
    void onClickOkay();

private:
    QLineEdit * name;
    QPushButton * cancel;
    QPushButton * ok;

    QVBoxLayout * mainLayout;
    QHBoxLayout * bottomLayout;
};


