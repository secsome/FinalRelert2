#pragma once

#include <Always.h>

class Rect
{
public:
	Rect(int x = 0, int y = 0, int w = 0, int h = 0) noexcept;

	Rect Intersect(const Rect& rectangle, int* x = nullptr, int* y = nullptr) const;
	static Rect Union(const Rect& rect1, const Rect& rect2);

	bool Is_Valid() const;
	int Size() const { return(Width * Height); }

	int X;
	int Y;
	int Width;
	int Height;
};