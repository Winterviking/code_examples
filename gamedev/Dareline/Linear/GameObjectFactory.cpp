#include "GameObjectFactory.h"


GameObjectFactory::GameObjectFactory(void)
{
}


GameObjectFactory::~GameObjectFactory(void)
{
}

IGameObject* GameObjectFactory::addStarSystem()
{
	return new StarSystem();
}
