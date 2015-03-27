#include <iostream>
#include "QueueLinked.h"
#include "show7.cpp"

using namespace std;

/*
 * name: QueueNode
 * 
 * inputParamter: data & next pointer
 * 
 * preCondtion: must have a list created
 * 
 * postCondtion: node will be created & added to the list 
 * with new data & next pointer
 * 
 * functionAlgorithm: nodeData is set to dataItem & nextPtr is set to next 
 * 
 * returnValue: none
*/
template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode( const DataType &nodeData, QueueNode *nextPtr )
{
	dataItem = nodeData;
	next = nextPtr;
}

/*
 * name: QueueLinked
 * 
 * inputParamter: none / ignored
 * 
 * preCondtion: none
 * 
 * postCondtion: a new list will be created
 * 
 * functionAlgorithm: front & back are set to null
 * 
 * returnValue: none
*/
template <typename DataType>
QueueLinked<DataType>::QueueLinked( int ignore )
{
	front = back = NULL;
}

/*
 * name: QueueLinked ( copy constructor )
 * 
 * inputParamter: a list
 * 
 * preCondtion: a source list must already exist in order for the 
 *              constructor to copy & create a new list
 * 
 * postCondtion: a new list will be created identical to a source list
 * 
 * functionAlgorithm: the constructor first checks to see if the source
 * list is empty.  if the source list is empty then the new list will 
 * have front & back set equal to null thus created an empty list. 
 * however if the list has information, then the data will be copied over
 * node by node.  the first source node is copied over as the new front
 * of the list.  for the front node the the data from the source node is
 * copied and the next is set equal to null in the case that there are 
 * no other nodes to be copied over.  front is assigned to destNode which
 * is used to move along the nodes in the list.  the source list is checked
 * to see the front is equal to the back signifying only one node in the
 * list.  if this is true then the back is set equal to the front. the 
 * sourceNode which was set to the front of the source is moved to the
 * next node in the list.  a while loop is implemented and will copy 
 * the data of the current source node into a tempNode.  tempNode's next
 * is set to null in the case of it being the last node.  destNode's next
 * is set to tempNode linking the two nodes together.  destNode is set
 * equal to tempNode in order to move the pointer up in the list. the
 * source list's back is checked for and if the current node is equal to 
 * the back then the destNode is equal to back.  the sourceNode is moved
 * up to the next node and this process is repeated until all the nodes
 * have been copied over to the new list.
 * 
 * returnValue: none
*/
template <typename DataType>
QueueLinked<DataType>::QueueLinked( const QueueLinked &source )
{
	QueueNode* sourceNode = source.front;
	QueueNode* destNode;
	QueueNode* tempNode;
	
	if( source.isEmpty() )
	{
		front = back = NULL;
	}
	else
	{
		front = new QueueNode( sourceNode->dataItem, NULL );
		
		destNode = front;
		
		if( source.front == source.back )
		{
			back = front;
		}
		
		sourceNode = sourceNode->next;
		
		while( sourceNode != NULL )
		{
			tempNode = new QueueNode( sourceNode->dataItem, NULL );
			
			destNode->next = tempNode;
			
			destNode = tempNode;
			
			if( sourceNode == source.back )
			{
				back = destNode;
			}
			
			sourceNode = sourceNode->next;
		}
	}
}

