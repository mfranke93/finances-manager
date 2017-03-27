//
// Created by max on 26/03/17.
//

#pragma once


#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <ui/plotting/graphics/PlotLineFactory.h>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *);
    ~SettingsDialog() = default;

protected slots:
    void onPressOkay();
    void onPressSelectDatabaseFile();

signals:
    void dbLocationChanged(QString);
    void defaultPlottypeChanged(PlotType);

private:
    QVBoxLayout * topLevelLayout;
    QGridLayout * settingsItemsLayout;
    QHBoxLayout * bottomButtonLayout;

    QLabel      * defaultDbLocationLabel;
    QLabel      * defaultPlottypeLabel;

    QLineEdit   * defaultDbLocationEdit;
    QComboBox   * defaultPlottypeCombo;

    QPushButton * cancelButton;
    QPushButton * okayButton;

    QPushButton * openFileSelectButton;

};



