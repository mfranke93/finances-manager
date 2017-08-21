//
// Created by max on 12/10/16.
//


#pragma once

#include <iostream>
#include <QtGui/QColor>
#include <QtGui/QPixmap>
#include <QtGui/QFont>

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
    QFont const& getRecipientNameFont() const { return recipientNameFont; };
    QFont const& getRecipientAddressFont() const { return recipientAddressFont; };

    /**
     * Get a color whose hue depends on the percentage between the parameters, for rainbow color schemes.
     * 
     * \param index     Index of color
     * \param range     Number of colors to generate, such that 0 ≤ index < range
     * 
     * \return          A dark and light version of the color as std::pair
     */
    std::pair<QColor, QColor> getRainbowColor(size_t const& index, size_t const& range) const;

    /**
     * Number of numbered colors, e.g. color04.light/dark
     */
    static constexpr size_t numberedColorRange {32};
protected:
    void initColors();

    static QColor lightVersion(QColor const&) throw();

private:
    ResourceHandler();

    static ResourceHandler * instance;

    std::map<QString const, QColor const> colors;
    std::map<QString const, QPixmap const> icons;

    QFont recipientNameFont;
    QFont recipientAddressFont;
};


