// Paranthropus GS inc. 2012
// Project GUUS 0.1
#pragma once

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdio.h>

//algorythm
//0-fill em with 0
//1-fill em with randoms

class MultidiagonalMatrix
{
public:
	MultidiagonalMatrix ( const int& algorythm_, const int& diagonal_number_ = 1, const int& side_length_ = 1 )
	{
		length_cache = 0;
		setLengthCache ( diagonal_number_, side_length_ );
		recreateMatrix ( algorythm_ );
	}
	MultidiagonalMatrix ()
	{
		length_cache = 0;
		main_array = 0;
		side_length = 0;
		diagonal_number = 0;
	}
	~MultidiagonalMatrix ()
		{clean();}
public:
	void recreateMatrix ( const int& algorythm_ )
	{
		if ( length_cache )
		{
			if ( main_array )
			{
				for ( int i = 0; i < diagonal_number; i++ )
				{
					for ( int j = 0; j < length_cache[i]; j++ )
					{

						main_array[i][j]=0;
					}
				}
			}
			else
			{
				reallocate();
			}
			switch ( algorythm_ )
			{
				case 0:
				{
					// random
					for ( int i = 0; i < diagonal_number; i++ )
					{
						for ( int j = 0; j < length_cache[i]; j++ )
						{
							main_array[i][j]=0;//TODO:: MAH RANDOM COPYPASTE PLOX
						}
					}
				}
				break;
				case 1:// mah task :) useless irl, still :)
				{
					int counter = 0;
					int N = 14;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=3.15f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=2.6f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=1.37f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=((float)N+(float)j)/100.f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=1.37f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=2.6f;}
					counter++;
					for ( int j = 0; j < length_cache[counter]; j++ )
						{main_array[counter][j]=3.15f;}

				}
				break;
				case 2:// file io
				{
				}
				break;
				default://error
				{
					printf("ERROR::\n");
				}
				break;
			}
		}
		else
		{
			printf ( "ERROR::\n" );
		}
	}

	void printMatrixOut ()
	{
		if ( main_array && length_cache )
		{
			for ( int i = 0; i < diagonal_number; i++ )
			{
				for ( int j = 0; j < length_cache[i]; j++ )
				{
					printf("%5.2f ", main_array[i][j] );
				}
				printf("\n");
			}
		}
	}

	// NO!!! NEED OTHER APPROach :)
	inline double getNumber ( const int& x, const int& y ) // NO NONONONONONONO
	{
	 	int lborder, rborder;
		if ( diagonal_number == 1 )
			{lborder = y;}
		else
		{
			lborder = - diagonal_number / 2 + y;
		}
		rborder = diagonal_number + lborder;
		if ( lborder <= x < rborder )
			{return main_array[y][x];}
		else
			{return 0;}
	}

	void setLengthCache ( const int& diagonal_number_, const int& side_length_ )
	{
		if ( diagonal_number_ % 2 == 1 )
		{
			if ( diagonal_number_ != diagonal_number )
			{
				if ( length_cache )
					delete [] length_cache;
				length_cache = new int[diagonal_number_];
				diagonal_number = diagonal_number_;
			}
			side_length = side_length_;
			int different = diagonal_number_ / 2;
			int loop_cntr = 0;
			for ( int i = 0; i < diagonal_number_ / 2; i++ )
			{
				length_cache[loop_cntr] = side_length_ - different;
				different--;
				loop_cntr++;
			}
			length_cache[loop_cntr] = side_length_;
			for ( int i = diagonal_number_ / 2 - 1; i >= 0 ; i-- )
			{
				different++;
				loop_cntr++;
				length_cache[loop_cntr] = side_length_ - different;
			}
			//DEBUG
			for ( int i = 0; i < diagonal_number_; i++ )
			{
				printf ( "%i ", length_cache[i] );
			}
			printf("\n");
		}
		else
		{
			printf ( "ERROR::\n" );
		}
	}

	void clean ()
	{
		deallocate();
		delete [] length_cache;
		length_cache = 0;
		side_length = 0;
		diagonal_number = 0;
	}

private:
	double** main_array;
	int* length_cache;
	int side_length;
	int diagonal_number;
	
	void deallocate ()
	{
		if (main_array)
		{
			for ( int i = 0; i < diagonal_number; i++ )
			{
				if ( main_array[i] )
				{
					delete [] main_array[i];
				}
			}
		}
		delete [] main_array;
		main_array = 0;
	}

	void reallocate ()
	{
		if ( main_array )
			{deallocate();}
		if ( length_cache )
		{
			main_array = new double*[diagonal_number];
			if (main_array)
			{
				for ( int i = 0; i < diagonal_number; i++ )
				{
					main_array[i]=new double[length_cache[i]];
					for ( int j = 0; j < length_cache[i]; j++ )
					{
						main_array[i][j]=0;
					}
				}
			}
		}

	}
};


#endif // End of TYPES_H_INCLUDED

