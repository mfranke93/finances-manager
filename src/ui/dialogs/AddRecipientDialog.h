//
// Created by max on 05/10/16.
//


#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class AddRecipientDialog : public QDialog
{
Q_OBJECT

public:
    AddRecipientDialog(QWidget * parent, Qt::WindowFlags const& f);
    ~AddRecipientDialog() = default;

protected slots:
    void onPressOkay();
private:
    QLineEdit * name;
    QTextEdit * address;
    QCheckBox * isOnline;
    QPushButton * cancel;
    QPushButton * ok;

    QVBoxLayout * mainLayout;
    QHBoxLayout * layout1;
    QHBoxLayout * layout2;
};


