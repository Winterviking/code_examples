#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

#include "IEventReceiver.h"
#include "ICanvasLayer.h"
//#include "ilayerfactory.h"
//#include "LayerFactory.h"

//TODO:::: Define CacheManager
//TODO:::: garbage collector? to delete queue for caches .... only if really needed
#include "CacheManager.h"
#include "LayerManager.h"
#include "XMLreading.h"
#include "settings.h"

#include "defArea.h"

#include "tests.h"

class Canvas : public IEventReceiver
{
public: // STRUCT SECTION
		//enum E_CANVAS_LAYER
		//{
		//	ECL_BACKGROUND_LAYER,
		//	ECL_LINE_CLOUD,
		//	ECL_TEXTURE_CACHE_FRAGMENTED,
		//	ECL_NUMBER
		//};

		// [bunch]->[bunch]->[bunch]
		// merge->[layer_cache].render()
		// ...
		//struct layer_bunch
		//{
		//	layer_bunch (E_CANVAS_LAYER layer )
		//	{
		//		num = 0;
		//		index_layer = core::list<ICanvasLayer*>();
		//		layers_pointer = core::list<ICanvasLayer*>::Iterator();
		//		eclayer = layer;
		//	}
		//	E_CANVAS_LAYER eclayer;
		//	core::list<ICanvasLayer*> index_layer;
		//	core::list<ICanvasLayer*>::Iterator layers_pointer;
		//	int num;
		//};




public:
	Canvas( IrrlichtDevice* device_ = 0 );
	~Canvas(void);

public:
		// This is the one method that we have to implement
		virtual bool OnEvent(const SEvent& event)
		{
			// Remember whether each key is down or up
			if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
				{KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;}
			if ( event.EventType == irr::EET_MOUSE_INPUT_EVENT )
			{
				if ( event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN )
				{
/*					if ( !frame_enabled )
					{
						frame_enabled = true;
						ltc.X = event.MouseInput.X;
						ltc.Y = event.MouseInput.Y;
						lbc.X = event.MouseInput.X;
						rtc.Y = event.MouseInput.Y;
						
						// saaaame :)
						rbc.X = event.MouseInput.X;
						rbc.Y = event.MouseInput.Y;
						lbc.Y = event.MouseInput.Y;
						rtc.X = event.MouseInput.X;
					}*/
				}
				else if ( event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP )
				{
/*					if ( frame_enabled )
					{
						frame_enabled = false;
						rbc.X = event.MouseInput.X;
						rbc.Y = event.MouseInput.Y;
						lbc.Y = event.MouseInput.Y;
						rtc.X = event.MouseInput.X;
					}
					if ( rbc == ltc )
					{
						selected_points.clear();
					}*/
				}
				else if ( event.MouseInput.Event == irr::EMIE_MOUSE_MOVED )
				{
/*					if ( frame_enabled )
					{
						rbc.X = event.MouseInput.X;
						rbc.Y = event.MouseInput.Y;
						lbc.Y = event.MouseInput.Y;
						rtc.X = event.MouseInput.X;

						core::list<core::vector2di>::Iterator itrat = active_points.begin();
						
						selected_points.clear();
						if ( ( ltc.X <= rbc.X ) && ( ltc.Y <= rbc.Y ) )
						{
							while ( itrat != active_points.end() )
							{
								if (rect_test_( *itrat, core::recti(ltc,rbc) ) )
									{selected_points.push_back ( *itrat );}
								itrat++;
							}
						}
						else if ( ( ltc.X <= rbc.X ) && ( ltc.Y > rbc.Y ) )
						{
							while ( itrat != active_points.end() )
							{
								if (rect_test_( *itrat, core::recti(lbc,rtc) ) )
									{selected_points.push_back ( *itrat );}
								itrat++;
							}
						}
						else if ( ( ltc.X > rbc.X ) && ( ltc.Y <= rbc.Y ) )
						{
							while ( itrat != active_points.end() )
							{
								if (rect_test_( *itrat, core::recti(rtc,lbc) ) )
									{selected_points.push_back ( *itrat );}
								itrat++;
							}
						}
						else if ( ( ltc.X > rbc.X ) && ( ltc.Y > rbc.Y ) )
						{
							while ( itrat != active_points.end() )
							{
								if (rect_test_( *itrat, core::recti(rbc,ltc) ) )
									{selected_points.push_back ( *itrat );}
								itrat++;
							}
						}
					}*/
				}
			}
			return false;
		}

public:

/* TODO:::: wai
		virtual bool IsKeyDown(EKEY_CODE keyCode) const
		{
			return KeyIsDown[keyCode];
		}
*/
		void render (void);

		void cursorSwitchEnabled (void)
			{cursor.enabled = !cursor.enabled;}

