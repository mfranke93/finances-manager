#include "RecurrentItemNameFactory.h"

QString
RecurrentItemNameFactory::build(QDate const& date) const
{
    DateToStringFactory f;
    QString ret ("");
    QString::const_iterator it = templateString.cbegin();
    bool tokenMode { false};
    QString token ("");

    while (it != templateString.cend())
    {
        QChar const next = *it;
        
        if (tokenMode)
        {
            if (next == '}')
            {
                ret.append(f.build(token, date));
                token.clear();
                tokenMode = false;
            }
            else 
            {
                token.append(next);
            }
        }
        else
        {
            if (next == '{')
            {
                tokenMode = true;
            }
            else
            {
                ret.append(next);
            }
        }
        
        ++it;
    }

    if (tokenMode)
    {
        std::fprintf(stderr, "Unfinished token at end of template string: \"%s\".\n", token.toStdString().c_str());
    }

    return ret;
}

