//
// Created by max on 12/10/16.
//

#include "ResourceHandler.h"

ResourceHandler * ResourceHandler::instance = nullptr;

ResourceHandler::ResourceHandler()
{
    // ctor
    initColors();

    recipientNameFont = []() -> QFont
    {
        QFont font ("Sans Serif", 10);
        font.setBold(true);
        return font;
    }();
    recipientAddressFont = []() -> QFont
    {
        QFont font ("Sans Serif", 7);
        return font;
    }();
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
    std::map<QString, QColor> cols;
    constexpr size_t RANGE = numberedColorRange;
    for (size_t count = 0; count < RANGE; ++count)
    {
        char buf[10];
        std::sprintf(buf, "color%02lu", count+1);
        constexpr int value = static_cast<int>(0.8 * 256);
        constexpr int saturation = static_cast<int>(0.7 * 256);
        const int hue = static_cast<int>(count/ static_cast<double>(RANGE) * 360);

        cols.emplace(std::make_pair(QString(buf), QColor::fromHsv(hue, saturation, value)));
     }

    colors.clear();
    for (auto& t : cols)
    {
        QColor const col  = t.second;
        QColor const col2 = ResourceHandler::lightVersion(col);
        colors.emplace(std::make_pair(t.first + ".dark", col));
        colors.emplace(std::make_pair(t.first + ".light", col2));
    }

    // UI colors
    {
        colors.emplace(std::make_pair(
                "negative numbers red",
                QColor(240, 20, 30)
        ));
        colors.emplace(std::make_pair(
                "positive numbers blue",
                QColor(20, 20, 80)
        ));
        colors.emplace(std::make_pair(
                "plot background white",
                QColor(0xff, 0xff, 0xff)
        ));
        colors.emplace(std::make_pair(
                "plot grid grey",
                QColor(0x80, 0x80, 0x80)
        ));
        colors.emplace(std::make_pair(
                "plot negative line red",
                QColor(0xf0, 0x20, 0x20)
        ));
        colors.emplace(std::make_pair(
                "plot negative area red",
                QColor(0xf0, 0x20, 0x20, 70).lighter()
        ));
        colors.emplace(std::make_pair(
                "plot positive line blue",
                QColor(0x20, 0x20, 0xf0)
        ));
        colors.emplace(std::make_pair(
                "plot positive area blue",
                QColor(0x20, 0x20, 0xf0, 70).lighter()
        ));
        colors.emplace(std::make_pair(
                "plot line green",
                QColor(0x20, 0x80, 0x20)
        ));
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