//
// Created by max on 23/03/17.
//

#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <QtCore/QString>

class SettingsManager
{
public:
    static SettingsManager * getInstance();
    ~SettingsManager() = default;

    void setDatabaseLocation(QString const&);
    QString const& databaseLocation();

protected:
    SettingsManager();

private:
    static SettingsManager * instance;

    /**
     * Path to store database at.
     */
    QString mDatabaseLocation;
};



