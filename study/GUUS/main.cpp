

#include <stdio.h>

#include "types.h"

void main (void)
{
//	int marx = 5 / 2;
//	printf ( "%i", marx );
	MultidiagonalMatrix m = MultidiagonalMatrix();
	m.setLengthCache(7,30);
	m.setLengthCache(7,10);
	m.recreateMatrix(1);
	m.printMatrixOut();


	// SHIFT APPROACH

	_getchar_nolock();
}










