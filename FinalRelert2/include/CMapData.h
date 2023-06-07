#pragma once

#include <Always.h>

#include <INI.h>
#include <CellClass.h>

class CMapData
{
public:
	explicit CMapData();

    CLASS_NOCOPY(CMapData);
    CLASS_NOMOVE(CMapData);

    bool LoadMap();
    void LoadMapDimension();

    INIClass MapFile;
    Rect Size;
    Rect LocalSize;
    CellClass* Cells[0x40000];
};

extern CMapData Map;

class MapCellEnumerator
{
	MapCellEnumerator()
		: NextX{ 1 }
		, NextY{ Map.Size.Width }
		, NextColumn{ Map.Size.Width - 1 }
		, NextCell{ 0x200 * Map.Size.Width + 1 }
	{}

	operator bool() const
	{
		return NextX < Map.Size.Width + Map.Size.Height 
			&& NextY < Map.Size.Width + Map.Size.Height;
	}

	CellClass* operator*() const
	{
		return Map.Cells[NextCell];
	}

	MapCellEnumerator& operator++()
	{
		// TODO
	}

	MapCellEnumerator operator++(int)
	{
		auto const old = *this;
		++*this;
		return old;
	}

	int NextX;
	int NextY;
	int NextColumn;
	int NextCell;
};
//
//class CellRectEnumerator
//{
//	Rect bounds;
//	Cell current;
//
//public:
//	CellRectEnumerator(Rect bounds)
//		: bounds(bounds), current()
//	{
//		current = Cell{
//			static_cast<short>(bounds.X),
//			static_cast<short>(bounds.Y) };
//	}
//
//	operator bool() const {
//		return current.Y <= bounds.Bottom;
//	}
//
//	const CellStruct& operator * () const {
//		return current;
//	}
//
//	CellRectEnumerator& operator ++ () {
//		this->next();
//		return *this;
//	}
//
//	void operator ++ (int) {
//		this->next();
//	}
//
//protected:
//	void next() {
//		// increase the x coordinate and, if it is outside the bounds,
//		// go to the beginning of the next "line"
//		++current.X;
//
//		if (current.X > bounds.Right) {
//			current.X = static_cast<short>(bounds.Left);
//			++current.Y;
//		}
//	}
//};
