#include "LineCloudLayer.h"


LineCloudLayer::LineCloudLayer ( IrrlichtDevice* device ) : ICanvasLayer(device) //, canvas_rect( canvas_ )
{
	mat2d.AntiAliasing = 5;
//	mat2d.AmbientColor = ...;
	mat2d.Thickness = 2.f;
//	mat2d.Shininess
	// default
	color = video::SColor( 255,0,0,200 );
}


LineCloudLayer::~LineCloudLayer(void)
{
}

void LineCloudLayer::render()
{
	video::SMaterial old = driver->getMaterial2D();
	driver->getMaterial2D() = mat2d;
	core::list<core::line2di>::Iterator it = line_cloud.begin();

	driver->enableMaterial2D( true );
	while ( it != line_cloud.end() )
	{
		driver->draw2DLine((*it).start,(*it).end, color );
		it++;
	}
	driver->enableMaterial2D( false );
	driver->getMaterial2D() = old;
}