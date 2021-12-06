#pragma once

#include <irrlicht.h>

using namespace irr;



template<class T>
class PointerCache
{
public:
typedef struct ptr_cache
{
	ptr_cache ( T* ptr_, const int& id_ ) : id ( id_ ), ptr ( ptr_ ) {}
	int id;
	T* ptr;

	inline bool operator < ( const ptr_cache& other ) const
	{
		if ( ( id < other.id ) )
			return true;
		else 
			return false;
    }
} intern;

public:

	PointerCache(void) : is_sorted ( false )
	{
	}

	virtual ~PointerCache(void)
	{
	}

	void addPtr ( T* data_ptr_, const int& id_ )
	{
		data.push_back( intern( data_ptr_, id_ ) );
		if ( is_sorted )
			is_sorted = false;
	}

	T* getPtrById ( const int& id )
//	int getPtrById ( const int& id )
	{
		if( !is_sorted )
			data.sort();
		int val = binary_search ( id, 0, data.size() - 1 );
		if ( val==-1 )
			return 0; 
		else
			return data[val].ptr;
//			return data[val].id;
	}

	// kinda overload
	s32 binary_search( const int& id , s32 left, s32 right) const
	{
		if (!data.size())
			return -1;
	
		s32 m;
	
		do
		{
			m = (left+right)>>1;
			
			if (id < data[m].id )
				right = m - 1;
			else
				left = m + 1;
			
		} while((id < data[m].id || data[m].id < id) && left <= right );

		if (!(id < data[m].id ) && !(data[m].id < id))
			return m;
			
		return -1;
	}


	core::array<intern> data;
	bool is_sorted;
};

