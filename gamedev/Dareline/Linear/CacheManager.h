#pragma once

#include "Cache.h"

// Cache Factory


enum E_CACHE_TYPE
{
	ECT_GAME_OBJECT,
	ECT_TEXTURE,
	ECT_NUMBER
};

class CacheManager
{
private:
	struct cache_keeper
	{
		void* cache;
		E_CACHE_TYPE type;
	};
public:
	CacheManager(void);
	~CacheManager(void);

	GameObjectCache* createGOCache( bool managed )
	{
		cache_keeper keep;
		GameObjectCache* res = new GameObjectCache( managed );
		keep.cache = ( void* )res;
		keep.type = ECT_GAME_OBJECT;
		return res;
	}

	TextureCache* createTextureCache()
	{
		cache_keeper keep;
		TextureCache* res = new TextureCache( false );
		keep.cache = ( void* )res;
		keep.type = ECT_TEXTURE;
		return res;
	}
private:
	core::list<cache_keeper> caches;
};

