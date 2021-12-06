#pragma once

#include "IArea.h"
#include <IrrlichtDevice.h>

#include "BackgroundLayer.h"
#include "LineCloudLayer.h"
#include "TextureCacheFragmentedLayer.h"

//class Canvas;

class ILayerFactory
{
public:

	ILayerFactory()
	{

	}

	virtual ~ILayerFactory(void)
	{
	}

	virtual BackgroundLayer* createBackgroundLayer () = 0;
	virtual LineCloudLayer* createLineCloudLayer () = 0;
	virtual TextureCacheFragmentedLayer* createTCFL () = 0; 
};

