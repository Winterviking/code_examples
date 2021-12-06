#pragma once
#include "igameobject.h"
class StarSystem : public IGameObject
{
public:
	StarSystem(void);
	~StarSystem(void);



	// TODO:::: Animamation Sequence might be implement :) if ill want it
	// ( most likely i will implement suitable animation system AKA animators )
//	video::ITexture* picture;
//	core::vector2di shift; // for texture displaying
//	core::recti textureregion;
//	int textureid;

	//TODO:::: maby change it to vector of coords :) after i implement domain system at all
//	int starsystem_id;
//	int z_order;

	// Setters
	void SetPosition ( const core::vector2di& position_ ) 
	{pos2d = position_;}
	void SetShift ( const core::vector2di& shift_ )
	{texshift = shift_;}
	void SetTexture ( video::ITexture* tex ) 
	{bus.tex = tex;}
	void SetTextureArea ( const core::recti& texregion ) 
	{textureregion = texregion;}

	void setData ( const UniTrans& data )// memory is safe nows
	{
		texshift = *data.texshift;
		pos2d = *data.pos2d;
		textureregion = *data.texregion;
		bus.tex = data.tex;
		//?????
		bus.GLOBAL_ID = data.GLOBAL_ID;
		bus.id = data.id;
		bus.z_order = data.z_order;
	}

	// real memory values
//	video::ITexture* tex;
	core::vector2di texshift;
	core::vector2di pos2d;
	core::recti textureregion;
};

