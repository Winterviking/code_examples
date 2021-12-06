#include "GenericCache.h"
//#include "StarSystem.h"
#include <ITexture.h>
#include "IGameObject.h"
#include <rect.h>
#include "IArea.h"

//typedef GenericCache<StarSystem> StarSystemCache;
typedef GenericCache<IGameObject> GameObjectCache;
typedef GenericCache<video::ITexture> TextureCache;
//typedef GenericCache<core::recti> RectCache;
//typedef GenericCache<IArea> AreaCache;
