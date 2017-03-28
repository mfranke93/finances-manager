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
#include <ui/common/SelectOrAddRecipientButton.h>
#include <ui/dialogs/additem/AddItemRow.h>

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    AddItemDialog(QWidget * parent, Qt::WindowFlags const& f);
    ~AddItemDialog();

public slots:
    void onClickOkay();

protected slots:
    /**
     * Check whether inserted data is valid:
     * price, name, recipient.
     */
    void checkCanAddItem();

private:
    AddItemRow * addItemRow;

    QLabel * recipientLabel;

    SelectOrAddRecipientButton * selectOrAddRecipientButton;

    QCalendarWidget * dateEdit;

    QPushButton * ok;
    QPushButton * cancel;

    QVBoxLayout * mainLayout;
    QHBoxLayout * bottomLayout;
};


