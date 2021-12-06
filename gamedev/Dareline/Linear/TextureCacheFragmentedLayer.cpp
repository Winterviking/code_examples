//#include "TextureCacheFragmentedLayer.h"

/*
template<class T>
TextureCacheFragmentedLayer<T>::TextureCacheFragmentedLayer( IrrlichtDevice* device_ ) : ICanvasLayer(device_)
{
}

template<class T>
TextureCacheFragmentedLayer<T>::~TextureCacheFragmentedLayer(void)
{
}

template<class T>
void TextureCacheFragmentedLayer<T>::render()
{
	for ( int i = 0; i < gobjcache->data.size(); i++ )
	{
		int iddd = ((StarSystem*)((gobjcache->data[i]).ptr))->textureid;
		video::ITexture* tex = texcache->getPtrById( iddd );
		core::vector2di pos = gobjcache->data[i].ptr->position - gobjcache->data[i].ptr->shift;
		core::recti rec = ((StarSystem*)(gobjcache->data[i].ptr))->textureregion;
		driver->draw2DImage( tex, pos, rec,  0,video::SColor(255,255,255,255), true);
	}
}
*/