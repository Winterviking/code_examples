
#pragma once

#include <irrlicht.h>

#include "macro.h"
#include "types.h"

using namespace irr;
using namespace scene;
using namespace video;

class MipMapMesh
{
	// TODO::: DATA STRUCT
	struct LODwell
	{
		// we shift this group of structs simultaneously [o]____[o]
		// ints are signed coz we can go to negative values =)
		struct
		{
			int f_x;
			int f_y;
			int t_x;
			int t_y;
		} left_wall;
		struct
		{
			int f_x;
			int f_y;
			int t_x;
			int t_y;
		} right_wall;
		struct
		{
			int f_x;
			int f_y;
			int t_x;
			int t_y;
		} top_wall;
		struct
		{
			int f_x;
			int f_y;
			int t_x;
			int t_y;
		} bottom_wall;
		// square for detections
		float from_x;
		float from_y;
		float to_x;
		float to_y;

		int number_of_LOD;

		IIndexBuffer* indices;

		bool enabled;
	};
public:
	MipMapMesh(void);
	~MipMapMesh(void);

/*	IMeshBuffer* createSquare16() // May be useful :)
	{
		if ( side > 128 )
			{return 0;}

		SMeshBuffer* buf = new SMeshBuffer();

		// Vertices
		switch ( block_type )
		{
			case 0:
			{
				buf->Vertices.set_used ( side * side );

				int k = 0;
				STANDART_FOR_LOOP ( i, side )
				{
					STANDART_FOR_LOOP ( j, side )
					{
						S3DVertex& v = buf->Vertices[k++];
						v.Pos.set ( sub_block_length * i, 0, sub_block_length * j );
						v.Normal.set ( 0, 1, 0 );// SHOULD BE REDONE
						v.Color = 0x00000000;
					}			
				}
				break;
			}
		}

		printf ( "vertices have been created" );

		return (IMeshBuffer*)buf;
	}
	*/

		//grid scheme
		//
		//(0,0,0).1.4.7 ==>z
		// ||x   .2.5.8 
		// \/    .3.6.9
		//
		// vertices [1----9]
	IDynamicMeshBuffer* createSquare()
	{
		if ( side > 1024 )
			{return 0;}
		
		// Autodecision
		CDynamicMeshBuffer* buf = new CDynamicMeshBuffer( video::EVT_STANDARD, bits_in_index );

		// VBO
		buf->setHardwareMappingHint ( EHM_STATIC, EBT_VERTEX );
		buf->setHardwareMappingHint ( EHM_DYNAMIC, EBT_INDEX ); // EHM_STREAM can be better

		// Creation
		switch ( block_type )
		{
			case 0:
			{
				buf->getVertexBuffer().set_used ( side * side );

				int k = 0;
				STANDART_FOR_LOOP ( i, side )
				{
					STANDART_FOR_LOOP ( j, side )
					{
//						S3DVertex& v = ( (S3DVertex*) buf->getVertices() )[k++]; // ghey :)
						S3DVertex& v = buf->getVertexBuffer()[k++];
						v.Pos.set ( sub_block_length * i, 0, sub_block_length * j );
						v.Normal.set ( 0, 1, 0 );// SHOULD BE REDONE
						v.Color = 0xFFFFFFFF;
					}			
				}
				break;
			}
		}
		printf ( "vertices have been created" );
		return buf;
	}

	// Indices
	inline void CreateSquareIndices(void)
	{
		int cellamount = side; //- 1; //- 1;
		STANDART_FOR_LOOP ( i, cellamount )
		{
			STANDART_FOR_LOOP ( j, cellamount )
			{
				int index11 = j + i * cellamount;
				int index12 = j + 1 + i * cellamount;
				int index21 = j + ( i + 1 ) * cellamount;
				int index22 = j + 1 + ( i + 1 ) * cellamount;

				indices->push_back ( index11 );
				indices->push_back ( index12 );
				indices->push_back ( index21 );
// DEBUG:::: "checker"
				indices->push_back ( index12 );
				indices->push_back ( index21 );
				indices->push_back ( index22 );
// correct :)
				//indices->push_back ( index12 );
				//indices->push_back ( index22 );
				//indices->push_back ( index21 );
			}
		}
//		indices->
		printf ( "\n indices have been created " );
	}

