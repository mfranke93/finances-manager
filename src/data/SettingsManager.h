//
// Created by max on 23/03/17.
//

#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <QtCore>

class SettingsManager : public QObject
{
    Q_OBJECT

    friend void deallocateSettingsManagerAtExit();

public:
    static SettingsManager * getInstance();
    ~SettingsManager();

    QString const& databaseLocation();
    QString const& backupScriptPath();
    QString const& backupRestoreScriptPath();

public slots:
    void setDatabaseLocation(QString const&);
    void setBackupScriptPath(QString const&);
    void setBackupRestoreScriptPath(QString const&);

signals:
    void databaseLocationChanged(QString);
    void backupScriptPathChanged(QString);
    void backupRestoreScriptPathChanged(QString);

protected:
    SettingsManager();
    void loadConfig(QString const&);

private:
    static SettingsManager * instance;

    /**
     * Path to store database at.
     */
    QString mDatabaseLocation;

    QString mConfigFilePath;

    /**
     * File for backup script.
     */
    QString mBackupScriptFile;

    /**
     * File for script to restore from backup.
     */
    QString mBackupRestoreScriptFile;
};

void deallocateSettingsManagerAtExit();
