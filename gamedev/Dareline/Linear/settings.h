
#include <vector2d.h>
using namespace irr;

struct cursor_struct_
{
	bool enabled;
	bool isOverCanvas;
	int cursor_type;
	int cursor_max_side;
};

struct ftw
{
	ftw()
	{
	}


};

struct gsettings
{
	gsettings (cursor_struct_* cur, core::vector2di* pos )
	{
		cursor = cur;
		cursor_pos = pos;
	}

	cursor_struct_* cursor;
	core::vector2di* cursor_pos;
};
