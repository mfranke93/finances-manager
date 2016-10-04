//
// Created by max on 03/10/16.
//


#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <memory>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCalendarWidget>

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    AddItemDialog(QWidget * parent, Qt::WindowFlags const& f);
    ~AddItemDialog();

public slots:
    void rebuildCategoryContents();
    void rebuildRecipientContents();

private:
    QLineEdit * itemName;

    QComboBox * category;
    QComboBox * recipient;
    QCalendarWidget * dateEdit;

    QPushButton * ok;
    QPushButton * cancel;

    QVBoxLayout * mainLayout;
    QHBoxLayout * itemLayout;
    QHBoxLayout * bottomLayout;
};