	// COPY SQUARE from_x - begins from 0 liek arrays
	// TODO:: optimize em to fully pointer - style copying
	IIndexBuffer* copyIndexBufferRegion ( IIndexBuffer* emitter, IIndexBuffer* receiver, int from_x, int from_y, int to_x, int to_y )
	{
		printf ( "reg_" );
		if ( from_x == to_x || from_y == to_y )
			{return receiver;}

		if ( receiver == 0 )
		{
			receiver = new CIndexBuffer ( bits_in_index );
//			receiver->setHardwareMappingHint ( EHM_STREAM );
		}

		const int indices_in_polygon = 6;
		
		int shift_i = ( side/* - 1*/ ) * indices_in_polygon;
		if ( bits_in_index == EIT_32BIT )
		{
			INT32* ptr = 0;
			INT32* ptr_to = 0;
			DEDICATED_FOR_LOOP ( i, to_x, from_x )
			{
				DEDICATED_FOR_LOOP ( j, to_y, from_y )
				{
					ptr = &((INT32*)emitter->getData())[ shift_i * i + j * indices_in_polygon ];
					ptr_to = ptr + ( indices_in_polygon );
					while ( ptr != ptr_to )
					{
						receiver->push_back( *ptr );
						ptr++;
					}
				}
			}
		}
		else
		{
			INT16* ptr = 0;
			INT16* ptr_to = 0;
			DEDICATED_FOR_LOOP ( i, to_x, from_x )
			{
				DEDICATED_FOR_LOOP ( j, to_y, from_y )
				{
					ptr = &((INT16*)emitter->getData())[ shift_i * i + j * indices_in_polygon ];
					ptr_to = ptr + ( indices_in_polygon );
					while ( ptr != ptr_to )
					{
						receiver->push_back( *ptr );
						ptr++;
					}
				}
			}
		}
		//ghey var
/*		
		int shift_i = ( side - 1 ); //* ;

		DEDICATED_FOR_LOOP ( i, to_x, from_x )
		{
			DEDICATED_FOR_LOOP ( j, to_y, from_y )
			{
				// u32/u16 optimization possibility :) we should work directly with pointers watch memcpy code lol
				u32 indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon ];
				receiver->push_back( indx );
				indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon + 1 ];
				receiver->push_back( indx );
				indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon + 2 ];
				receiver->push_back( indx );
				indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon + 3 ];
				receiver->push_back( indx );
				indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon + 4 ];
				receiver->push_back( indx );
				indx = emitter[ i * shift_i * indices_in_polygon + j * indices_in_polygon + 5 ];
				receiver->push_back( indx );
			}
		}
*/

		// TODO :::::: Maybe must be called after composition
//		receiver->setDirty();
		return receiver;
	}

	void updateLODwell ( LODwell& lod, int dir_x, int dir_y )
	{
		
	}

