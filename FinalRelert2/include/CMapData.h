#pragma once

#include <Always.h>

#include <INI.h>

class CMapData
{
public:
    explicit CMapData() = default;

    CLASS_NOCOPY(CMapData);
    CLASS_NOMOVE(CMapData);

    INIClass MapFile;
    struct
    {
        int Left;
        int Top;
        int Width;
        int Height;
    } MapSize;
};

extern CMapData Map;
