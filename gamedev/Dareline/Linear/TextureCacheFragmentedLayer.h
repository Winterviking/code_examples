#pragma once
#include "icanvaslayer.h"
//#include "StarSystem.h"

#include "Cache.h"

//REFACTOR::::: MAKE IT A BIT MOAR GENERAL : LET IT BE INTERFACE ( then we just will call functions with standartized cache datasources )

//TODO::::
//1)must be generic
//2)must be added template cache with transition struct manager ( cache system manager ) for memory management
//3)relation simplification ( via struct and 1 function call )


// TODO:::: delete template thing
//template < class T >
class TextureCacheFragmentedLayer : public ICanvasLayer
{
public:
	TextureCacheFragmentedLayer( IrrlichtDevice* device_ ) : ICanvasLayer(device_)
	{}
	~TextureCacheFragmentedLayer(void)
	{}

//	void render();

	void setCaches ( TextureCache* cach1, GameObjectCache* cach2 )
	{
		texcache = cach1;
		gobjcache = cach2;
	}

	void TextureCacheFragmentedLayer::render()
	{
		for ( int i = 0; i < gobjcache->data.size(); i++ )
		{
			//int iddd = ((StarSystem*)((gobjcache->data[i]).ptr))->textureid;
			//video::ITexture* tex = texcache->getPtrById( iddd );
			//core::vector2di pos = gobjcache->data[i].ptr->position - gobjcache->data[i].ptr->shift;
			//core::recti rec = ((StarSystem*)(gobjcache->data[i].ptr))->textureregion;
//			video::ITexture* tex = gobjcache->getPtrByNumber(i)->getData().tex;
//			core::vector2di pos = gobjcache->getPtrByNumber(i)->getData().pos2d - gobjcache->getPtrByNumber(i)->getData().texshift;
//			core::recti rec = gobjcache->getPtrByNumber(i)->getData().texregion;
			UniTrans& link = gobjcache->getPtrByNumber(i)->getData();
			driver->draw2DImage( link.tex, *link.pos2d - *link.texshift, *link.texregion, 0,video::SColor(255,255,255,255), true);
		}
	}

	TextureCache* texcache;
	GameObjectCache* gobjcache;
};
/*template < class T >
class TextureCacheFragmentedLayer : public ICanvasLayer
{
public:
	TextureCacheFragmentedLayer( IrrlichtDevice* device_ );
	~TextureCacheFragmentedLayer(void);

	void render();

	void setCaches ( TextureCache* cach1, T* cach2 )
	{
		texcache = cach1;
		gobjcache = cach2;
	}

	TextureCache* texcache;
	T* gobjcache;
};
*/


