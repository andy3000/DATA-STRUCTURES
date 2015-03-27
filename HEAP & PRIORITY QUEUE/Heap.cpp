/** 
 * @file Heap.cpp
 * @author Amardeep Singh
 * @brief This program creates a heap.
 * @date April 8th 2014
*/
#include "Heap.h"

/**
 * Constructor.
 * 
 * The constructor allocates memory for the heap.  It only does
 * this if the size is greater than zero.
 * 
 * @pre A heap does not exist
 * @post The heap is created with the size of the heapSize.
 * 
 * @param Int heapSize.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::Heap( int heapSize )
{
	if( heapSize > 0 )
	{
		maxSize = heapSize;
	}
	else
	{
		maxSize = DEFAULT_MAX_HEAP_SIZE;
	}
	
	size = 0;
	dataItems = new DataType[ maxSize ];
}

/**
 * Copy Constructor.
 * 
 * The copy constructor creates a new heap with the values from
 * the source heap.  
 * 
 * @pre A heap does not exist
 * @post A heap is created with the values from the source hash table.
 * 
 * @param Heap source passed by const reference.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::Heap( const Heap &source )
{
	maxSize = source.maxSize;
	size = source.size;
	dataItems = new DataType[ maxSize ];
	
	if( !source.isEmpty() ) 
	{
		for( int i = 0; i < size; i++ )
		{
			dataItems[ i ] = source.dataItems[ i ];
		}
	}
}

/**
 * Overloaded assignment operator.
 * 
 * The assignment operator assigns one heap to the existing heap.
 * It first checks to see if the current object is the same as the source.
 * If it is then it returns the dereferenced this object.  Otherwise it
 * clears the heap and creates a new heap with the values from the source
 * heap.
 * 
 * @pre A heap exists
 * @post A heap is assigned to the source heap.
 * 
 * @param Heap source passed by const reference
 * @return Dereferenced this
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >& Heap< DataType, KeyType, Comparator >::operator=( const Heap &source )
{
	if( this == &source )
	{
		return *this;
	}
	else
	{
		clear();
		
		maxSize = source.maxSize;
		size = source.size;
		dataItems = new DataType[ maxSize ];
		
		if( !source.isEmpty() ) 
		{
			for( int i = 0; i < size; i++ )
			{
				dataItems[ i ] = source.dataItems[ i ];
			}
		}
	}
	
	return *this;
}

/**
 * Destructor.
 * 
 * The destructor deallocates memory used for heap.
 * 
 * @pre A heap exists.
 * @post A heap is deallocated.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
Heap< DataType, KeyType, Comparator >::~Heap()
{
	delete[]dataItems;
	dataItems = NULL;
}

/**
 * Insert.
 * 
 * The insert function inserts a new data item into the heap.  The
 * heapUP function is called in order to maintain the structure of the heap.
 * The size of the heap is incremented.
 * 
 * @pre A heap does not contain a new item
 * @post A heap contains a new item
 * @param DataType newDataItem passed by const reference.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::insert( const DataType& item ) throw ( logic_error )
{
	if( isFull() )
	{
		throw logic_error( "HEAP IS FULL!" );
	}
	
	dataItems[ size ] = item;
	heapUP( size );
	size++;
}

/**
 * Remove.
 * 
 * The remove function removes an element from the heap.  It then calls
 * the heapify function in order to maintain the structure of the heap.
 * The size of the heap is decremented.
 * 
 * @pre A heap has an element in it
 * @post The element is removed from the heap.
 * 
 * @return DataType
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
DataType Heap< DataType, KeyType, Comparator >::remove() throw ( logic_error )
{
	if( isEmpty() )
	{
		throw logic_error( "HEAP IS EMPTY!" );
	}
	
	DataType returnItem = dataItems[ 0 ];
	dataItems[ 0 ] = dataItems[ --size ];
	
	heapify( 0 );
	
	return returnItem;
}

/**
 * heapUP
 * 
 * This function moves an element to the top of the heap depending on its
 * priority.  It does this recursivley until the newly inserted item is
 * moved to the top.
 * 
 * @pre A newly inserted element is on the bottom of the heap.
 * @post The newly inserted element is moved to the top of the heap.
 * 
 * @param Int me
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::heapUP( int me )
{
	int parent = getParent( me );
	
	if( me != 0 )
	{
		if( Comparator()( dataItems[ me ].getPriority(), 
			dataItems[ parent ].getPriority() ) )
		{
			swap( dataItems[ parent ], dataItems[ me ] );
			heapUP( parent );
		}
	}
}

/**
 * heapify
 * 
 * This function moves around elements in order to maintain the structure
 * of the heap.  It performs this recursivley.
 * 
 * @pre After an element is removed it is out of order.
 * @post The heap is orgranized ot maintain it's strucutre.
 * 
 * @param Int N
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::heapify( int N )
{
	int leftChild = getLeftChild( N );
	int rightChild = getRightChild( N );
	
	if( leftChild >= size )
	{
		return;
	}
	else
	{
		if( rightChild >= size )
		{
			if( Comparator()( dataItems[ leftChild ].getPriority(), 
				dataItems[ N ].getPriority() ) )
			{
				swap( dataItems[ N ], dataItems[ leftChild ] );
			}
		}
		else
		{
			int compareChild = leftChild;
			
			if( Comparator()( dataItems[ rightChild ].getPriority(), 
				dataItems[ compareChild ].getPriority() ) )
			{
				compareChild = rightChild;
			}
			
			if( Comparator()( dataItems[ compareChild ].getPriority(), 
				dataItems[ N ].getPriority() ) )
			{
				swap( dataItems[ N ], dataItems[ compareChild ] );
				heapify( compareChild );
			}
		}
	}
}

/**
 * Clear.
 * 
 * This funciton clears the heap.
 * 
 * @pre A heap contains values.
 * @post The heap is cleared.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::clear()
{
	if( !isEmpty() )
	{
		delete[]dataItems;
		dataItems = new DataType[ maxSize ];
		size = 0;
	}
}

/**
 * isEmpty
 * 
 * This funciton checks the heap to see if it is empty.
 * 
 * @pre A heap exists
 * @post A heap is checked to see if it contains any values.
 * 
 * @return bool.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
bool Heap< DataType, KeyType, Comparator >::isEmpty() const
{
	return( size == 0 );
}

/**
 * isFull
 * 
 * This funciton checks the heap to see if it is full.
 * 
 * @pre A heap exists
 * @post A heap is checked to see if it is full
 * 
 * @return bool.
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
bool Heap< DataType, KeyType, Comparator >::isFull() const
{
	return( size == maxSize );
}

/**
 * getParent
 * 
 * This funciton gets the parent of the index given.
 * 
 * @pre The parent of the index is unknown
 * @post The parent of the index is known
 * 
 * @param int N
 * @return int
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getParent( int N )
{
	return( ( N - 1 ) / 2 );
}

/**
 * getLeftChild
 * 
 * This funciton gets the leftChild of the index given.
 * 
 * @pre The leftChild of the index is unknown
 * @post The leftChild of the index is known
 * 
 * @param int N
 * @return int
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getLeftChild( int N )
{
	return( ( 2 * N ) + 1 );
}

/**
 * getRightChild
 * 
 * This funciton gets the rightChild of the index given.
 * 
 * @pre The rightChild of the index is unknown
 * @post The rightChild of the index is known
 * 
 * @param int N
 * @return int
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
int Heap< DataType, KeyType, Comparator >::getRightChild( int N )
{
	return( ( 2 * N ) + 2 );
}

/**
 * WriteLevels
 * 
 * This function writes the levels of the heap in order from highest 
 * to lowest.
 * 
 * @pre a heap exists.
 * @post a heap is printed in order
 * 
 */
template< typename DataType, typename KeyType, typename Comparator >
void Heap< DataType, KeyType, Comparator >::writeLevels () const
{
	int level = 0;
	
	if( !isEmpty() )
	{	
		for( int i = 0; i < size; i++ )
		{
			cout << dataItems[ i ].getPriority() << " ";
			
			if( i == level )
			{
				cout << endl;
				level = ( i + 1 ) * 2;
			}
		}
	}
}
