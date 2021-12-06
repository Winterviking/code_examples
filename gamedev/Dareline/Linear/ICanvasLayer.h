#pragma once

#include <irrlicht.h>

#include "IAreaFactory.h"

using namespace irr;

class ICanvasLayer
{
public:

	ICanvasLayer( IrrlichtDevice* device_ )
	{
		device = device_;
		driver = device->getVideoDriver();
		separate_gui = 0;
	}

	virtual ~ICanvasLayer(void)
	{
	}


	virtual void render() = 0;

	virtual void OnEvent ( irr::SEvent event )
	{
		return;
	}

	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	IAreaFactory* separate_gui;
};

