#ifndef __MACRO_H_INCLUDED__
#define __MACRO_H_INCLUDED__

#define STANDART_FOR_LOOP( a, b ) for ( int a = 0 ; a < b; a++ )
#define DEDICATED_FOR_LOOP( a, b, c ) for ( int a = c ; a < b; a++ )
#define SMART_FOR_LOOP( a, b, c, d ) for ( int a = c ; a < b; a += d )
#define ARRAY2D( a, l, x, y ) ( a [ x * l + y ] )


#define CLAMP( from, to, val ) if ( val < from )	\
									{val = from;}	\
								if ( val > to )		\
									{val = to;}		\




#endif // End of __MACRO_H_INCLUDED__