#include "LayerFactory.h"

LayerFactory::LayerFactory( IArea* area_, IrrlichtDevice* device_ )
{
	def_area = area_;
	device = device_;
}

LayerFactory::~LayerFactory(void)
{
}

BackgroundLayer* LayerFactory::createBackgroundLayer()
{
	return new BackgroundLayer ( device, def_area );
}

LineCloudLayer* LayerFactory::createLineCloudLayer()
{
	return new LineCloudLayer (device);
}

TextureCacheFragmentedLayer* LayerFactory::createTCFL ()
{
	return new TextureCacheFragmentedLayer(device);
}
