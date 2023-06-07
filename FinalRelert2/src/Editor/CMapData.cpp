#include <CMapData.h>

CMapData Map;

CMapData::CMapData()
{
    for (auto& pCell : Cells)
        pCell = new CellClass;
}

bool CMapData::LoadMap()
{
    LoadMapDimension();

    return false;
}

void CMapData::LoadMapDimension()
{
    Size = MapFile.Get_Rect("Map", "Size", Size);
    LocalSize = MapFile.Get_Rect("Map", "LocalSize", Size);
    
}
