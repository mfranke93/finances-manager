//
// Created by max on 02/01/17.
//

#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <data/DbHandler.h>
#include "MenuBar.h"

MenuBar::MenuBar()
{
    // ctor
    buildFileMenu();
}

void
MenuBar::buildFileMenu()
{
    QMenu * menu = new QMenu("File");
    addMenu(menu);

    /******************************/
    menu->addAction("Make data backup", this, SLOT(makeDataBackup()));
    /******************************/
    menu->addSeparator();
    menu->addAction("Quit", this, SLOT(closeApplication()), QKeySequence(Qt::KeyboardModifier::ControlModifier | Qt::Key_Q));
    /******************************/
}

void
MenuBar::makeDataBackup()
{
    DbHandler::getInstance()->dumpDatabase();
}
