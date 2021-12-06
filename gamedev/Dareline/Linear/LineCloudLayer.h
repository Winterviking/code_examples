#pragma once
#include "icanvaslayer.h"
class LineCloudLayer : public ICanvasLayer
{
public:
	LineCloudLayer( IrrlichtDevice* device );
	~LineCloudLayer(void);

	void render ();

	void addLine ( core::vector2di& begin, core::vector2di& end )
	{
		line_cloud.push_back ( core::line2di( begin, end ) );
	}
	
	void addLine ( core::line2di& newline )
	{
		line_cloud.push_back ( newline );
	}

	core::list<core::line2di> line_cloud;

	video::SColor color;

	video::SMaterial mat2d;
};

