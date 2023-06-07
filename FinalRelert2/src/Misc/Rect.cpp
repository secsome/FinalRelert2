#include <Rect.h>

Rect::Rect(int x, int y, int w, int h) noexcept
	: X { x }
	, Y { y }
	, Width{ w }
	, Height{ h }
{
}

bool Rect::Is_Valid() const
{
	return Width > 0 && Height > 0;
}

Rect Rect::Intersect(const Rect& rectangle, int* x, int* y) const
{
	static Rect illegal{ 0,0,0,0 };
	Rect r = rectangle;

	if (!Is_Valid() || !rectangle.Is_Valid()) 
		return illegal;

	if (r.X < X) 
	{
		r.Width -= X - r.X;
		r.X = X;
	}
	if (r.Width < 1)
		return illegal;

	if (r.Y < Y) 
	{
		r.Height -= Y - r.Y;
		r.Y = Y;
	}
	if (r.Height < 1) 
		return illegal;

	if (r.X + r.Width > X + Width)
		r.Width -= (r.X + r.Width) - (X + Width);
	if (r.Width < 1) 
		return illegal;

	if (r.Y + r.Height > Y + Height)
		r.Height -= (r.Y + r.Height) - (Y + Height);
	if (r.Height < 1) 
		return illegal;

	if (x != nullptr)
		*x -= (r.X - X);
	if (y != nullptr)
		*y -= (r.Y - Y);

	return r;
}

Rect Rect::Union(const Rect& rect1, const Rect& rect2)
{
	if (rect1.Is_Valid()) 
	{
		if (rect2.Is_Valid()) 
		{
			Rect result = rect1;

			if (result.X > rect2.X) 
			{
				result.Width += result.X - rect2.X;
				result.X = rect2.X;
			}
			if (result.Y > rect2.Y) 
			{
				result.Height += result.Y - rect2.Y;
				result.Y = rect2.Y;
			}
			if (result.X + result.Width < rect2.X + rect2.Width)
				result.Width = rect2.X + rect2.Width - result.X + 1;
			if (result.Y + result.Height < rect2.Y + rect2.Height)
				result.Height = rect2.Y + rect2.Height - result.Y + 1;
			return result;
		}
		return rect1;
	}
	return rect2;
}