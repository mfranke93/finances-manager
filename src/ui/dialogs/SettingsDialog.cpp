//
// Created by max on 26/03/17.
//

#include <data/SettingsManager.h>
#include <QtWidgets/QFileDialog>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *)
{
    setWindowTitle("Settings");

    topLevelLayout = new QVBoxLayout;
    settingsItemsLayout = new QGridLayout;
    bottomButtonLayout = new QHBoxLayout;

    defaultDbLocationLabel = new QLabel("Database location:");
    defaultDbLocationEdit = new QLineEdit(SettingsManager::getInstance()->databaseLocation());
    openDbFileSelectButton = new QPushButton("...");
    openDbFileSelectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    openDbFileSelectButton->setMaximumWidth(30);
    backupScriptPathLabel = new QLabel("Backup script:");
    backupScriptPath = new QLineEdit(SettingsManager::getInstance()->backupScriptPath());
    openBackupScriptFileSelectButton = new QPushButton("...");

    backupRestoreScriptPathLabel = new QLabel("Backup restore script:");
    backupRestoreScriptPath = new QLineEdit(SettingsManager::getInstance()->backupRestoreScriptPath());
    openBackupRestoreScriptFileSelectButton = new QPushButton("...");

    cancelButton = new QPushButton("Cancel");
    okayButton = new QPushButton("Okay");

    settingsItemsLayout->setColumnStretch(1, 4);
    settingsItemsLayout->setColumnStretch(2, 8);
    settingsItemsLayout->setColumnStretch(3, 1);

    settingsItemsLayout->addWidget(defaultDbLocationLabel, 1, 1, 1, 1);
    settingsItemsLayout->addWidget(defaultDbLocationEdit, 1, 2, 1, 1);
    settingsItemsLayout->addWidget(openDbFileSelectButton, 1, 3, 1, 1);
    settingsItemsLayout->addWidget(backupScriptPathLabel, 3, 1);
    settingsItemsLayout->addWidget(backupScriptPath, 3, 2);
    settingsItemsLayout->addWidget(openBackupScriptFileSelectButton, 3, 3);
    settingsItemsLayout->addWidget(backupRestoreScriptPathLabel, 4, 1);
    settingsItemsLayout->addWidget(backupRestoreScriptPath, 4, 2);
    settingsItemsLayout->addWidget(openBackupRestoreScriptFileSelectButton, 4, 3);

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
    connect(SettingsManager::getInstance(), SIGNAL(backupScriptPathChanged(QString)),
            backupScriptPath, SLOT(setText(QString)));
    connect(this, SIGNAL(dbLocationChanged(QString)), SettingsManager::getInstance(),
            SLOT(setDatabaseLocation(QString)));
    connect(this, SIGNAL(defaultPlottypeChanged(PlotType)), SettingsManager::getInstance(),
            SLOT(setBackupScriptPath(QString)));
    connect(this, &SettingsDialog::backupRestoreScriptPathChanged, SettingsManager::getInstance(),
            &SettingsManager::setBackupRestoreScriptPath);
    connect(SettingsManager::getInstance(), &SettingsManager::backupRestoreScriptPathChanged,
            backupRestoreScriptPath, &QLineEdit::setText);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(okayButton, SIGNAL(clicked()), this, SLOT(onPressOkay()));
    connect(openDbFileSelectButton, SIGNAL(clicked()), this, SLOT(onPressSelectDatabaseFile()));
    connect(openBackupScriptFileSelectButton, SIGNAL(clicked()), this, SLOT(onPressSelectBackupScriptFile()));
    connect(openBackupRestoreScriptFileSelectButton, SIGNAL(clicked()), this, SLOT(onPressSelectBackupRestoreScriptFile()));
}

void
SettingsDialog::onPressOkay()
{
    emit dbLocationChanged(defaultDbLocationEdit->text());
    emit dbLocationChanged(defaultDbLocationEdit->text());
    emit backupScriptPathChanged(backupScriptPath->text());
    emit backupRestoreScriptPathChanged(backupRestoreScriptPath->text());
    accept();
}

void
SettingsDialog::onPressSelectDatabaseFile()
{
    QString const dbFile = QFileDialog::getOpenFileName(this, "Select database",
            defaultDbLocationEdit->text(), "SQLite3 databases (*.db)");
    if (!dbFile.isEmpty()) 
    {
        this->defaultDbLocationEdit->setText(dbFile);
    }
}

void
SettingsDialog::onPressSelectBackupScriptFile()
{
    QString const backupFile = QFileDialog::getOpenFileName(this, "Select backup script",
                                                        backupScriptPath->text(), "Shell script (*.sh)");
    if (!backupFile.isEmpty()) 
    {
        this->backupScriptPath->setText(backupFile);
    }
}

void
SettingsDialog::onPressSelectBackupRestoreScriptFile()
{
    QString const backupRestoreFile = QFileDialog::getOpenFileName(this, "Select backup restore script",
                                                        backupScriptPath->text(), "Shell script (*.sh)");
    if (!backupRestoreFile.isEmpty()) 
    {
        this->backupRestoreScriptPath->setText(backupRestoreFile);
    }
}
