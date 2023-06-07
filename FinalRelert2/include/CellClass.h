#pragma once

#include <Always.h>

#include <CMapData.h>

struct Cell
{
    short X;
    short Y;

    int AsIndex() const
    {
        return X + Y * 0x200;
    }

    void FromIndex(int index)
    {
        X = index % 0x200;
        Y = index / 0x200;
    }

    operator int() const
    {
        return AsIndex();
    }

    Cell& operator=(int index)
    {
        FromIndex(index);
        return *this;
    }
};

class CellClass
{
public:

    Cell Position;
    int TileType;
    byte Tile;
    char Level;
    bool IsIceGrowthAllowed;
};