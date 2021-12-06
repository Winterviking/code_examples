
//#ifndef __I_GAME_OBJECT_INCLUDED__
//#define __I_GAME_OBJECT_INCLUDED__

#pragma once

#include <irrlicht.h>

using namespace irr;

// TODO:::: must be relocated
//???? may be used & and * ( most likely ( so we can have values separated and maybe no that much mem waste ) )
struct UniTrans
{
	UniTrans () : tex( 0 ), pos2d( 0 ), texshift( 0 ), texregion( 0 ) {}// nullify pointers
	video::ITexture* tex;
//	core::list<video::ITexture*> texlist;
	core::vector2di* pos2d;
	core::vector2di* texshift;
	core::recti* texregion;
	// Scratch
	int GLOBAL_ID;
	int id;
	int z_order;
//	core::list<core::recti> texreglist;
};


// TODO :::: MAJOR CHANGES IN GAME_OBJECT interface !!!! whole program should be refined
class IGameObject
{
public:
	
	IGameObject( /*int gid*/ /*assigned by factory*/)
	{
	}

	virtual ~IGameObject(void)
	{
	}

	//TODO:::: every UniBusMember can be managed from here by stub ::: every function should be virtual ( so classes can add specific things )

	// REFACTOR:::: maby inline?

	// TEMP:::: all funcs are implemented, but virtual
	// REFACTOR:::: bus struct to pointers
	// real values should have get/set
	// at least getter should be coded for every member
	
	// Getters will be kinda non - safe

	// idea :::: all real memory should be taken by children :) Our Non-Abstract parent contain only pointers

	virtual UniTrans& getData()
		{return bus;}
	
	// REAL GET/SET
	// GLOBAL ID
	int getGID ()
		{return bus.GLOBAL_ID;}
	void setGID ( const int& gid )// just in case most likely be removed
		{bus.GLOBAL_ID = gid;}
	// LOCAL ID :::: may become more complicated if really needed
	int getID ()
		{return bus.id;}
	void setID ( const int& id )// just in case most likely be removed
		{bus.id = id;}
	// ZORDER
	int getZOrder ()
		{return bus.z_order;}
	void setZOrder ( const int& z_order )// just in case most likely be removed
		{bus.z_order = z_order;}

	// Scratch
	virtual void SetPosition ( const core::vector2di& position_ ) {}
	virtual void SetShift ( const core::vector2di& shift_ ) {}
	virtual void SetTexture ( video::ITexture* tex ) {}
	virtual void SetTextureArea ( const core::recti& texregion ) {}
	virtual void setData ( const UniTrans& data ) {/*bus = UniTrans( data );*/} // most likely teh main stub
	
	// Non Safe Getters
	virtual core::vector2di& GetPostition ()
		{return *bus.pos2d;}
	
	virtual core::vector2di& GetShift ()
		{return *bus.texshift;}

	virtual core::recti& GetTextureArea ()
		{return *bus.texregion;}

	// Safe Getters :)
	virtual video::ITexture* GetTexture ()
		{return bus.tex;}
protected:
	UniTrans bus;
};

//#endif // __I_GAME_OBJECT_INCLUDED__