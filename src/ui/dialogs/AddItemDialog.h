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
#include <QtWidgets/QLabel>
#include <QtSql/QSqlError>

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    AddItemDialog(QWidget * parent, Qt::WindowFlags const& f);
    ~AddItemDialog();

public slots:
    void rebuildCategoryContents();
    void rebuildRecipientContents();
    void onClickOkay();
    void onClickAddRecipient();
    void onClickAddCategory();

private:
    QLineEdit * itemName;
    QLineEdit * price;

    QLabel * recipientLabel;
    QLabel * categoryLabel;

    QComboBox * category;
    QComboBox * recipient;

    QCalendarWidget * dateEdit;

    QPushButton * ok;
    QPushButton * cancel;
    QPushButton * newRecipient;
    QPushButton * newCategory;

    QVBoxLayout * mainLayout;
    QHBoxLayout * lineEditLayout;
    QGridLayout * recipientCategoryLayout;
    QHBoxLayout * bottomLayout;
};