/*
 * name: QueueLinked overload = operater 
 * 
 * inputParamter: a list
 * 
 * preCondtion: a source list must exist for it to be assigned to an 
 * existing list
 * 
 * postCondtion: the source list will be assigned to dest list
 * functionAlgorithm: the overloaded assignment operator first checks to
 * see if the list is the same object. if it is then it outputs an error.
 * then checks to see if the source list list is empty.  if the source 
 * list is empty then dest list is cleared then front & back set equal 
 * to null thus created an empty list. however if the list has information, 
 * then the data will be copied over node by node.  the dest list is cleared
 * then first source node is copied over as the new front of the list.  
 * for the front node the the data from the source node is copied and the 
 * next is set equal to null in the case that there are no other nodes to 
 * be copied over.  front is assigned to destNode which is used to move 
 * along the nodes in the list.  the source list is checked to see the 
 * front is equal to the back signifying only one node in the
 * list.  if this is true then the back is set equal to the front. the 
 * sourceNode which was set to the front of the source is moved to the
 * next node in the list.  a while loop is implemented and will copy 
 * the data of the current source node into a tempNode.  tempNode's next
 * is set to null in the case of it being the last node.  destNode's next
 * is set to tempNode linking the two nodes together.  destNode is set
 * equal to tempNode in order to move the pointer up in the list. the
 * source list's back is checked for and if the current node is equal to 
 * the back then the destNode is equal to back.  the sourceNode is moved
 * up to the next node and this process is repeated until all the nodes
 * have been copied over to the new list.
 * 
 * returnValue: QueueLinked<DataType> the dest list is returned
*/
template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator = ( const QueueLinked &source )
{
	QueueNode* sourceNode = source.front;
	QueueNode* destNode;
	QueueNode* tempNode;
	
	if( this == &source )
	{
		cout << "ERROR!" << endl;
	}
	else if( source.isEmpty() )
	{
		clear();
		front = back = NULL;
	}
	else
	{
		clear();
		
		front = new QueueNode( sourceNode->dataItem, NULL );
		
		destNode = front;
		
		if( source.front == source.back )
		{
			back = front;
		}
		
		sourceNode = sourceNode->next;
		
		while( sourceNode != NULL )
		{
			tempNode = new QueueNode( sourceNode->dataItem, NULL );
			
			destNode->next = tempNode;
			
			destNode = tempNode;
			
			if( sourceNode == source.back )
			{
				back = destNode;
			}
			
			sourceNode = sourceNode->next;
		}
	}

	return *this;
}

/*
 * name: ~QueueLinked
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must exist for the destructor to be called
 * 
 * postCondtion: list will be deallocated
 * 
 * functionAlgorithm: the function used two node pointers to deallocate
 * the list.  the currentNode is set to the front and the deleteNode is
 * set to the node that will be deallocated.  the function checks to see
 * if the list actually has data in it.  if it's not empty then it will 
 * go ahead and start deallocating the nodes.  the deleteNode gets set 
 * with the currentNode.  the currentNode gets moved to the next node in
 * the list. the deleteNode is deallocated and then a while loop is started
 * and repeats this process until all the nodes have been deallocated
 * 
 * returnValue: none
*/
template <typename DataType>
QueueLinked<DataType>::~QueueLinked()
{
	QueueNode* currentNode = front;
	QueueNode* deleteNode;
	
	if( !isEmpty() )
	{
		deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;		
		
		while( currentNode != NULL )
		{
			deleteNode = currentNode;
			currentNode = currentNode->next;
			delete deleteNode;
		}
	}
	
	front = back = NULL;
}

/*
 * name: enqueue
 * 
 * inputParamter: a DataType item
 * 
 * preCondtion: a list must be declared to enqueue
 * 
 * postCondtion: a new node will be created with data item 
 * 
 * functionAlgorithm: the function first checks to see if the list is 
 * empty.  if it is empty then the a new front is created and the node
 * is create with the item and it's next set to null.  the back is also
 * set to the front.  if the list is not full then a tempNode is used to
 * create a new node with the data item and it's next set to null.  the
 * back node's next is set equal to tempNode thus linking the new node.
 * the back is moved up to tempNode creating the new back of the list.
 * 
 * returnValue: none
*/
template <typename DataType>
void QueueLinked<DataType>::enqueue( const DataType &item ) throw (logic_error)
{
	QueueNode* tempNode;
	
	if( isEmpty() )
	{
		front = new QueueNode( item, NULL );
		back = front;
	}
	else if( !isFull() )
	{
		tempNode = new QueueNode( item, NULL );
		
		back->next = tempNode;
		
		back = tempNode;
	}	
}

/*
 * name: dequeue
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must have data to be able to dequeue
 * 
 * postCondtion: a node will be dequeued and data will be returned
 * 
 * functionAlgorithm: the fucntion checks to see if the list is empty.
 * if the list is not empty then the item at the front is extracted. the
 * front is moved to the front's next creating a new front. there is a 
 * dequeueNode pointer which was previously set to the original front 
 * and after the info has been extracted the dequeueNode is deallocated
 * 
 * returnValue: DataType item
*/
template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
	QueueNode* dequeueNode = front;
	DataType item;
	
	if( isEmpty() )
	{
		throw logic_error( "dequeue() while queue empty"  );
	}
	else
	{
		item = front->dataItem;
		front = front->next;
		delete dequeueNode;
		return item;
	}
}

