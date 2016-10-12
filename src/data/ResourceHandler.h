//
// Created by max on 12/10/16.
//


#pragma once


#include <QtGui/QColor>

class ResourceHandler
{
public:
    static inline ResourceHandler const * getInstance()
    {
        if (instance == nullptr)
        {
            instance = new ResourceHandler;
        }

        return instance;
    }

    ~ResourceHandler() = default;
    ResourceHandler(ResourceHandler const&) = delete;
    ResourceHandler& operator= (ResourceHandler const&) = delete;

    QColor const& getColor(QString const&) const;
    QIcon const& getIcon(QString const&) const;

protected:
    void initColors();

private:
    ResourceHandler();

    static ResourceHandler * instance;

    std::map<QString const, QColor const> colors;
    std::map<QString const, QIcon const> icons;
};


