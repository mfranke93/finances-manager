//
// Created by max on 23/03/17.
//

#include "SettingsManager.h"

SettingsManager * SettingsManager::instance = nullptr;

SettingsManager::SettingsManager()
{
    QString const userHome = []() -> QString {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        return QString(homedir) + "/";
    }();
    QString const configFolder = userHome + ".finances-manager/";

    mDatabaseLocation = QString(configFolder) + "finances.db";
    mDefaultPlotType  = PlotType::CUMULATIVE_WITH_MINMAX;
    // TODO
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

    // TODO: reload?
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

    // TODO: reload?
}
