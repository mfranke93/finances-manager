//
// Created by max on 26/03/17.
//

#include <data/SettingsManager.h>
#include <QtWidgets/QFileDialog>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *)
{
    topLevelLayout = new QVBoxLayout;
    settingsItemsLayout = new QGridLayout;
    bottomButtonLayout = new QHBoxLayout;

    defaultDbLocationLabel = new QLabel("Database location:");
    defaultDbLocationEdit = new QLineEdit(SettingsManager::getInstance()->databaseLocation());
    openFileSelectButton = new QPushButton("...");
    openFileSelectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    openFileSelectButton->setMaximumWidth(30);
    defaultPlottypeLabel = new QLabel("Plottype:");
    defaultPlottypeCombo = new QComboBox;
    {
        defaultPlottypeCombo->addItem("Cumulative");
        defaultPlottypeCombo->addItem("Cumulative with MinMax");
        defaultPlottypeCombo->addItem("Peaks");
    }
    defaultPlottypeCombo->setCurrentIndex(static_cast<int>(SettingsManager::getInstance()->defaultPlottype()));

    cancelButton = new QPushButton("Cancel");
    okayButton = new QPushButton("Okay");

    settingsItemsLayout->setColumnStretch(1, 4);
    settingsItemsLayout->setColumnStretch(2, 8);
    settingsItemsLayout->setColumnStretch(3, 1);

    settingsItemsLayout->addWidget(defaultDbLocationLabel, 1, 1, 1, 1);
    settingsItemsLayout->addWidget(defaultDbLocationEdit, 1, 2, 1, 1);
    settingsItemsLayout->addWidget(openFileSelectButton, 1, 3, 1, 1);
    settingsItemsLayout->addWidget(defaultPlottypeLabel, 2, 1);
    settingsItemsLayout->addWidget(defaultPlottypeCombo, 2, 2, 1, 2);

    bottomButtonLayout->addWidget(cancelButton, 1);
    bottomButtonLayout->addStretch(2);
    bottomButtonLayout->addWidget(okayButton, 1);

    topLevelLayout->addItem(settingsItemsLayout);
    topLevelLayout->addSpacerItem(new QSpacerItem(200, 5));
    topLevelLayout->addItem(bottomButtonLayout);
    setLayout(topLevelLayout);
    setMinimumWidth(640);

    /* signals */
    connect(SettingsManager::getInstance(), SIGNAL(databaseLocationChanged(QString)),
            defaultDbLocationEdit, SLOT(setText(QString)));
    connect(SettingsManager::getInstance(), SIGNAL(defaultPlottypeChanged(PlotType)),
            defaultPlottypeCombo, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(dbLocationChanged(QString)), SettingsManager::getInstance(),
            SLOT(setDatabaseLocation(QString)));
    connect(this, SIGNAL(defaultPlottypeChanged(PlotType)), SettingsManager::getInstance(),
            SLOT(setDefaultPlotType(PlotType)));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(okayButton, SIGNAL(clicked()), this, SLOT(onPressOkay()));
    connect(openFileSelectButton, SIGNAL(clicked()), this, SLOT(onPressSelectDatabaseFile()));
}

void
SettingsDialog::onPressOkay()
{
    emit dbLocationChanged(defaultDbLocationEdit->text());
    emit defaultPlottypeChanged(static_cast<PlotType>(defaultPlottypeCombo->currentIndex()));
    accept();
}

void
SettingsDialog::onPressSelectDatabaseFile()
{
    QString const dbFile = QFileDialog::getOpenFileName(this, "Select database",
            defaultDbLocationEdit->text(), "SQLite3 databases (*.db)");
    if (!dbFile.isEmpty()) this->defaultDbLocationEdit->setText(dbFile);
}
