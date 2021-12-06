#pragma once

#include <irrXML.h>
#include <irrString.h>
//#include "TextureCache.h"
#include "GameObjectFactory.h"
#include "Cache.h"
#include "LayerManager.h"
#include "CacheManager.h"
//#include "Canvas.h"

using namespace irr;
using namespace io;

enum DATA_NODE_TYPE
{
	DNT_STARSYSTEM,
	DNT_TUNNEL,
	DNT_TEXTURE,
	DNT_NUMBER
};

struct machineryData
{
		
};

class XMLreading
{
public:
	XMLreading( LayerManager* lmngr_, CacheManager* cmngr_ );
	~XMLreading(void);

	struct machineryData
	{
		
	};

	// reads data
machineryData* readDataFromXML ( c8* path )
{
	// initiate
//	machineryData* mech = new machineryData;
	IrrXMLReader* xml = createIrrXMLReader ( path );

	// reading loop
	while ( xml->read() && xml )// TODO:::: optimize
	{
		// type caster
		switch ( xml->getNodeType() )
		{
			case EXN_ELEMENT:
			{
				if ( strcmp ( xml->getNodeName(), "canvas" ) )
				{
					if ( strcmp ( xml->getAttributeValueSafe("dimension"), "2d" ) )
					{
						readAttributes2D ( xml );
					}
					else if ( strcmp ( xml->getAttributeValueSafe("dimension"), "3d" ) )
					{
						readAttributes3D ( xml );
					}
				}
				break;
			}
			case EXN_ELEMENT_END:
			{

				break;
			}
		}
	}
	xml->~IIrrXMLReader();

	return 0;//mech;
}

void readAttributes2D ( IrrXMLReader* xml )
{
	// reading loop
	while ( xml->read() )
	{
		// Type Caster
		switch ( xml->getNodeType() )
		{
			case EXN_ELEMENT:
			{
				if ( !strcmp ( xml->getNodeName(), "texture" ) )
					{readAttributes2D ( DNT_TEXTURE, xml );}
				else if ( !strcmp ( xml->getNodeName(), "star" ) )
				{
					readAttributes2D ( DNT_STARSYSTEM, xml );
				}
				else if ( !strcmp ( xml->getNodeName(), "tunnel" ) )
				{
					readAttributes2D ( DNT_TUNNEL,xml );
				}
			}
			case io::EXN_ELEMENT_END: // Exit From this routine
			{
				break;
			}
		}
	}
}

void readAttributes3D ( IrrXMLReader* xml )
{
	// stub
}

void readAttributes2D ( DATA_NODE_TYPE type, IrrXMLReader* xml )
{
	switch ( type )
	{
		case DNT_STARSYSTEM:
		{
			StarSystem* newb = new StarSystem();
			newb->setID ( xml->getAttributeValueAsInt("id") );
			//TODO:::: add a bit freeedom to format
			//int flags;
			//0...0000[00000000]
			//................^. - position
			//...............^.. - textureregion
			// reading loop
			
			//REFACTOR:::: to subprogram returning StarSystem class :)
			bool read = true;
//			int id = -1;
			while ( xml->read() && read )
			{
				// Type Caster
				switch ( xml->getNodeType() )
				{
					case EXN_ELEMENT:
					{
						if ( !strcmp ( xml->getNodeName(), "position" ) )
						{
							newb->pos2d = core::vector2di( xml->getAttributeValueAsInt("x"), xml->getAttributeValueAsInt("y") );
							newb->setZOrder( xml->getAttributeValueAsInt("zorder") );
						}
						else if ( !strcmp ( xml->getNodeName(), "textureregion" ) )
						{
							newb->textureregion = core::recti (
								xml->getAttributeValueAsInt("ltx"),
								xml->getAttributeValueAsInt("lty"),
								xml->getAttributeValueAsInt("rbx"),
								xml->getAttributeValueAsInt("rby") );
							newb->texshift = core::vector2di( ( newb->textureregion.LowerRightCorner.X - newb->textureregion.UpperLeftCorner.X ) / 2, ( newb->textureregion.LowerRightCorner.Y - newb->textureregion.UpperLeftCorner.Y ) / 2 );
							newb->SetTexture ( texcache->getPtrById ( xml->getAttributeValueAsInt("id") ) );
						}
						break;
					}
					case EXN_ELEMENT_END:
					{
						read = false;
						break;
					}
				}
			}

			//TODO:::: i guess we should here fill layers or something lol :)
			// watch wut i can do here
			// class TextureCacheFragmentedLayer
			// input :: textureCache :::: ided texture :::: layer should be filled dynamically

			starsyscache->addPtr( /*(IGameObject*)*/newb, newb->getID() );
			break;
		}
		case DNT_TUNNEL:
		{
			lcl->addLine( 
					(starsyscache->getPtrById( xml->getAttributeValueAsInt( "idfrom" ) ) )->GetPostition(),
					(starsyscache->getPtrById( xml->getAttributeValueAsInt( "idto" ) ))->GetPostition()
			);
			break;
		}
		case DNT_TEXTURE:
		{
//			core::stringc l =  xml->getAttributeValueSafe ( "path" );
			cacheTexture( xml->getAttributeValueSafe("path"), xml->getAttributeValueAsInt( "id" ) );
			break;
		}
	}
}

void readAttributes3D ( DATA_NODE_TYPE type, IrrXMLReader* xml )
{
	//stub
}

void cacheTexture ( const io::path& path, const int& id )
{
	video::ITexture* tex = driver->getTexture ( path );
	driver->makeColorKeyTexture(tex, core::vector2di(0,0));

	texcache->addPtr( tex, id );
}


