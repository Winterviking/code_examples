#pragma once

#include <irrlicht.h>

using namespace irr;

template< class T >
class GenericCache
{
private:
//	template<class T>
	typedef struct cache
	{
		cache ( T* ptr_, const int& num_/*, bool is_managed_*/ ) : ptr ( ptr_ ), sort_id ( num_ )/*, is_managed ( is_managed_ )*/
		{}
		~cache ()// autodeletion ( gheeeeeeeey )
		{
//			if ( managed )
//				delete ptr;
		}

		T* ptr;
		int sort_id;
		
		inline bool operator < ( const cache& other ) const
		{
			if ( ( sort_id < other.sort_id ) )
				return true;
			else 
				return false;
		}

		//T* retrieve_ptr ()
		//{
		//	T* ret = ptr;
		//	ptr = 0;
		//	return ret;
		//}
	} intern;
public:
	GenericCache( bool managed_ = false ) : managed ( managed_ )
	{}
	~GenericCache()
	{
		if ( managed )
		{
			for ( int i = 0; i < data.size(); i++ )
			{
				if ( data[i].ptr )
				{
					delete data[i].ptr;
					data[i].ptr = 0;
				}
			}
		}
		data.clear();
	}
	
	void addPtr ( T* data_ptr_, const int& id_ )
	{
		data.push_back( intern( data_ptr_, id_/*,managed*/ ) );
		if ( is_sorted )
			is_sorted = false;
	}

#ifndef __TEST_001__
	T* getPtrById ( const int& id )
	{
		if( !is_sorted )
			data.sort();
		int val = binary_search ( id, 0, data.size() - 1 );
		if ( val==-1 )
			return 0; 
		else
			return data[val].ptr;
	}
#elif
	int getPtrById ( const int& id )
	{
//		this
		if( !is_sorted )
			data.sort();
		int val = binary_search ( id, 0, data.size() - 1 );
		if ( val==-1 )
			return 0; 
		else
			return data[val].sort_id;
	}
#endif

	T* getPtrByNumber ( const int& num )
	{
		return data[num].ptr;
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
			
			if (id < data[m].sort_id )
				right = m - 1;
			else
				left = m + 1;
			
		} while((id < data[m].sort_id || data[m].sort_id < id) && left <= right );

		if (!(id < data[m].sort_id ) && !(data[m].sort_id < id))
			return m;
			
		return -1;
	}

	bool managed;

	core::array<intern> data;
	bool is_sorted;
};