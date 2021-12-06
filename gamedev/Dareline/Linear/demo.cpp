

int main()
{
	video::ITexture* stars = driver->getTexture ( "media/star_alpha.bmp" );
	driver->makeColorKeyTexture(stars, core::position2d<s32>(0,0));

	video::ITexture* starframe = driver->getTexture ( "media/star_frame_.bmp" );
	driver->makeColorKeyTexture ( starframe, core::position2d<s32>(10,10) );

	video::ITexture* curs = driver->getTexture ( "media/cursor_.bmp" );
	driver->makeColorKeyTexture(curs, core::position2d<s32>(0,16));

	core::rect<s32> star1(0,0,16,16);
	core::rect<s32> star2(16,0,32,16);

	// Activity Rects
	core::list<area> interactivity;
	
	driver->getMaterial2D().AntiAliasing = 5;
	driver->getMaterial2D().Thickness = 1.f;
	
	// star positions 
	core::vector2di star_pos1 = core::vector2di(90,110);
	core::vector2di star_pos2 = core::vector2di(238,107);
	core::vector2di star_pos3 = core::vector2di(44,257);
	core::vector2di star_pos4 = core::vector2di(230,301);
	core::vector2di shift = core::vector2di(8,8);

// COORDINATES!!!! of active points
	active_points.push_back(star_pos1);
	active_points.push_back(star_pos2);
	active_points.push_back(star_pos3);
	active_points.push_back(star_pos4);


// interactivity
	area intv;
	intv.rctngl = core::recti( star_pos1.X - 10, star_pos1.Y - 10, star_pos1.X + 10, star_pos1.Y + 10 );
	intv.z_order = 0;

	video::ITexture* fancy_curs_1 = driver->getTexture ( "media/curs_frame_1.bmp" );
	driver->makeColorKeyTexture(fancy_curs_1, core::position2d<s32>(0,16));
	intv.cursor_anim.push_back ( fancy_curs_1 );

	video::ITexture* fancy_curs_2 = driver->getTexture ( "media/curs_frame_2.bmp" );
	driver->makeColorKeyTexture(fancy_curs_2, core::position2d<s32>(0,16));
	intv.cursor_anim.push_back ( fancy_curs_2 );

	video::ITexture* fancy_curs_3 = driver->getTexture ( "media/curs_frame_3.bmp" );
	driver->makeColorKeyTexture(fancy_curs_3, core::position2d<s32>(0,16));
	intv.cursor_anim.push_back ( fancy_curs_3 );

	intv.cursor_type = 1;
	intv.id = 1;

	interactivity.push_back( intv );

	intv.id = 2;
	intv.rctngl = core::recti( star_pos2.X - 10, star_pos2.Y - 10, star_pos2.X + 10, star_pos2.Y + 10 );
	interactivity.push_back( intv );
	intv.id = 3;
	intv.rctngl = core::recti( star_pos3.X - 10, star_pos3.Y - 10, star_pos3.X + 10, star_pos3.Y + 10 );
	interactivity.push_back( intv );
	intv.id = 4;
	intv.rctngl = core::recti( star_pos4.X - 10, star_pos4.Y - 10, star_pos4.X + 10, star_pos4.Y + 10 );
	interactivity.push_back( intv );





	device->getCursorControl()->setVisible(false);

	int lastFPS = -1;
	u32 time = 0;
	u32 oldtime = 0;
	core::vector2di startpos = star_pos1;
	core::vector2di endpos = star_pos2;
	float speed = 0.0001;
	float dist = 0.f;
	bool anim_enabled = true;

	bool int_test = true;

	int curs_type = 0;
	area active;
	int ms_anim_cursor = 500;
	int cur_time = 0;
	int current_frame = 0;
	video::ITexture* current_cursor = 0;

	time = device->getTimer()->getTime();

	while(device->run() && driver)
	{
		if (device->isWindowActive())
		{
			time = device->getTimer()->getTime();
			driver->beginScene(true, true, video::SColor(255,0,0,0));

			driver->enableMaterial2D(true);
			// layer 1
			driver->draw2DLine( star_pos1,star_pos2, video::SColor( 255,0,0,200 ));
			driver->draw2DLine( star_pos2,star_pos3, video::SColor( 255,0,0,200 ));
			driver->draw2DLine( star_pos3,star_pos4, video::SColor( 255,0,0,200 ));
			driver->enableMaterial2D(false);

			// layer 2
			driver->draw2DImage(stars, star_pos1 - shift, star1, 0,video::SColor(255,255,255,255), true);
			driver->draw2DImage(stars, star_pos2 - shift, star2, 0,video::SColor(255,255,255,255), true);
			driver->draw2DImage(stars, star_pos3 - shift, star2, 0,video::SColor(255,255,255,255), true);
			driver->draw2DImage(stars, star_pos4 - shift, star1, 0,video::SColor(255,255,255,255), true);
			
			// fleet layer
			if ( anim_enabled )// animation
			{
				dist += speed * ( time - oldtime );
				if ( dist < 1.f )
				{
					core::vector2di pos = endpos.getInterpolated ( startpos, dist );
					driver->draw2DRectangle(video::SColor(255,255,255,255), core::rect<s32>(pos.X - 3, pos.Y - 3, pos.X + 3, pos.Y + 3 ));
				}
				else
					{anim_enabled = false;}
			}
			else
			{
				driver->draw2DRectangle(video::SColor(255,255,255,255), core::rect<s32>(endpos.X + 10 - 3, endpos.Y - 3, endpos.X + 10 + 3, endpos.Y + 3 ));
			}

			// selected object frame layer

			core::list<core::vector2di>::Iterator itrat = selected_points.begin();
								
			while ( itrat != selected_points.end() )
			{
				driver->draw2DImage ( starframe, *itrat - core::vector2di(10,10), core::recti(0,0,20,20), 0,video::SColor(255,255,255,255), true);

				itrat++;
			}

//			driver->draw2DImage ( starframe, star_pos1 - core::vector2di(10,10), core::recti(0,0,20,20), 0,video::SColor(255,255,255,255), true);
//			driver->draw2DImage ( starframe, star_pos2 - core::vector2di(10,10), core::recti(0,0,20,20), 0,video::SColor(255,255,255,255), true);

			// frame layer
			if ( frame_enabled )
			{
				driver->draw2DLine( ltc,rtc, video::SColor( 255,0,200,0 ));
				driver->draw2DLine( rtc,rbc, video::SColor( 255,0,200,0 ));
				driver->draw2DLine( rbc,lbc, video::SColor( 255,0,200,0 ));
				driver->draw2DLine( lbc,ltc, video::SColor( 255,0,200,0 ));
			}

			// cursor layer
			video::E_MATERIAL_TYPE old = driver->getMaterial2D().MaterialType;
			
			if ( int_test )
			{
				core::list<area> activated;

				core::vector2di pos = device->getCursorControl()->getPosition();
				core::list<area>::Iterator it = interactivity.begin();
								
				while ( it != interactivity.end() )
				{
					if ( rect_test( pos, (*it).rctngl ) )
					{
						activated.push_back( *it );
					}
					it++;
				}
				
				if ( activated.size() == 1 )
				{
					active = *activated.begin();
					if ( curs_type != active.cursor_type )
					{
						curs_type = active.cursor_type;
						cur_time = 0;
						current_frame = 0;
						current_cursor = *active.cursor_anim.begin();
					}

					cur_time += time - oldtime;
					if ( cur_time > ms_anim_cursor )
					{
						cur_time = 0;
						current_frame++;
						if ( current_frame == active.cursor_anim.size() )
							{current_frame = 0;}
						current_cursor = *(active.cursor_anim.begin() + current_frame);
					}
					driver->draw2DImage ( current_cursor, pos - shift, core::recti(0,0,16,16),0,video::SColor(255,255,255,255),true );
				}
				else if ( activated.size() == 0 )
				{
					if ( curs_type != 0 )
					{
						curs_type = 0;
						cur_time = 0;
						current_frame = 0;
						current_cursor = 0;
					}
				}
				else
				{
					core::list<area>::Iterator itr = interactivity.begin();
					active = *itr; itr++;	
					while ( itr != activated.end() )
					{
						if ( (*itr).z_order > active.z_order )
							{active = *itr;}
						itr++;
					}
					
					if ( curs_type != active.cursor_type )
					{
						curs_type = active.cursor_type;
						cur_time = 0;
						current_frame = 0;
						current_cursor = *active.cursor_anim.begin();
					}
					
					cur_time += time - oldtime;
					if ( cur_time > ms_anim_cursor )
					{
						cur_time = 0;
						current_frame++;
						if ( current_frame == active.cursor_anim.size() )
							{current_frame = 0;}
						current_cursor = *(active.cursor_anim.begin() + current_frame);
					}
					driver->draw2DImage ( current_cursor, pos - shift, core::recti(0,0,16,16),0,video::SColor(255,255,255,255),true );
				}
			}

//			driver->enableMaterial2D(true);

			// default draw
			if ( curs_type == 0 )
			{
				driver->draw2DImage(curs,device->getCursorControl()->getPosition(), core::recti(0,0,16,16),0,video::SColor(255,255,255,255),true );
			}
//			driver->enableMaterial2D(false);

			driver->endScene();
		}
	}

	device->drop();

	return 0;
}

#endif