/*
 * name: clear
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must exist to clear it
 * 
 * postCondtion: the list is cleared of it's nodes
 * 
 * functionAlgorithm: the function used two node pointers to deallocate
 * the list.  the currentNode is set to the front and the deleteNode is
 * set to the node that will be deallocated.  the function checks to see
 * if the list actually has data in it.  if it's not empty then it will 
 * go ahead and start deallocating the nodes.  the deleteNode gets set 
 * with the currentNode.  the currentNode gets moved to the next node in
 * the list. the deleteNode is deallocated and then a while loop is started
 * and repeats this process until all the nodes have been deallocated.
 * front and back are set to null.
 * 
 * returnValue: none
*/
template <typename DataType>
void QueueLinked<DataType>::clear()
{
	QueueNode* currentNode = front;
	QueueNode* deleteNode;
	
	if( !isEmpty() )
	{
		deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;		
		
		while( currentNode != NULL )
		{
			deleteNode = currentNode;
			currentNode = currentNode->next;
			delete deleteNode;
		}
	}
	
	front = back = NULL;
}

/*
 * name: isEmpty
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must be created to check if it's empty
 * 
 * postCondtion: checks if empty
 * 
 * functionAlgorithm: the function returns if the front is equal to null
 * 
 * returnValue: a bool with the result
*/
template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const
{
	return( front == NULL );
}

/*
 * name: isFull
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must exist to check if full
 * 
 * postCondtion: checks if list is full
 * 
 * functionAlgorithm: the fucntion always returns false
 * 
 * returnValue: a bool return true
*/
template <typename DataType>
bool QueueLinked<DataType>::isFull() const
{
	if( true )
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
 * name: putFront
 * 
 * inputParamter: a DataType item
 * 
 * preCondtion: a list must exist to put to the front 
 * 
 * postCondtion: a new node is put at the front of the list 
 * 
 * functionAlgorithm: the function checks to see if the list is empty.
 * if the list is empty then a new front node is created with the item 
 * and the next set to null.  the back is also set to the front.  the 
 * function then checks to see if the list is not full. if its not full
 * then a tempNode is created with the item and it's next is pointing to
 * the front of the list thus linking the list.  the front is then set
 * to the tempNode making it the new front of the list.
 * 
 * returnValue: none
*/
template <typename DataType>
void QueueLinked<DataType>::putFront( const DataType &item ) throw (logic_error)
{
	QueueNode* tempNode;
	
	if( isEmpty() )
	{
		front = new QueueNode( item, NULL );
		back = front;
	}
	else if( !isFull() )
	{
		tempNode = new QueueNode( item, front );
		front = tempNode;
	}	
}

/*
 * name: getRear
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must exist to get the rear
 * 
 * postCondtion: the rear is removed 
 * 
 * functionAlgorithm: the function checks to see if the list is not empty.
 * then it checks to see if the front is equal to the back. if it is then
 * the item is extracted from the back and the back is deallocated. the
 * front and back are set to null thus emptying the list.  the item is 
 * returned. if the front and back are not equal then the item from the 
 * back is extracted.  a tempNode is set equal to the front and works it's
 * way down the list until the tempNode's next is equal to the back.
 * once the tempNode has reached to node before the back it sets it's next
 * equal to null thus creating the new back.  the orignal back is deallocated
 * and the back is set equal to tempNode.  the item is returned.
 * 
 * returnValue: DataType item
*/
template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
	QueueNode* tempNode;
	DataType item;
	
	if( isEmpty() )
	{
		throw logic_error( "getRear() while queue empty" );
	}
	else
	{
		if( front == back )
		{
			item = back->dataItem;
			delete back;
			
			front = back = NULL;
			return item;
		}
		else
		{
			item = back->dataItem;
			tempNode = front;
			
			while( tempNode->next != back )
			{
				tempNode = tempNode->next;
			}
			
			tempNode->next = NULL;
			delete back;
			back = tempNode;
			
			return item;
		}
	}		
}

/*
 * name: getLength
 * 
 * inputParamter: none
 * 
 * preCondtion: a list must exist to get it's length
 * 
 * postCondtion: none
 * 
 * functionAlgorithm: the function has a tempNode set to front and a count
 * which is set equal to zero.  if the list is empty then the count is 
 * returned with the value zero. else if the list has nodes then the 
 * count is incremented. the tempNode is moved to the next node and the
 * count is incremented until the end of the list is reached. the function
 * then returns the count of nodes.
 * 
 * returnValue: int count
*/
template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
	QueueNode* tempNode = front;
	int count = 0;
	
	if( isEmpty() )
	{
		return count;
	}
	else
	{
		count++;	
		tempNode = tempNode->next;
		
		while( tempNode != NULL )
		{
			count++;
			tempNode = tempNode->next;
		}
		
		return count;
	}
}
