#include "MipMapMesh.h"

MipMapMesh::MipMapMesh(void) : block_amount ( 128 ), block_size ( 1 ), side_length ( 512.f ), block_type ( 0 )
{
	side = block_size * block_amount;
	/*__width = width / ( side );
	__height = height / ( side );*/
	sub_block_length = side_length / side;

	if ( ( side * side ) > 65536 )
	{
		bits_in_index = EIT_32BIT;
		indices = new CIndexBuffer ( EIT_32BIT );
	}
	else
	{
		bits_in_index = EIT_16BIT;
		indices = new CIndexBuffer ( EIT_16BIT );
	}
	// yesh we will never display it :)
	indices->setHardwareMappingHint( EHM_NEVER );

	// TODO:::: SCRATCH DEFAULTS !!!! 
	position = core::vector3df ( 0.f, 0.f, 0.f );
	rotation = core::vector3df ( 0.f, 0.f, 0.f );
	scale = core::vector3df ( 1.f, 1.f, 1.f );
}

MipMapMesh::~MipMapMesh(void)
{
}

/*
MipMapMesh::MipMapMesh(void) : width( 512.f ), block_quantity ( 256 ), block_type ( 0 ), 
	max_block_size ( 1 ), height ( 512.f ), cache_tex_size ( 128 ), lod_distance ( 34.f ),
	virtu_tex_size ( 2048 )
{
	side = block_quantity * max_block_size;
	__width = width / ( side );
	__height = height / ( side );

	int s_w = 0;
	if ( __width < __height )
	{
		s_w = lod_distance / __width;
	}
	else
	{
		s_w = lod_distance / __height;
	}

	offset = s_w;
}


MipMapMesh::~MipMapMesh(void)
{
}
*/