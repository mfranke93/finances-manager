//
// Created by max on 12/10/16.
//


#pragma once

#include <iostream>
#include <QtGui/QColor>
#include <QtGui/QPixmap>

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
    QPixmap const& getIcon(QString const&) const;

    /**
     * Number of numbered colors, e.g. color04.light/dark
     */
    static constexpr size_t numberedColorRange {16};
protected:
    void initColors();

    static QColor lightVersion(QColor const&) throw();

private:
    ResourceHandler();

    static ResourceHandler * instance;

    std::map<QString const, QColor const> colors;
    std::map<QString const, QPixmap const> icons;
};


