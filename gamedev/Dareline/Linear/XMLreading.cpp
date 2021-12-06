#include "XMLreading.h"


XMLreading::XMLreading( LayerManager* lmngr_, CacheManager* cmngr_ ) : lmngr ( lmngr_ ), cmngr ( cmngr_ )
{
	//REFACTOR:::: when domains will be implemented
	lcl = lmngr->createLineCloudLayer();
	tcfl = lmngr->createTCFL();
	device = lmngr->device;
	driver = device->getVideoDriver();
	texcache = cmngr->createTextureCache();
	starsyscache = cmngr->createGOCache( false );
	tcfl->setCaches( texcache, starsyscache );
}


XMLreading::~XMLreading(void)
{
}

