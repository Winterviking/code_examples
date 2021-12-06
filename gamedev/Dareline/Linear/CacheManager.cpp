#include "CacheManager.h"


CacheManager::CacheManager(void)
{

}


CacheManager::~CacheManager(void)
{
	core::list<cache_keeper>::Iterator it = caches.begin();
	while ( it != caches.end() )
	{
		switch ( (*it).type )
		{
			case ECT_GAME_OBJECT:
			{
				GameObjectCache* todelete = (GameObjectCache*)(*it).cache;
				delete todelete;
				break;
			}
			case ECT_TEXTURE:
			{
				TextureCache* todelete = (TextureCache*)(*it).cache;
				delete todelete;
				break;
			}
		}
	}
}
