#pragma once
#include "iarea.h"
class defArea : public IArea
{
	public:
		defArea(video::ITexture* cursor_, core::recti& area );
		~defArea(void);

	core::recti rctngl;

//	core::list<video::ITexture*> cursor_anim;
	
	video::ITexture* cursor;

	int getID (void)
		{return id;}
	int getZOrder (void)
		{return z_order;}

private:
	int id;
	int z_order;
};