		IrrlichtDevice* getDevice (void)
			{return device;}
		IArea* getDefaultArea (void)
		{
			return default_area;
		}

		void readLayers (void)
		{
			xml->readDataFromXML( "data.xml" );
		}

		//inline LineCloudLayer* createLineCloudLayer (void)
		//{
		//	return (LineCloudLayer*)createLayer( ECL_LINE_CLOUD );
		//}

		//inline TextureCacheFragmentedLayer* createTCFL (void)
		//{
		//	return (TextureCacheFragmentedLayer*)createLayer( ECL_TEXTURE_CACHE_FRAGMENTED );
		//}


		//ICanvasLayer* createLayer ( E_CANVAS_LAYER type )
		//{
		//	ICanvasLayer* result = 0;
		//	switch ( type )
		//	{
		//		case ECL_BACKGROUND_LAYER:
		//			{
		//				result = LFactory->createBackgroundLayer();
		//				break;
		//			}
		//		case ECL_LINE_CLOUD:
		//			{
		//				result = LFactory->createLineCloudLayer();
		//				break;
		//			}
		//		case ECL_TEXTURE_CACHE_FRAGMENTED:
		//			{
		//				result = LFactory->createTCFL();
		//				break;
		//			}
		//	}
		//	layer_cache[type].index_layer.push_back ( result );
		//	return result;
		//}

		// DEBUG:::::
		void run_loop (void)
		{
			lmngr->mergeLayers();
			int lastFPS = 0;

			while ( device->run() && driver )
			{
				if ( device->isWindowActive() )
				{
					this->render();

					int fps = driver->getFPS();

					if (lastFPS != fps)
					{
						core::stringw str = L"Canvas Demo : FPS[";
						str += fps;
						str += "]";
						str += " OpenGL";

						device->setWindowCaption(str.c_str());
						lastFPS = fps;
					}

				}
			}
		}

private:
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
		IrrlichtDevice *device;
		video::IVideoDriver* driver;

		// Canvas Settings
		core::dimension2du dimension;

		// base GUI element : parent for everything
		defArea* default_area;

		// Color of background
		video::SColor ambient;
		
		// REFACTOR:::: settings structs must be available through header
		// CURSOR RELATED SECTION
		struct cursor_struct
		{
			bool enabled;
			bool isOverCanvas;
			int cursor_type;
			int cursor_max_side;
		} cursor;

		//struct gsettings
		//{
		//	gsettings ()
		//	{
		//		
		//	}
		//	cursor_struct& cursor;
		//};

		core::vector2di cursor_pos;

		core::vector2di updateCursorPos (void)
		{
			cursor_pos = device->getCursorControl()->getPosition();
			return cursor_pos;
		}

		// FRAME RELATED SECTION
		struct
		{
			bool frame_enabled;
			core::vector2di ltc;
			core::vector2di lbc;
			core::vector2di rbc;
			core::vector2di rtc;
		} frame;

		core::list<core::vector2di> active_points;
		core::list<core::vector2di> selected_points;

		// canvas layer related stuff
		LayerManager* lmngr;

		CacheManager* cmngr;

		XMLreading* xml;
		
		//core::array<layer_bunch> layer_cache;
		//core::list<ICanvasLayer*> layer_line;
		//ILayerFactory* LFactory;

		// TODO:::: 
		// Call after xml reading ^^ :::: merge eats allmost nothing lol : so i can call it many tiemes
		// if ill achieve layers which i have to add/delete every second then i should add other list with different capabilities
		//inline void mergeLayers ()
		//{
		//	layer_line.clear();
		//	for ( int i = 0; i < layer_cache.size(); i++ )
		//	{
		//		core::list<ICanvasLayer*>& spare = layer_cache[i].index_layer;
		//		core::list<ICanvasLayer*>::Iterator it = spare.begin();
		//		
		//		while ( it != spare.end() )
		//		{
		//			layer_line.push_back( *it );
		//			it++;
		//		}
		//		layer_cache[i].layers_pointer = spare.getLast();
		//	}
		//}


		// TODO:::: if i will need additional layer addition at runtime, then i better add some another xml-related indexing 

		// mostly for debug and demo purposes

		public:
		inline void makeDevice ()
		{
			dimension = core::dimension2d<u32>(800, 600);

			SIrrlichtCreationParameters params;
			params.AntiAlias = 5;// best for lines :::: indeed
			params.Bits = 16;
			params.Fullscreen = false;
			params.WindowSize = dimension;
			params.DriverType = video::EDT_OPENGL;
			params.EventReceiver = this;
	
			device = createDeviceEx ( params );

			if (device == 0)
				return;

			driver = device->getVideoDriver();
		}
};
