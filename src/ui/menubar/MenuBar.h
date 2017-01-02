//
// Created by max on 02/01/17.
//

#pragma once

#include <QtWidgets/QMenuBar>

class MenuBar : public QMenuBar
{
public:
    MenuBar();
    MenuBar(MenuBar const&) = default;
    MenuBar& operator=(MenuBar const&) = default;
};



