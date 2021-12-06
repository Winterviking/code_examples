#include "StarSystem.h"


StarSystem::StarSystem(void) : IGameObject ()/* a must :) for my pleasure */
{
	bus.pos2d = &pos2d;
	bus.texregion = &textureregion;
	bus.texshift = &texshift;
}


StarSystem::~StarSystem(void)
{
}
