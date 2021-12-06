#pragma once

#include "StarSystem.h"

class IGameObjectFactory
{
public:

	IGameObjectFactory(void)
	{
	}

	virtual ~IGameObjectFactory(void)
	{
	}

	virtual IGameObject* addStarSystem( void ) = 0;
};

