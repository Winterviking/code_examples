#include "LayerManager.h"


LayerManager::LayerManager( IArea* area_, IrrlichtDevice* device_ ): LFactory( area_, device_ )
{
	device = device_;
	layer_cache.reallocate( ECL_NUMBER );
	for ( int i = 0; i < ECL_NUMBER; i++ )
	{
		layer_cache.push_back ( layer_bunch ( (E_CANVAS_LAYER)i ) );
	}
}


LayerManager::~LayerManager(void)
{
}
