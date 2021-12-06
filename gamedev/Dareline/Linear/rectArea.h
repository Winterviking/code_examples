#pragma once
#include "IArea.h"

class rectArea : public IArea
{
public:
	rectArea(void);
	~rectArea(void);

	int get_frame_amount (void)
	{
		return cursor_anim.size();
	}



	core::recti rctngl;
	int z_order;

	core::list<video::ITexture*> cursor_anim;

	int cursor_type;
	
	int id;
};

