//
// Created by max on 12/10/16.
//

#include "ResourceHandler.h"

ResourceHandler * ResourceHandler::instance = nullptr;

ResourceHandler::ResourceHandler()
{
    // ctor
    initColors();
}

void
ResourceHandler::initColors()
{
    // red and light red
    colors[QString("color1")] = QColor(205, 80, 80);
    colors[QString("color2")] = QColor(205, 140, 140);

    // green and light green
    colors[QString("color3")] = QColor(80, 205, 80);
    colors[QString("color4")] = QColor(140, 205, 140);

    // blue and light blue
    colors[QString("color5")] = QColor(80, 80, 205);
    colors[QString("color6")] = QColor(140, 140, 205);
}