	LineCloudLayer* lcl;
	TextureCacheFragmentedLayer* tcfl;
	
	LayerManager* lmngr;
	CacheManager* cmngr;
	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	TextureCache* texcache;
	GameObjectCache* starsyscache;
//	PointerCache<IGameobject>* cache;
};








/*
// Paranthropus GS inc. 20_10
// License :: Freedom For Information
// Copyright (C) 2002-2005 Nikolaus Gebhardt ( IrrXML 1.2 )
// This file is a part of project "SCARAB"
// project version 1.0.1

// Short Description
// Reads data from XML

#ifndef __XML_READING_H_INCLUDED__
#define __XML_READING_H_INCLUDED__

#pragma once

// Native Headers
#include <string.h>
#include <malloc.h>

// Outsourcing Headers
#include "irrXML/irrXML.h"
#include "irrXML/irrString.h"

// Standart Headers
#include "templates__.h"
#include "enumerations.h"

// Namespaces
using namespace irr;
using namespace io;

// Data Structs
struct machineryData
{
	dynArrayVoidPtr domain;
};

// Array Type Caster Realization
void readAttributes ( END_TYPE data_type, IrrXMLReader* xml, dynArrayVoidPtr* what )
{
	// defaults
	bool exitFlag = true;
	int cntr = 0;

	int quantity = xml->getAttributeValueAsInt ( "quantity" );
	const char* element = xml->getNodeName();
////////////////////////////////////////////////////
	int length = 0;
	const char* p = element;
	while ( *p )
	{
		++length;
		++p;
	}
	char* eleme =( char* ) malloc ( sizeof ( char ) * ( length ) );

	strcpy ( eleme, element );

	///////////////////////////////////////////////
//	printf ( "%s \n", element );
	what->type = data_type;

	// Creates An Array By EndType ( enumeration )
	switch ( data_type )
	{
		// Array Of Arrays
		case ET_DYNARRAYVOIDPTR:
		{
			what->allocate < dynArrayVoidPtr > ( quantity );

			// reading loop
			while ( exitFlag && xml->read() )
			{
				// Type Caster
				switch ( xml->getNodeType() )
				{
					case EXN_ELEMENT:
					{
						if ( !strcmp ( xml->getAttributeValueSafe ( "data" ), "true" ) )
							{readAttributes ( ET_INTEGER, xml, &( ( dynArrayVoidPtr* )( what->data ) ) [ cntr ] );}
						else
							{readAttributes ( ET_DYNARRAYVOIDPTR, xml, &( ( dynArrayVoidPtr* )( what->data ) ) [ cntr ] );}
						cntr++;
						break;
					}
					case io::EXN_ELEMENT_END: // Exit From this routine
					{
						if ( !strcmp ( eleme, xml->getNodeName() ) )
						{
							exitFlag = false;
						}
						break;
					}
				}
			}
			break;
		}
		case ET_INTEGER:
		{
			what->allocate < int > ( quantity );

			// reading loop
			while ( xml->read() && exitFlag )
			{
				switch ( xml->getNodeType() )
				{
					case EXN_ELEMENT: // Enddata creation
					{
						( ( int* )( what->data ) ) [ cntr ] = xml->getAttributeValueAsInt ( "number" );
//						printf ( "%d", ( ( int* )( what->data ) ) [ cntr ] );
						cntr++;
						break;
					}
					case io::EXN_ELEMENT_END: // Exit from this routine
					{
						exitFlag = false;
						break;
					}
				}
			}
			break;
		}
	}
}

// Main Function To Call
machineryData* readDataFromXML ( c8* path )
{
	// initiate
	machineryData* mech = new machineryData;
	IrrXMLReader* xml = createIrrXMLReader ( path );

	// reading loop
	while ( xml->read() && xml )
	{
		// type caster
		switch ( xml->getNodeType() )
		{
			case EXN_ELEMENT:
			{
				if ( !strcmp ( xml->getNodeName(), "domain" ) )
				{
					if ( !strcmp ( xml->getAttributeValueSafe ( "data" ), "true" ) )
						{readAttributes ( ET_INTEGER, xml, &( mech->domain ) );}
					else
						{readAttributes ( ET_DYNARRAYVOIDPTR, xml, &( mech->domain ) );}
				}
				break;
			}
		}
	}
	xml->~IIrrXMLReader();

	return mech;
}

// Gets An Array By Numbers From machinery_data* struct ( templates___ header)))) )
dynArrayVoidPtr* getArray ( machineryData* mech, int* indices, int depth )
{
	dynArrayVoidPtr* ptr = &mech->domain;
	for ( int i = 0; i < depth; i++ )
		{ptr = &( ( ( dynArrayVoidPtr* ) ( ptr->data ) ) [ indices [ i ] ] );}
	return ptr;
}

#endif // End of __XML_READING_H_INCLUDED__
*/