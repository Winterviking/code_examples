#include "defArea.h"


defArea::defArea ( video::ITexture* cursor_, core::recti& area ) : z_order( -30000 ), id ( 0 ), cursor ( cursor_ ),rctngl ( area )
{
}


defArea::~defArea(void)
{
}
