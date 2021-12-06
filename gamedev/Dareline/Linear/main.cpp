#include <irrlicht.h>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "Canvas.h"
//#include "GenericCache.h"
//#include "PointerCache.h"
//#include "XMLreading.h"

// demou

//class hui
//{
//public:
//	hui () {}
//	~hui () {}
//
//	int head[40];
//};

void main (void)
{
/*	GenericCache<hui>* na = new GenericCache<hui> ( true );
	hui* inst = new hui();
	na->addPtr(inst,1 );
	delete na;
*/
/*	GenericCache<video::ITexture> na;
	na.addPtr(0,2 );
	na.addPtr(0,4 );
	na.addPtr(0,3 );
	na.addPtr(0,1 );

	printf ( "%d", na.getPtrById(3) );
	printf ( "%d", na.getPtrById(4) );
	printf ( "%d", na.getPtrById(2) );
	printf ( "%d", na.getPtrById(1) );
	*/
/**/
	Canvas* can = new Canvas();

	can->readLayers();
	can->run_loop();

	delete can;
//*/

	//int* arm = 0;
	//int& mas = *arm;
	//int i = mas + 1;



	//Canvas* can = new Canvas();
	//
	//// XML INPUT REQUIRED :::: Basic Game Object implementation

	//// Program creates layers :) igameobject points different objects in list memory so we can change values in runtime ^^
	//LineCloudLayer* lay = can->createLineCloudLayer();

	//lay->addLine( core::line2di( 0,0,300,50 ) );
	//lay->addLine( core::line2di( 300,50,54,67 ) );
	//lay->addLine( core::line2di( 54,67,91,187 ) );
	//lay->addLine( core::line2di( 91,187,101,250 ) );
	//lay->addLine( core::line2di( 101,250,400,400 ) );

	//can->run_loop();
	//z
	//delete can;

	//PointerCache<video::ITexture> na;
	//na.addPtr(0,2 );
	//na.addPtr(0,4 );
	//na.addPtr(0,3 );
	//na.addPtr(0,1 );

	//printf ( "%d", na.getPtrById(3) );
	//printf ( "%d", na.getPtrById(4) );
	//printf ( "%d", na.getPtrById(2) );
	//printf ( "%d", na.getPtrById(1) );


	getchar();
}










