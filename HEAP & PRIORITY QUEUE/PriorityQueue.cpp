/** 
 * @file PriorityQueue.cpp
 * @author Amardeep Singh
 * @brief This program creates a prorityQueue
 * @date April 8th 2014
*/
#include "PriorityQueue.h"

/**
 * Constructor.
 * 
 * The constructor allocates memory for the heap.  It only does
 * this if the size is greater than zero. It calls the constructor of the
 * heap.
 * 
 * @pre A priorityQueue does not exist
 * @post The priorityQueue is created with the size of the priorityQueueSize.
 * 
 * @param Int priorityQueueSize.
 * 
 */
template < typename DataType, typename KeyType, typename Comparator >
PriorityQueue< DataType, KeyType, Comparator >::PriorityQueue( int priorityQueueSize )
{
}

/**
 * Enqueue.
 * 
 * The Enqueue function inserts a new data item into the priorityQueue.  
 * It does this by calling the insert function of the heap.
 * 
 * @pre A priorityQueue does not contain a new item
 * @post A priorityQueue contains a new item
 * @param DataType newDataItem passed by const reference.
 * 
 */
template < typename DataType, typename KeyType, typename Comparator >
void PriorityQueue< DataType, KeyType, Comparator >::enqueue( const DataType &newDataItem )
{
	Heap<DataType>::insert( newDataItem );
}

/**
 * Dequeue.
 * 
 * The Dequeue function removes an element from the priorityQueue.  It 
 * does this by calling the heap remove function.
 * 
 * @pre A priorityQueue has an element in it
 * @post The element is removed from the priorityQueue.
 * 
 * @return DataType
 * 
 */
template < typename DataType, typename KeyType, typename Comparator >
DataType PriorityQueue< DataType, KeyType, Comparator >::dequeue()
{
	return Heap<DataType>::remove();
}
