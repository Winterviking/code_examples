#pragma once

#include "rectArea.h"

class IAreaFactory
{
public:

	IAreaFactory()
	{

	}

	~IAreaFactory(void)
	{
	}

	virtual rectArea* createRectArea ( IArea* parent ) = 0;
//	virtual MultipleRectArea* createMultiRectArea ( IArea* parent ) = 0;
	
};

