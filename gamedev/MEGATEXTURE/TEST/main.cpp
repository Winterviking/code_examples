

#include <stdio.h>
#include <conio.h>

// wut to test
#define __TEST_1__


#ifdef __TEST_1__

void main (void)
{


	int i = 0;
	for ( ; i < 10; i++ )
	{
		if ( i == 8 )
		break;
	}

	printf ( "%d", i );
	_getch();



}

#endif





