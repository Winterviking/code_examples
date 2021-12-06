#pragma once

#include <irrlicht.h>

using namespace irr;

typedef struct tex_construct
{
	tex_construct ( video::ITexture* ptr_, const int& id_ ) : id ( id_ ), texture ( ptr_ ) {}
	int id;
	video::ITexture* texture;

	// TEST
	inline bool operator < ( const tex_construct& other ) const
	{
		if ( ( id < other.id ) )
			return true;
		else 
			return false;
    }
} txture;

class TextureCache// : public core::array<txture>
{
public:

public:
	TextureCache(void);
	~TextureCache(void);

	void addTexture ( video::ITexture* texture_, const int& id_ )
	{
		textures.push_back( txture( texture_, id_ ) );
		if ( is_sorted )
			is_sorted = false;
	}

	video::ITexture* getTextureById ( const int& id )
//	int getTextureById ( const int& id )
	{
		if( !is_sorted )
			textures.sort();
		int val = binary_search ( id, 0, textures.size() - 1 );
		if ( val==-1 )
			return 0; 
		else
			return textures[val].texture;
//			return textures[val].id;
	}

	// kinda overload
	s32 binary_search( const int& id , s32 left, s32 right) const
	{
		if (!textures.size())
			return -1;
	
		s32 m;
	
		do
		{
			m = (left+right)>>1;
			
			if (id < textures[m].id )
				right = m - 1;
			else
				left = m + 1;
			
		} while((id < textures[m].id || textures[m].id < id) && left <= right );

		if (!(id < textures[m].id ) && !(textures[m].id < id))
			return m;
			
		return -1;
	}


	core::array<txture> textures;
	bool is_sorted;
};

