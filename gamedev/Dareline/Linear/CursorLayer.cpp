#include "CursorLayer.h"


CursorLayer::CursorLayer(IrrlichtDevice* device) : ICanvasLayer ( device )
{
}


CursorLayer::~CursorLayer(void)
{
}

void CursorLayer::render()
{
	if ( def )
	{
		defaultRendering();
	}
	else
	{
		alternateRendering();
	}
}