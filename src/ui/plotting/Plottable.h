//
// Created by max on 08/10/16.
//

#pragma once

#include <QtGui/QPainter>

class Plottable
{
public:
    virtual void plot(QPainter * const) const = 0;
};
