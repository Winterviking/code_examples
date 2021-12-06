


#include <conio.h>

#include <memory.h>

#include <irrlicht.h>

#include "macro.h"
#include "MipMapMesh.h"

#pragma comment ( lib, "irrlicht.lib" )

// REFACTOR????
// checker test cache
// true caching on disk

using namespace irr;
using namespace scene;
using namespace video;


struct grid_block
{
	
};

float vtc_to_tc ( float vtc )
{
	return 0.f;
}

void main (void)
{
	IrrlichtDevice* device = createDevice ( video::EDT_OPENGL, core::dimension2du ( 800, 600 ), 32U, false );
	video::IVideoDriver* driver = device->getVideoDriver();
	
	/*
	driver->setTextureCreationFlag ( video::ETCF_ALWAYS_32_BIT, true );//ARGB
	driver->setTextureCreationFlag ( video::ETCF_CREATE_MIP_MAPS, false );
	video::ITexture* tex = driver->addTexture ( core::dimension2du ( 2048, 2048 ), "mega2048.bmp" );

	char* mom = (char*)tex->lock();
	video::ECOLOR_FORMAT fmat = tex->getColorFormat();
	
	int color_size = 3;
//	driver->writeImageToFile(
	int block_quantity = 256;
	int max_block_size = 1;
	float width = 512.f;
	float height = 512.f;
	int virtu_tex_size = 2048;
	int cache_tex_size = 128;
	int quantity = virtu_tex_size / cache_tex_size;// 2048x2048 mega : 128x128 cache atom
	

	int block_type = 0; // STATIC GRID

	// 1 dimensioned array
	if( fmat == video::ECF_A8R8G8B8 )
	{
		printf("Texture Color were changed successfully");
//		driver->
//		mom[256] = 16;
	}
	else
		{return;}

	scene::SMesh* mesh = new scene::SMesh();

	mesh->MeshBuffers.clear();
	SMeshBuffer* buf = new SMeshBuffer();
	*/
	//TODO::::
	//indices
	//if recombine meshbuffer create new vertice
	//recreate indices
	// 2 different pipelines i should write :) 1st will use full memory
	
	// Vertices and tex coords
/*	switch ( block_type )
	{
		case 0:
		{
			// TODO :::: calculate proper offset, so will be no array repositioning
			buf->Vertices.set_used ( block_quantity * block_quantity * max_block_size );
//			int i( 0 ),j( 0 );
			int k = 0;
			float __width = width / ( block_quantity * max_block_size );
			float __height = height / ( block_quantity * max_block_size );
*//*
			float vtc_x ( 0 ), vtc_y ( 0 );// virtual texcoords for current megatexture
			float barrier_atom = 1.f / (float)quantity;
			float barrier_x ( barrier_atom ), barrier_y ( barrier_atom );
			float rtc_x ( 0.f ), rtc_y ( 0.f );
			float rtc_atom_x = __width / ( barrier_atom * width );
			float rtc_atom_y = __height / ( barrier_atom * height );
*//*
			STANDART_FOR_LOOP ( i, block_quantity * max_block_size )
			{
//				vtc_x = __width * i / width;
				STANDART_FOR_LOOP ( j, block_quantity * max_block_size )
				{
//					vtc_y = __height * j / height;

*//*
					if ( vtc_x >= barrier_x )
					{
						rtc_x = ( vtc_x - barrier_x ) / barrier_atom;
						barrier_x += barrier_atom;
					}
					else
					{
						rtc_x += rtc_atom_x;
					}

					if ( vtc_y >= barrier_y )
					{
						rtc_y = ( vtc_y - barrier_y ) / barrier_atom;
						barrier_y += barrier_atom;
					}
					else
					{
						rtc_y += rtc_atom_y;
					}
*//*
					S3DVertex& v = buf->Vertices[k++];
					v.Pos.set ( __width * i, 0, __height * j );
					v.Normal.set ( 0, 1, 0 );
					v.Color = 0x00FFFFFF;
//					v.TCoords.set( rtc_x, rtc_y );
				}			
			}
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
	};

	printf ( "\nvertices just have been created" );

	// INDICES!!!!!!!!



//	buf->Vertices.set_used (  );

	// clean shits
	buf->drop();
	mesh->drop();

// Spam


*/





	// Engine Stuff Must Be Added ^^


///// NEW STUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
/////*******************************************************************
/////*******************************************************************
/////*******************************************************************
/////*******************************************************************

	MipMapMesh* nir = new MipMapMesh();

	nir->preRender(device);

	delete nir;

























	device->drop();
	_getch();
}








