
// TODO :::: preprocessor herez

#include <vector2d.h>
#include <rect.h>
using namespace irr;

// TODO:::: refine :)

// strict
inline bool rect_test ( core::vector2di& vec, core::recti& bounds )
{
	if ( ( vec.X > bounds.UpperLeftCorner.X ) && ( vec.X < bounds.LowerRightCorner.X ) && ( vec.Y > bounds.UpperLeftCorner.Y ) && ( vec.Y < bounds.LowerRightCorner.Y ) )
		{return true;}
	else
		{return false;}
}

// non strict
inline bool rect_test_ ( core::vector2di& vec, core::recti& bounds )
{
	if ( ( vec.X >= bounds.UpperLeftCorner.X ) && ( vec.X <= bounds.LowerRightCorner.X ) && ( vec.Y >= bounds.UpperLeftCorner.Y ) && ( vec.Y <= bounds.LowerRightCorner.Y ) )
		{return true;}
	else
		{return false;}
}