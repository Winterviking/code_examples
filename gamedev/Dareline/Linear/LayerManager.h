#pragma once

#include <irrList.h>

#include "LayerFactory.h"

class LayerManager
{
public:
		enum E_CANVAS_LAYER
		{
			ECL_BACKGROUND_LAYER,
			ECL_LINE_CLOUD,
			ECL_TEXTURE_CACHE_FRAGMENTED,
			ECL_NUMBER
		};

		// [bunch]->[bunch]->[bunch]
		// merge->[layer_cache].render()
		// ...
		struct layer_bunch
		{
			layer_bunch (E_CANVAS_LAYER layer )
			{
				num = 0;
				index_layer = core::list<ICanvasLayer*>();
				layers_pointer = core::list<ICanvasLayer*>::Iterator();
				eclayer = layer;
			}
			E_CANVAS_LAYER eclayer;
			core::list<ICanvasLayer*> index_layer;
			core::list<ICanvasLayer*>::Iterator layers_pointer;
			int num;
		};


public:
	LayerManager( IArea* area_, IrrlichtDevice* device_ );
	~LayerManager(void);



public:

		inline LineCloudLayer* createLineCloudLayer (void)
		{
			return (LineCloudLayer*)createLayer( ECL_LINE_CLOUD );
		}

		inline TextureCacheFragmentedLayer* createTCFL (void)
		{
			return (TextureCacheFragmentedLayer*)createLayer( ECL_TEXTURE_CACHE_FRAGMENTED );
		}

		ICanvasLayer* createLayer ( E_CANVAS_LAYER type )
		{
			ICanvasLayer* result = 0;
			switch ( type )
			{
				case ECL_BACKGROUND_LAYER:
					{
						result = LFactory.createBackgroundLayer();
						break;
					}
				case ECL_LINE_CLOUD:
					{
						result = LFactory.createLineCloudLayer();
						break;
					}
				case ECL_TEXTURE_CACHE_FRAGMENTED:
					{
						result = LFactory.createTCFL();
						break;
					}
			}
			layer_cache[type].index_layer.push_back ( result );
			return result;
		}

		inline void mergeLayers ()
		{
			layer_line.clear();
			for ( int i = 0; i < layer_cache.size(); i++ )
			{
				core::list<ICanvasLayer*>& spare = layer_cache[i].index_layer;
				core::list<ICanvasLayer*>::Iterator it = spare.begin();
				
				while ( it != spare.end() )
				{
					layer_line.push_back( *it );
					it++;
				}
				layer_cache[i].layers_pointer = spare.getLast();
			}
		}

		void render ()
		{
			// TODO:::: layer stream // should be static and dynamic layers :D
			core::list<ICanvasLayer*>::Iterator it = layer_line.begin();

			while ( it != layer_line.end() )
			{
				(*it)->render();
				it++;
			}
		}
//
		LayerFactory LFactory;
		core::array<layer_bunch> layer_cache;
		core::list<ICanvasLayer*> layer_line;
		IrrlichtDevice* device;
};

