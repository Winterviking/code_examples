#pragma once
#include "icanvaslayer.h"
class BackgroundLayer :	public ICanvasLayer
{
public:
	BackgroundLayer( IrrlichtDevice* device, IArea* canvas_ );
	~BackgroundLayer(void);


	void render ();

	IArea* canvas_rect;
};

