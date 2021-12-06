#pragma once
#include "iareafactory.h"
class AreaFactory : public IAreaFactory
{
public:
	AreaFactory(void);
	~AreaFactory(void);

	// single rectangular area
	rectArea* createRectArea ( IArea* parent );
	// multiple rectangular area
//	MultipleRectArea* createMultiRectArea ( IArea* parent );
};

