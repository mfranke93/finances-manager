//
// Created by max on 23/03/17.
//

#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <QtCore/QString>
#include <ui/plotting/graphics/PlotLineFactory.h>

class SettingsManager : public QObject
{
    Q_OBJECT

    friend void deallocateSettingsManagerAtExit();

public:
    static SettingsManager * getInstance();
    ~SettingsManager();

    QString const& databaseLocation();
    PlotType const& defaultPlottype();
    QString const& backupScriptPath();
    QString const& backupRestoreScriptPath();

public slots:
    void setDatabaseLocation(QString const&);
    void setDefaultPlotType(PlotType const&);
    void setBackupScriptPath(QString const&);
    void setBackupRestoreScriptPath(QString const&);

signals:
    void databaseLocationChanged(QString);
    void defaultPlottypeChanged(PlotType);
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
    PlotType mDefaultPlotType;

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
