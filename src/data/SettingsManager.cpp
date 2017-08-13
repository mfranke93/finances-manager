//
// Created by max on 23/03/17.
//

#include <fstream>
#include "SettingsManager.h"

SettingsManager * SettingsManager::instance = nullptr;

SettingsManager::SettingsManager()
{
    QString const userHome = []() -> QString {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return QString(homedir) + "/";
    }();
    QString const configFolder = userHome + ".config/finances-manager/";

    mDatabaseLocation = QString(configFolder) + "finances.db";
    mDefaultPlotType  = PlotType::CUMULATIVE_WITH_MINMAX;
    mBackupScriptFile = QString(configFolder) + "backup.sh";

    // load rc file
    mConfigFilePath = configFolder + "config";
    loadConfig(mConfigFilePath);

    atexit(deallocateSettingsManagerAtExit);
}

SettingsManager::~SettingsManager()
{
    std::ofstream config (mConfigFilePath.toStdString());
    config << "defaultPlotType " << static_cast<int>(mDefaultPlotType) << std::endl;
    config << "databaseLocation " << mDatabaseLocation.toStdString() << std::endl;
    config << "backupScriptPath " << mBackupScriptFile.toStdString() << std::endl;
    config << "backupRestoreScriptPath " << mBackupRestoreScriptFile.toStdString() << std::endl;

    config.close();
}

SettingsManager *
SettingsManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SettingsManager;
    }

    return instance;
}

QString const&
SettingsManager::databaseLocation()
{
    return mDatabaseLocation;
}

void
SettingsManager::setDatabaseLocation(QString const& dbLocation)
{
    mDatabaseLocation = dbLocation;
    emit databaseLocationChanged(dbLocation);
}

PlotType const&
SettingsManager::defaultPlottype()
{
    return mDefaultPlotType;
}

void
SettingsManager::setDefaultPlotType(PlotType const& pt)
{
    mDefaultPlotType = pt;
    emit defaultPlottypeChanged(pt);
}

QString const&
SettingsManager::backupScriptPath()
{
    return mBackupScriptFile;
}

QString const&
SettingsManager::backupRestoreScriptPath()
{
    return mBackupRestoreScriptFile;
}

void
SettingsManager::setBackupScriptPath(QString const& sc)
{
    std::printf("backup changed: %s\n", sc.toStdString().c_str());
    mBackupScriptFile = sc;
    emit backupScriptPathChanged(sc);
}

void
SettingsManager::loadConfig(QString const& filename)
{
    std::ifstream configFile;
    configFile.open(filename.toStdString().c_str());

    std::string token;
    while (configFile)
    {
        configFile >> token;

        if (token == "defaultPlotType")
        {
            int i;
            configFile >> i;
            mDefaultPlotType = static_cast<PlotType>(i);
        }
        else if (token == "databaseLocation")
        {
            configFile >> token;
            mDatabaseLocation = QString(token.c_str());
        }
        else if (token == "backupScriptPath")
        {
            configFile >> token;
            mBackupScriptFile = QString(token.c_str());
        }
        else if (token == "backupRestoreScriptPath")
        {
            configFile >> token;
            mBackupRestoreScriptFile = QString(token.c_str());
        }
    }

    configFile.close();
}

void
deallocateSettingsManagerAtExit()
{
    if (SettingsManager::instance != nullptr) delete SettingsManager::instance;
}

void
SettingsManager::setBackupRestoreScriptPath(QString const& sc)
{
    std::printf("restore changed: %s\n", sc.toStdString().c_str());
    mBackupRestoreScriptFile = sc;
    emit backupRestoreScriptPathChanged(sc);
}
