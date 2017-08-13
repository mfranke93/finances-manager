//
// Created by max on 02/01/17.
//

#include <QtWidgets/QApplication>
#include <data/DbHandler.h>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <ui/dialogs/SettingsDialog.h>
#include <data/SettingsManager.h>
#include <QtCore/QProcess>
#include "MenuBar.h"

MenuBar::MenuBar()
{
    // ctor
    buildFileMenu();
    buildHelpMenu();
}

void
MenuBar::buildFileMenu()
{
    QMenu * menu = new QMenu("&File");
    addMenu(menu);

    /******************************/
    menu->addAction("Make data &backup", this, SLOT(makeDataBackup()));
    menu->addAction("&Restore data backup", this, &MenuBar::restoreDataBackup);
    menu->addAction("Settings", this, SLOT(openSettings()));
    /******************************/
    menu->addSeparator();
    menu->addAction("&Quit", this, SLOT(closeApplication()), QKeySequence(Qt::KeyboardModifier::ControlModifier | Qt::Key_Q));
    /******************************/
}

void
MenuBar::buildHelpMenu()
{
    QMenu * menu = new QMenu("&Help");
    addMenu(menu);

    /******************************/
    menu->addAction("&About", this, SLOT(showAbout()));
    /******************************/
}

void
MenuBar::makeDataBackup()
{
    // call backup script
    QString dbLocation = SettingsManager::getInstance()->databaseLocation();
    QString backupScript = SettingsManager::getInstance()->backupScriptPath();

    QString execStr = QString("/usr/bin/urxvt -e zsh -c \"") + backupScript + " " + dbLocation + "\"";

    QProcess process;
    process.start(execStr);
    if (!process.waitForFinished(30000))
    {
        std::cerr << "Backup timed out (30s)." << std::endl;
    }
}

void
MenuBar::restoreDataBackup()
{
    // call restore script
    QString const backupRestoreScript = SettingsManager::getInstance()->backupRestoreScriptPath();
    QString tmpdir;

    // get backup file
    QString const backup = QFileDialog::getOpenFileName(this, "Select backup",
            "", "PGP-encrypted database backup (*.gpg)");

    // create tmpfs to extract data into
    {
        QString const execStr = QString("mktemp --directory --tmpdir=/dev/shm");
        QProcess process;
        process.start(execStr);
        process.waitForFinished(30000);
        tmpdir = QString(process.readAllStandardOutput()).trimmed();
    }

    // use backup restore script to extract data out to directory
    {
        QString const execStr ("/usr/bin/urxvt -e zsh -c \"" + backupRestoreScript + " " + backup + " " + tmpdir + "\"");
        QProcess process;
        process.start(execStr);
        process.waitForFinished();
    }

    // FIXME: temporary cat
    {
        QProcess process;
        QString exec ("cat " + tmpdir + "/restore.sql");
        std::printf("Starting command '%s'\n", exec.toStdString().c_str());
        process.start(exec);
        process.waitForFinished();
        std::printf("==== \n%s\n", QString(process.readAllStandardOutput()).toStdString().c_str());
    }

    // TODO: clear database via handler
    // TODO: execute content of script into database
    DbHandler::getInstance()->restoreDatabaseFromFile(tmpdir + "/restore.sql");
    
    // cleanup tmpfs
    {
        QProcess cleanup;
        cleanup.start("rm -rfv " + tmpdir);
        cleanup.waitForFinished();
    }
}

void
MenuBar::showAbout()
{
    char versionString [50];
    std::sprintf(versionString, "Version %d.%d.%d\nBuild %s %s", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO,
                 __DATE__, __TIME__);

    QDialog dialog (this);
    dialog.setWindowTitle("About");
    dialog.setLayout(new QVBoxLayout);

    QFont font ("Arial", 20);
    font.setBold(true);
    QLabel * label = new QLabel("Finances Manager");
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    dialog.layout()->addWidget(label);

    label = new QLabel(versionString);
    font.setBold(false);
    font.setPointSize(12);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    dialog.layout()->addWidget(label);

    label = new QLabel("<a href=\"http://github.com/mfranke93/finances-manager\">http://github.com/mfranke93/finances-manager</a>");
    font.setFamily("Monospace");
    font.setBold(false);
    font.setPointSize(10);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    dialog.layout()->addWidget(label);

    static_cast<QVBoxLayout *>(dialog.layout())->addSpacing(5);

    label = new QLabel("MIT License\n"
"\n"
    "Copyright (c) 2016 Max Franke\n"
"\n"
    "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
    "of this software and associated documentation files (the \"Software\"), to deal\n"
    "in the Software without restriction, including without limitation the rights\n"
    "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
    "copies of the Software, and to permit persons to whom the Software is\n"
    "furnished to do so, subject to the following conditions:\n"
"\n"
    "The above copyright notice and this permission notice shall be included in all\n"
    "copies or substantial portions of the Software.\n"
"\n"
    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    "SOFTWARE.");
    font.setFamily("Monospace");
    font.setBold(false);
    font.setPointSize(10);
    label->setFont(font);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    dialog.layout()->addWidget(label);

    dialog.exec();
}

void
MenuBar::openSettings()
{
    SettingsDialog settingsDialog (this);
    settingsDialog.exec();
}
