#pragma once
#include "ilayerfactory.h"
class LayerFactory : public ILayerFactory
{
public:
	LayerFactory( IArea* area_, IrrlichtDevice* device_ );
	~LayerFactory(void);

	BackgroundLayer* createBackgroundLayer ();
	LineCloudLayer* createLineCloudLayer ();
	TextureCacheFragmentedLayer* createTCFL (); 


	IArea* def_area;
	IrrlichtDevice* device;
};

