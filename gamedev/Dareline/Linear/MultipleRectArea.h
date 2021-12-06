#pragma once
#include "IArea.h"

#include "Cache.h"


//TODO:::: use it in cursor layer ::: think about finding out by z_oreder of game objects tied with rects :)

// all rects have same zorder
class MultipleRectArea : public IArea
{
	public:
		MultipleRectArea(void);
		~MultipleRectArea(void);

		// tmp will be game object most likely
		core::list<core::recti> rectangles;

		void fixRectangles (void)
		{
			for ( int i = 0; i < gocache->data.size(); i++ )
			{
				core::vector2di& pos = gocache->data[i].ptr->GetPostition();
				core::recti rect = core::recti( pos - frameshift, pos + frameshift );
				rectangles.push_back( rect );
			}		
		}

		int get_frame_amount (void)
		{
			return cursor_anim.size();
		}

		// we test multiple rectangles
		bool test ( core::vector2di& pos )
		{
			core::list<core::recti>::Iterator it = rectangles.begin();
			while ( it != rectangles.end() )
			{
				if ( ( pos.X > it->UpperLeftCorner.X ) && ( pos.X < it->LowerRightCorner.X ) && ( pos.Y > it->UpperLeftCorner.Y ) && ( pos.Y < it->LowerRightCorner.Y ) )
					{return true;}
				it++;
			}
			return false;
		}

		int z_order;

//		RectCache rectangles;

		core::list<video::ITexture*> cursor_anim;

		core::vector2di frameshift;

		int cursor_type;
	
		int id;
		GameObjectCache* gocache;
};

