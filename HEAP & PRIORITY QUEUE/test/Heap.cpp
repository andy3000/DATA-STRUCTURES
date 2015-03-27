#include "Heap.h"

using namespace std;

template < typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::Heap( int maxHeapSize )
{
	if( s
	maxSize = maxHeapSize;
	size = 0;
	dataItems = new DataType[ maxSize ];
}

template < typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::Heap( const Heap& other )
{
	*this = other;
}

template < typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >& Heap< DataType, KeyType, Comparator >::operator=( const Heap& src )
{
	if( this == &src )
		return *this;
	if( maxSize != src.maxSize )
	{
		delete []dataItems;
		maxSize = src.maxSize;
		dataItems = new DataType[ maxSize ];
	}
	
	size = src.size;
	
	for( int i = 0; i < size; i++ )
		dataItems[ i ] = src.dataItems[ i ];		
}

template < typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::~Heap()
{
	delete []dataItems;
	size = 0;
	maxSize = 0;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::insert( const DataType &newDataItem )    // Insert a data item
        throw ( logic_error )
{
	if( isFull() )
		throw logic_error( "HEAP IS FULL!" );
	dataItems[ size ] = newDataItem;
	heapUp( size );
	size++;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::heapUp( int location )
{
	int parent = getParent( location );
	if( location != 0 )
	{
		if( Comparator()(dataItems[ location ].getPriority(),
							dataItems[ parent ].getPriority() ) )
		{
			swap( dataItems[ parent ], dataItems[ location ] );
			heapUp( parent );
		}
	}
}

template < typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getParent( int index )
{
	return ( ( index - 1 ) / 2 );
}

template < typename DataType, typename KeyType, typename Comparator >
DataType Heap< DataType, KeyType, Comparator >::remove() throw ( logic_error )
{
	if( isEmpty() )
		throw logic_error( "HEAP IS EMPTY" );
		
	DataType val = dataItems[ 0 ];
	dataItems[ 0 ] = dataItems[ size - 1 ];
	size--;
	reHeap( 0 );
	return val;
}

template < typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::reHeap( int index )
{
	int lChild, rChild;
	lChild = getLeft( index );
	rChild = getRight( index );
	
	if( lChild >= size )
		return;
	else
	{
		if( rChild >= size )
		{
			if( Comparator()(dataItems[ lChild ].getPriority(),
							dataItems[ index ].getPriority() ) )
			{
				swap( dataItems[ index ], dataItems[ lChild ] );
			}
		}
		else
		{
			int maxChild = lChild;
			
			if( Comparator()(dataItems[ rChild ].getPriority(),
							dataItems[ maxChild ].getPriority() ) )
			{
				maxChild = rChild;
			}
			if( Comparator()(dataItems[ maxChild ].getPriority(),
							dataItems[ index ].getPriority() ) )
			{
				swap( dataItems[ index ], dataItems[ maxChild ] );
				reHeap( maxChild );
			}
		}
	}
}

template < typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getLeft( int index )
{
	return ( ( 2 * index ) + 1 );
}

template < typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getRight( int index )
{
	return ( ( 2 * index ) + 2 );
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::clear()
{
	size = 0;
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap< DataType, KeyType, Comparator >::isEmpty() const
{
	return (size == 0 );
}

template < typename DataType, typename KeyType, typename Comparator >
bool Heap< DataType, KeyType, Comparator >::isFull() const
{
	return ( size == maxSize );
}
















