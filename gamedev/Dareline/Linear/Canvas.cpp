#include "Canvas.h"

Canvas::Canvas ( IrrlichtDevice* device_) : ambient ( video::SColor(255,0,0,0) )
{

	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		{KeyIsDown[i] = false;}
	cursor.enabled = true;
	cursor.cursor_max_side = 16;
	cursor.cursor_type = 0;

	if ( device_ == 0 )
	{
		makeDevice();
	}
	device->getCursorControl()->setVisible( false );
	
	video::ITexture* curs = driver->getTexture( "media/cursor_.bmp" );
	driver->makeColorKeyTexture(curs, core::position2d<s32>(0,16));
	default_area = new defArea ( curs, core::recti(core::vector2di(0,0), dimension ) );

	cmngr = new CacheManager();
	lmngr = new LayerManager( default_area, device );
	xml = new XMLreading(lmngr,cmngr);
//	LFactory = new LayerFactory( default_area, device );

	//layer_cache.reallocate( ECL_NUMBER );
	//for ( int i = 0; i < ECL_NUMBER; i++ )
	//{
	//	layer_cache.push_back ( layer_bunch ( (E_CANVAS_LAYER)i ) );
	//}
}

Canvas::~Canvas(void)
{
	delete cmngr;
	delete lmngr;
	delete default_area;
	delete xml;
}

void Canvas::render ( void )
{
	cursor.isOverCanvas = rect_test_( updateCursorPos(), default_area->rctngl );

	driver->beginScene(true, true, ambient);

	lmngr->render();


	// Cursor layers are the highest :)

	// default layer ( main cursor )
	if ( cursor.cursor_type == 0 )
	if ( cursor.isOverCanvas && cursor.enabled )
	{	
		driver->draw2DImage(default_area->cursor,updateCursorPos(), core::recti(0,0,cursor.cursor_max_side,cursor.cursor_max_side),0,video::SColor(255,255,255,255),true );
	}

	driver->endScene();
}