	// TODO creation of LOD well structs
	void createLODwells ( int vcc_x = 0, int vcc_y = 0, int offset = 3, int offsetScaleCoeff = 2, int detectorOffset = 1 ) // TODO:::: STRONG DEBUG
	{
		// DEBUG:::: arguments
		vcc_x = side / 9;
		vcc_y = side / 2;
//		int offset = 3;
//		int offsetScaleCoeff = 2;
//		int detectorOffset = 1;

		// create LOD structs
		int cnt = offset;
		int detoffcnt = detectorOffset;
		int pow = 0;
		LODwell newLOD;
		LODwell oldLOD;
		printf ( "\n lod beggin " );

		do
		{
//			LODwell newLOD;
//			LODwell oldLOD;
			
			cnt *= ( pow ? offsetScaleCoeff : 1 );

			// TODO :::: real positions from scratch
			newLOD.from_x = position.X + ( vcc_x - 0.5f - detoffcnt ) * sub_block_length;
			newLOD.from_y = position.Y + ( vcc_y - 0.5f - detoffcnt ) * sub_block_length;
			newLOD.to_x = position.X + ( vcc_x + 0.5f + detoffcnt ) * sub_block_length;
			newLOD.to_y = position.Y + ( vcc_y + 0.5f + detoffcnt ) * sub_block_length;

			// TODO:::: Virtual cell coords : must be debugged btw
			newLOD.number_of_LOD = pow;
			newLOD.enabled = false; // as default ^^

			// TODO:::: optimize memory usage ^^ mabey later :) at least i should think about it
			// TODO:::: optimization is possible : we kinda not need 400000 same values in 1 struct :)
			if ( pow == 0 ) // Central Well is not a well et all :D
			{
				// whole square can be put into 1 struct
				newLOD.left_wall.f_x = vcc_x - cnt;
				newLOD.left_wall.f_y = vcc_y - cnt;
				newLOD.left_wall.t_x = vcc_x + cnt;
				newLOD.left_wall.t_y = vcc_y + cnt;
				// correction
				newLOD.right_wall.t_x = vcc_x + cnt;
				newLOD.right_wall.t_y = vcc_y + cnt;
			}
			else // TODO:::: actually we need 8 values to describe a well, not 16 :)
			{
				// TODO :::: Actually a bug here :) we must use OldLOD roght values :) And add those 2 values 2 1st LOD
				// outer square
				newLOD.left_wall.f_x = vcc_x - cnt;
				newLOD.left_wall.f_y = vcc_y - cnt;
				newLOD.right_wall.t_x = vcc_x + cnt;
				newLOD.right_wall.t_y = vcc_y + cnt;

				// left wall
				newLOD.left_wall.t_x = oldLOD.left_wall.f_x;
				newLOD.left_wall.t_y = newLOD.right_wall.t_y;

				// right wall
				newLOD.right_wall.f_x = oldLOD.right_wall.t_x;
				newLOD.right_wall.f_y = newLOD.left_wall.f_y;

				// bottom wall
				newLOD.bottom_wall.f_x = oldLOD.left_wall.f_x;
				newLOD.bottom_wall.f_y = newLOD.left_wall.f_y;
				newLOD.bottom_wall.t_x = oldLOD.right_wall.t_x;
				newLOD.bottom_wall.t_y = oldLOD.left_wall.f_y;

				// top wall
				newLOD.top_wall.f_x = oldLOD.left_wall.f_x;
				newLOD.top_wall.f_y = oldLOD.right_wall.t_y;
				newLOD.top_wall.t_x = oldLOD.right_wall.t_x;
				newLOD.top_wall.t_y = newLOD.left_wall.t_y;
			}

			lods.push_back ( newLOD );
			oldLOD = newLOD;

//			cnt *= offsetScaleCoeff; Suposed  to be here but we need this trik
			detoffcnt *= offsetScaleCoeff;
			pow++;
		}
		while ( cnt < side );
		printf ( "\n lod end " );

		// we created maximum amount of lodes which can be used in rendering of mesh
	}

	// TODO::: Composition of index buffer :) square case is handled nows
	IIndexBuffer* compose ( LODwell& lod_, bool square = false, bool clamp = true )
	{
		printf ( " composi b " );
		// buffering
		LODwell lod = lod_;

		// clamp borders
		if ( clamp )
		{
			CLAMP ( 0, side - 1, lod.left_wall.f_x )
			CLAMP ( 0, side - 1, lod.left_wall.t_x )
			CLAMP ( 0, side - 1, lod.left_wall.f_y )
			CLAMP ( 0, side - 1, lod.left_wall.t_y )
			CLAMP ( 0, side - 1, lod.right_wall.f_x )
			CLAMP ( 0, side - 1, lod.right_wall.t_x )
			CLAMP ( 0, side - 1, lod.right_wall.f_y )
			CLAMP ( 0, side - 1, lod.right_wall.t_y )
			CLAMP ( 0, side - 1, lod.top_wall.f_x )
			CLAMP ( 0, side - 1, lod.top_wall.t_x )
			CLAMP ( 0, side - 1, lod.top_wall.f_y )
			CLAMP ( 0, side - 1, lod.top_wall.t_y )
			CLAMP ( 0, side - 1, lod.bottom_wall.f_x )
			CLAMP ( 0, side - 1, lod.bottom_wall.t_x )
			CLAMP ( 0, side - 1, lod.bottom_wall.f_y )
			CLAMP ( 0, side - 1, lod.bottom_wall.t_y )
		}
		IIndexBuffer* temp = 0;
		temp = copyIndexBufferRegion ( indices, temp, lod.left_wall.f_x,lod.left_wall.f_y, lod.left_wall.t_x, lod.left_wall.t_y );
		if ( !square )
		{
			temp = copyIndexBufferRegion ( indices, temp, lod.right_wall.f_x,lod.right_wall.f_y, lod.right_wall.t_x, lod.right_wall.t_y );
			temp = copyIndexBufferRegion ( indices, temp, lod.top_wall.f_x,lod.top_wall.f_y, lod.top_wall.t_x, lod.top_wall.t_y );
			temp = copyIndexBufferRegion ( indices, temp, lod.bottom_wall.f_x,lod.bottom_wall.f_y, lod.bottom_wall.t_x, lod.bottom_wall.t_y );
		}
		printf ("composi end");
		return temp;
	}

	void getSpecificWell ( int x, int y )
	{
		
	}

