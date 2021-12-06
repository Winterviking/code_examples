#pragma once
#include "igameobjectfactory.h"
class GameObjectFactory : public IGameObjectFactory
{
public:
	GameObjectFactory(void);
	~GameObjectFactory(void);

	IGameObject* addStarSystem( void );
};




