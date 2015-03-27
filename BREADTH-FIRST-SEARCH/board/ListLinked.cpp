#include "ListLinked.h"

template <typename DataType>
List<DataType>::ListNode::ListNode( const DataType &item, ListNode* nextPointer )
{
	dataItem = item;
	next = nextPointer;
}

template <typename DataType>
List<DataType>::List( int ignore )
{
	head = cursor = NULL;
}

template <typename DataType>
List<DataType>::List( const List<DataType> &source )
{
	// initialize variables
	ListNode* sourceNode = source.head;
	ListNode* destNode;
	ListNode* tempNode;
	
	// if list is empty then create an empty list
	if( sourceNode.empty() )
	{
		head = cursor = NULL;
	}
	// else copy data over from source list
	else
	{
		// create new head node & copy over data from source list
		head = new ListNode( sourceNode->dataItem, NULL );
		
		// make destNode point to head
		destNode = head;
		
		// check to see if cursor is equal to head on source list
		if( source.cursor = source.head )
		{
			// if true then assign cursor to head
			cursor = head;
		}
		
		// move to next node in source list
		sourceNode = sourceNode->next;
		
		// copy over nodes until end of list is reached
		while( sourceNode != NULL )
		{
			// create new node with source data
			tempNode = new ListNode( sourceNode->dataItem, NULL );
			
			// link previous node to new node
			destNode->next = tempNode;
			
			// move destNode to newest node in new list
			destNode = tempNode;
			
			// check to see if cursor is equal to head on source list
			if( sourceNode = source.cursor )
			{
				cursor = destNode;
			}
			
			// move to next node in source list
			sourceNode = sourceNode->next;
		}
	}
}

template <typename DataType>
List<DataType>& List<DataType>::operator=( const List<DataType> &source )
{
	// initialize variables
	ListNode* sourceNode = source.head;
	ListNode* destNode = head;
	ListNode* tempNode;
	
	// check to see if source list is the same
	if( this == &source )
	{
		return;
	}
	// if source list is empty then clear list
	else if( sourceNode.empty() )
	{
		clear();
	}
	// else copy over source list
	else
	{
		// clear list
		clear();
		
		// create new head node & copy over data from source list
		head = new ListNode( sourceNode->dataItem, NULL );
		
		// make destNode point to head
		destNode = head;
		
		// check to see if cursor is equal to head on source list
		if( source.cursor == source.head )
		{
			cursor = head;
		}
		
		// move to next node in source list
		sourceNode = sourceNode->next;
		
		while( sourceNode != NULL )
		{
			// create new node with source data
			tempNode = new ListNode( sourceNode->dataItem, NULL );
			
			// link previous node to new node
			destNode->next = tempNode;
			
			// move destNode to newest node in new list
			destNode = tempNode;
			
			// check to see if cursor is equal to head on source list
			if( sourceNode == source.cursor )
			{
				cursor = destNode;
			}
			
			// move to next node in source list
			sourceNode = sourceNode->next;
		}
	}
	
	// return new list
	return *this;
}

template <typename DataType>
List<DataType>::~List()
{
	// initialize variables
	ListNode* currentNode = head;
	ListNode* deleteNode;
	
	// if list is not empty then deallocate memory
	if( !isEmpty() )
	{
		// node to be deleted
		deleteNode = currentNode;
		
		// move to next node to be deleted
		currentNode = currentNode->next;
		
		// delete node
		delete deleteNode;
		
		// loop til all nodes are deleted
		while( currentNode != NULL )
		{
			// node to be deleted
			deleteNode = currentNode;
			
			// move to next node to be deleted
			currentNode = currentNode->next;
			
			// delete node
			delete deleteNode;
		}
	}
	
	// set pointers to null
	head = cursor = NULL;
}

template <typename DataType>
void List<DataType>::insertAfter( const DataType &item )
{
	// initialize variables
	ListNode* tempNode;
	
	// if list is empty then create new head node
	if( isEmpty() )
	{
		head = new ListNode( item, NULL );
		cursor = head;
	}
	// else create a new node & link into list
	else
	{
		tempNode = new ListNode( item, cursor->next );
		cursor->next = tempNode;
		cursor = tempNode;
	}
}