	// TODO:::: MAJOR DEBUG CODE
	// Prolly we write here generic usage of written funcs to prepare all structs for rendering
	// Then In render struct we just get a device ready and render on it meshbuffer every loopframe ( without update ^^ )

	// DEBUG:::: 
	void preRender ( IrrlichtDevice* device )
	{
		// main vertex buffer
		IDynamicMeshBuffer* buffer = createSquare();
		// main index buffer
		CreateSquareIndices();
		createLODwells();
		//(lods.begin()++)->indices = compose( *(lods.begin()++) );

		// MAIN TESTS ARE HERE
		IIndexBuffer* indx = compose( *(lods.begin()+2));//,true );

		buffer->setIndexBuffer( indx );
//		buffer->setIndexBuffer( indices );
		buffer->setHardwareMappingHint(EHM_STATIC);
		device->getSceneManager()->addCameraSceneNodeFPS();
		while(device->run())
		{
			device->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

			device->getVideoDriver()->drawMeshBuffer( buffer );

			device->getSceneManager()->drawAll();

			device->getVideoDriver()->endScene();
		}
	}

	// DEBUG:::: 
	void Render ()
	{
		
	}
















public:
	int block_amount;
	int block_size;
	int side;

	float side_length;
	float sub_block_length;

	int block_type;

	// TODO :::: refactor :::: all params should be moved to categorized structs
	struct params
	{
	
	};

	core::list<LODwell> lods;

	// TODO:::: scratch ( maybe they'll be available after inheritance )
	core::vector3df position;
	core::vector3df rotation;
	core::vector3df scale;


	IIndexBuffer* indices;
	E_INDEX_TYPE bits_in_index;
//	position2d<u32> virtual_center;



//	int color[0xF]; // LOD colors
};











/*


class MipMapMesh
{
public:
	MipMapMesh(void);
	~MipMapMesh(void);
public:
	SMeshBuffer* createSquareVertexArray( int color ) 
	{
		SMeshBuffer* buf = new SMeshBuffer();

		// Vertices
		switch ( block_type )
		{
			case 0:
			{
				//grid
				//(0,0,0).1.4.7 ==>z
				// ||x   .2.5.8 
				// \/    .3.6.9
				//
				// vertices [1----9]
				buf->Vertices.set_used ( side * side + offset * 4 * 2 );

				int k = 0;
				STANDART_FOR_LOOP ( i, side )
				{
					STANDART_FOR_LOOP ( j, side )
					{
						S3DVertex& v = buf->Vertices[k++];
						v.Pos.set ( __width * i, 0, __height * j );
						v.Normal.set ( 0, 1, 0 );// SHOULD BE REDONE
						v.Color = color;
					}			
				}
				break;
			}
		};

		printf ( "\nvertices just have been created" );
		return buf;
	}

	void recalculateIndices ( SMeshBuffer* buf, int pos_x, int pos_y )
	{
		int f_x ( pos_x - offset ),
			f_y ( pos_y - offset ),
			t_x ( pos_x + offset ),
			t_y ( pos_y + offset );
		// TODO:: add border handling
		if ( t_x > side )
			{t_x = side;}
		if ( f_x < 0 )
			{f_x = 0;}
		if ( t_y > side )
			{t_y = side;}
		if ( f_y > 0 )
			{f_y = 0;}

		// additional vertices

		// indices
	}

	void update ( int pos_x, int pos_z )
	{
		
	}

	scene::SMesh* createMesh()
	{
		// texture data
		//int virtu_tex_size = 2048;
		//int cache_tex_size = 128;
		//int quantity = virtu_tex_size / cache_tex_size;// 2048x2048 mega : 128x128 cache atom

		//// geometry data
		//int block_quantity = 256;
		//int max_block_size = 1;
		//float width = 512.f;
		//float height = 512.f;
		//
		//int block_type = 0; // STATIC GRID


		scene::SMesh* mesh = new scene::SMesh();

		mesh->MeshBuffers.clear();
		SMeshBuffer* buf = createSquareVertexArray( 0x00FFFFFF );


		// Vertices and tex coords

		printf ( "\nvertices just have been created" );

	}
private:

	int virtu_tex_size;
	int cache_tex_size;
//	int quantity;// 2048x2048 mega : 128x128 cache atom

	// geometry data
	int block_quantity;
	int max_block_size;
	int side;
	float width;
	float height;

	float texture_scale;

	float lod_distance;
	
	int offset;

	int block_type; // STATIC GRID
};
*/
