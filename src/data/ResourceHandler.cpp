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

QColor
ResourceHandler::lightVersion(QColor const& color)
throw()
{
    return color.lighter(160);
}

void
ResourceHandler::initColors()
{
    std::map<QString, QColor> cols1;
    constexpr size_t RANGE = numberedColorRange;
    for (size_t count = 0; count < RANGE; ++count)
    {
        char buf[10];
        std::sprintf(buf, "color%02lu", ((count*5)%RANGE)+1);
        constexpr int value = static_cast<int>(0.8 * 256);
        constexpr int saturation = static_cast<int>(0.7 * 256);
        const int hue = static_cast<int>(count/ static_cast<double>(RANGE) * 360);

        cols1.emplace(std::make_pair(QString(buf), QColor::fromHsv(hue, saturation, value)));
     }

    // TODO: Add UI color scheme

    colors.clear();
    for (auto& t : cols1)
    {
        QColor const col  = t.second;
        QColor const col2 = ResourceHandler::lightVersion(col);
        colors.emplace(std::make_pair(t.first + ".dark", col));
        colors.emplace(std::make_pair(t.first + ".light", col2));
    }
}

QColor const&
ResourceHandler::getColor(QString const& str) const
{
    if (colors.find(str) == colors.end())
    {
        std::string errStr = "No such color in map: ";
        errStr += str.toStdString();
        throw std::out_of_range(errStr);
    }

    return colors.at(str);
}