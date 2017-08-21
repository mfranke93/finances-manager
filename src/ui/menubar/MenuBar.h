//
// Created by max on 02/01/17.
//

#pragma once

#include <QtWidgets/QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar();
    MenuBar(MenuBar const&) = default;
    MenuBar& operator=(MenuBar const&) = default;

protected:
    void buildFileMenu();
    void buildHelpMenu();

private slots:
    inline void closeApplication() { exit(0); };
    void makeDataBackup();
    void restoreDataBackup();
    void showAbout();
    void openSettings();
};



