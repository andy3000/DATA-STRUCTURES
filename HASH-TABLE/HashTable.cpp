/** 
 * @file HashTable.cpp
 * @author Amardeep Singh
 * @brief This program creates a hash table.
 * @date April 1st 2014
*/
#include "HashTable.h"

/**
 * Constructor.
 * 
 * The constructor allocates memory to an array of BSTs.  It only does
 * this if the size is greater than zero.
 * 
 * @pre A hash table does not exist
 * @post The hash table is created with the size of the tableSize.
 * 
 * @param Int size.
 * 
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable( int size )
{
	if( size > 0 )
	{
		tableSize = size;
		
		dataTable = new BSTree<DataType, KeyType>[ tableSize ];
	}
}

/**
 * Copy Constructor.
 * 
 * The copy constructor creates a new hash table with the values from
 * the source hash table.  
 * 
 * @pre A hash table does not exist
 * @post A hash table is created with the values from the source hash table.
 * 
 * @param HashTable source passed by const reference.
 * 
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable( const HashTable& source )
{
	tableSize = source.tableSize;
	dataTable = new BSTree<DataType, KeyType>[ tableSize ];
	
	if( !source.isEmpty() )
	{
		for( int i = 0; i < tableSize; i++ )
		{
			dataTable[ i ] = source[ i ];
		}
	}
}

/**
 * Overloaded assignment operator.
 * 
 * The assignment operator assigns one hash table to the existing hash table.
 * It first checks to see if the current object is the same as the source.
 * If it is then it returns the dereferenced this object.  Otherwise it
 * clears the table and creates a new table with the values from the source
 * table.
 * 
 * @pre A hash table exists
 * @post A hash table is assigned to the source hash table.
 * 
 * @param HashTable source passed by const reference
 * @return Dereferenced this
 * 
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=( const HashTable& source )
{
	if( this == &source )
	{
		return *this;
	}
	else
	{
		clear();
		delete[]dataTable;
		
		tableSize = source.tableSize;
		dataTable = new BSTree<DataType, KeyType>[ tableSize ];
		
		if( !source.isEmpty() )
		{
			for( int i = 0; i < tableSize; i++ )
			{
				dataTable[ i ] = source[ i ];
			}
		}
	}
	
	return *this;
}

/**
 * Destructor.
 * 
 * The destructor deallocates memory used for the hash table.
 * 
 * @pre A hash table exists.
 * @post A hash table is deallocated.
 * 
 */
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	delete[]dataTable;
	dataTable = NULL;
}

/**
 * Insert.
 * 
 * The insert function inserts a new data item into the hash table.  The
 * hash function of the new data item is used to find the index and then
 * the item is inserted into the BST in the hash table.
 * 
 * @pre A hash table does not contain a new item
 * @post A hash table contains a new item
 * @param DataType newDataItem passed by const reference.
 * 
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert( const DataType& newDataItem )
{
	dataTable[ newDataItem.hash( newDataItem.getKey() ) % tableSize ].insert( newDataItem );
}

/**
 * Remove.
 * 
 * The remove function removes an element from the hash table if it exisits
 * within the hash table.  The hash funciton of a temp item is used in order
 * to find the correct index and then the remove funciton is used by the
 * BST with the delete key.  If the item has been deleted from the BST 
 * in the hash table then a true is returned.  False otherwise.
 * 
 * @pre A hash table may or may not contain an element
 * @post If the element is contained within the hash table then it is removed
 * 
 * @param KeyType deleteKey passed by const reference.
 * 
 * @return bool 
 * 
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove( const KeyType& deleteKey )
{
	DataType temp;
	
	return ( dataTable[ temp.hash( deleteKey ) % tableSize ].remove( deleteKey ) );
}

/**
 * Retrieve
 * 
 * This funciton retrieves an element from the hash table if it is contained
 * within the hash table.  It uses the return items hash funciton to find
 * the index and then uses the retrieve function of the BST in the hash table.
 * It returns if the object and if it was retrieved or not as a bool.
 * 
 * @pre An element may or may not be within the hash table.
 * @post If the element is in the tree then it is retrieved.
 * 
 * @param KeyType searchKey passed by const reference, DataType returnItem passed by reference
 * 
 * @return bool
 * 
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve( const KeyType& searchKey, DataType& returnItem ) const
{
	return ( dataTable[ returnItem.hash( searchKey ) % tableSize ].retrieve( searchKey, returnItem ) );
}

/**
 * Clear.
 * 
 * This funciton clears the current hash table.
 * 
 * @pre A hash table contains values.
 * @post The hash table is cleared.
 * 
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for( int i = 0; i < tableSize; i++ )
	{
		dataTable[ i ].clear();
	}
}

/**
 * isEmpty
 * 
 * This funciton checks the hash table to see if it is empty.  It checks
 * every BST in the hash table to see if they are all empty.
 * 
 * @pre A hash table exists
 * @post A hash table is checked to see if it contains any values.
 * 
 * @return bool.
 * 
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	if( dataTable != NULL )
	{
		for( int i = 0; i < tableSize; i++ )
		{
			if( !dataTable[ i ].isEmpty() )
			{
				return false;
			}
		}
	}
	
	return true;
}
