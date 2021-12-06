#pragma once

#include "ICanvasLayer.h"

class CursorLayer : public ICanvasLayer
{
public:
	CursorLayer ( IrrlichtDevice* device );
	~CursorLayer(void);

	void render ();

	void defaultRendering (void)
	{
		
	}

	void alternateRendering (void)
	{
		
	}

	void setCursor ( video::ITexture* tex = 0 )
	{
		if ( tex == 0 )
		{
			def = true;
			alt_cursor = 0;
			cursor_anim = 0;
		}
		else
		{
			def = false;
			alt_cursor = tex;
		}
	}

	void setAnimatedCursor ( core::list<video::ITexture*>* tex_list )
	{
		def = false;
		cursor_anim = tex_list;
	}


	bool def;
	video::ITexture* def_cursor;
	video::ITexture* alt_cursor;
	core::list<video::ITexture*>* cursor_anim;
};

