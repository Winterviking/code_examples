#include "AreaFactory.h"


AreaFactory::AreaFactory(void)
{
}


AreaFactory::~AreaFactory(void)
{
}

rectArea* AreaFactory::createRectArea ( IArea* parent )
{
	return new rectArea();
}

//MultipleRectArea* AreaFactory::createMultiRectArea ( IArea* parent );
//{
//	return new MultipleRectArea();	
//}
