#pragma once
#include <qstring.h>

struct xml_strcut
{
    int x;
    int y;
    int width;
    int height;
    struct xml_font
    {
        QString font;
        int red;
        int green;
        int blue;
    };
    xml_font font;
    QString TimeType;
    struct xml_background
    {
        int red;
        int green;
        int blue;
        int alpha;
    };
    xml_background background;
};