template <typename DataType>
void List<DataType>::remove()
{
	// initialize variables
	ListNode* tempNode;
	
	// if list is empty return error
	if( isEmpty() )
	{
		cout << "ERROR!" << endl;
		return;
	}
	// else if cursor is at head
	else if( cursor == head )
	{
		// move head to new head location
		head = head->next;
		
		// remove cursor
		delete cursor;
		
		// move cursor to new head
		cursor = head;
	}
	// else if cursor is at last node
	else if( cursor->next == NULL )
	{
		// tempNode holds location of cursor
		tempNode = cursor;
		
		// go to prior node
		gotoPrior();
		
		// make that node the new last node in list
		cursor->next = NULL;
		
		// move cursor to the head
		cursor = head;
		
		// remove node
		delete tempNode;
	}
	// else remove the node
	else
	{
		// tempNode holds location of cursor
		tempNode = cursor;
		
		// go to prior node
		gotoPrior();
		
		// link cursor to node after the node to be removed
		cursor->next = tempNode->next;
		
		// move cursor next node in line after removal
		cursor = cursor->next;
		
		// remove the node
		delete tempNode;
	}
}

template <typename DataType>
void List<DataType>::replace( const DataType &item )
{
	// if list is empty then create a new head
	if( isEmpty() )
	{
		head = new ListNode( item, NULL );
		cursor = head;
	}
	// else replace new item with current item
	else
	{
		cursor->dataItem = item;
	}
}

template <typename DataType>
void List<DataType>::clear()
{
	// initialize variables
	ListNode* currentNode = head;
	ListNode* deleteNode;
	
	// if list is not empty then deallocate memory
	if( !isEmpty() )
	{
		// node to be deleted
		deleteNode = currentNode;
		
		// move to next node to be deleted
		currentNode = currentNode->next;
		
		// delete node
		delete deleteNode;
		
		// loop til all nodes are deleted
		while( currentNode != NULL )
		{
			// node to be deleted
			deleteNode = currentNode;
			
			// move to next node to be deleted
			currentNode = currentNode->next;
			
			// delete node
			delete deleteNode;
		}
	}
	
	// set pointers to null
	head = cursor = NULL;
}

template <typename DataType>
bool List<DataType>::isEmpty() const
{
	// check to see if list is empty 
	return ( head == NULL );
}

template <typename DataType>
bool List<DataType>::isFull() const
{
	// can't check for full so return false
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning()
{
	// if list empty return error
	if( isEmpty() )
	{
		cout << "ERROR!" << endl;
		return;
	}
	// else move cursor to beginning
	else
	{
		cursor = head;
	}
}

template <typename DataType>
void List<DataType>::gotoEnd()
{
	// if empty then return error
	if( isEmpty() )
	{
		cout << "ERROR!" << endl;
		return;
	}
	// else move cursor to last node in list
	else
	{	
		while( cursor->next != NULL )
		{
			cursor = cursor->next;
		}
	}
}

template <typename DataType>
bool List<DataType>::gotoNext()
{
	// if list empty return error
	if( isEmpty() )
	{
		return false;
	}
	// else if cursor at last element in list then return error
	else if( cursor->next == NULL )
	{
		return false;
	}
	// else move cursor to next element
	else
	{
		cursor = cursor->next;
		return true;
	}
}

template <typename DataType>
bool List<DataType>::gotoPrior()
{
	// initialize variables
	ListNode* tempNode = head;
	
	// if empty then return error
	if( isEmpty() )
	{
		return false;
	}
	// if cursor at beginning of list then return error
	else if( cursor == head )
	{
		return false;
	}
	// else if go to prior node
	else
	{
		// while tempNodes next is not equal to cursor
		while( tempNode->next != cursor )
		{
			// move tempNode to next node in list
			tempNode = tempNode->next;
		}
		
		// once prior node is found move cursor 
		cursor = tempNode;
		return true;
	}
}

template <typename DataType>
bool List<DataType>::getCursor( DataType &item ) const 
{
	// if empty then return error
	if( isEmpty() )
	{
		cout << "ERROR!" << endl;
		return false;
	}
	// get cursor and return item
	else
	{
		item = cursor->dataItem;
		return true;
	}
}

template <typename DataType>
void List<DataType>::insertBefore( const DataType &item )
{
	// initialize variables
	ListNode* tempNode;
	
	// if empty then return error
	if( isEmpty() )
	{
		head = new ListNode( item, NULL );
		cursor = head;
	}
	// else if cursor is at the head
	else if( cursor == head )
	{
		// create tempNode with it's next pointing to head
		tempNode = new ListNode( item, head );
		
		// set cursor and head equal to temp node to create the new head
		head = cursor = tempNode;
	}
	// else insert before
	else
	{
		// create tempNode with it's next pointing to cursor
		tempNode = new ListNode( item, cursor );
		
		// move cursor to prior node
		gotoPrior();
		
		// link cursor's next to tempNode 
		cursor->next = tempNode;
		
		// move cursor to newly inserted node
		cursor = tempNode;
	}
}
