#pragma once

#include <irrlicht.h>

using namespace irr;

class IArea
{
public:

	IArea(void)
	{
	}

	virtual ~IArea(void)
	{

	}

	virtual bool test ( const core::vector2di& pos ) { return false; }


	IArea* parent;

	core::list<IArea*> children;
};

