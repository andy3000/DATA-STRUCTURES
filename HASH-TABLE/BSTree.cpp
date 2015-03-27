/** 
 * @file BSTree.cpp
 * @author Amardeep Singh
 * @brief This program creates a binary search tree and evaluates it.
 * @date March 11th 2014
*/
#include "BSTree.h"

/**
 * Node constructor.
 * 
 * The node constructor excepts a char data and two node pointers which
 * point to the left and right nodes.  It sets them equal to dataItem,
 * left and right.
 * 
 * @pre A node is uninitialized and not created.
 * @post The created node contains the dataItem and left and right pointers
 * to other nodes with in the list.   
 * 
 */
template< typename DataType, class KeyType >
BSTree< DataType, KeyType >::BSTreeNode::BSTreeNode( 
const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

/**
 * Default constructor.
 * 
 * The default constructor initializes the root to null.
 * 
 * @post root is equal to null.
 * 
 */
template< typename DataType, class KeyType >
BSTree< DataType, KeyType >::BSTree()
{
	root = NULL;
}

/**
 * Copy constructor.
 * 
 * The copy constructor accepts a tree and creates a tree.  It checks
 * to see if the source tree is empty.  If it is empty then it sets the
 * root equal to null otherwise it copies over the source tree 
 * 
 * @pre a tree does not exist.
 * @post a tree is copied from the source tree.
 * 
 * @param BSTree source.
 * 
 */ 
template< typename DataType, class KeyType >
BSTree< DataType, KeyType >::BSTree( const BSTree<DataType, KeyType>& source )
{
	if( source.isEmpty() )
	{
		root = NULL;
	}
	else
	{
		copyHelper( root, source.root );
	}
}

/**
 * Overloaded assignment operator.
 * 
 * The assignment operator copies the source tree over.  It accepts a 
 * source tree and checks to see if 'this' is equal to source.  If it is
 * not equal to the source then it checks to see if the source tree is
 * empty.  If it is empty then the tree is cleared and root is set equal
 * to null.  Otherwise the contents of the source tree is copied over.
 * 
 * @pre The tree exists with current data.
 * @post The tree is assigned the contents of a source tree.
 * 
 * @param BSTree source
 * @return *this
 * 
 */
template< typename DataType, class KeyType >
BSTree< DataType, KeyType>& BSTree< DataType, KeyType >::operator=(
const BSTree<DataType,KeyType>& source )
{
	if( this == &source )
	{
		return *this;
	}
	else if( source.isEmpty() )
	{
		clear();
	}
	else
	{
		clear();
		copyHelper( root, source.root );
	}
	
	return *this;
}

/**
 * Destructor.
 * 
 * The destuctor deallocates memory if the tree is not empty.  It does this
 * by calling the clear function.
 * 
 * @pre The tree has nodes or is empty.
 * @post If the tree had nodes then they are deallocated.
 * 
 */
template< typename DataType, class KeyType >
BSTree< DataType, KeyType >::~BSTree()
{
	if( !isEmpty() )
	{
		clear();
	}
}
/**
 * Copy Helper.
 * 
 * This functions helps other functions in copying the contents of a
 * source tree to a dest tree.  It creates an exact replica of the source
 * tree.  This function is a recursive function and it calls itself to 
 * go through all the nodes in order to copy the tree correctly.
 * 
 * @pre a dest tree is created and is empty
 * @post a dest tree contains the data of a source tree
 * 
 * @param BSTreeNode pointer dest pass by reference
 * @param BSTreeNode pointer source
 * 
 * @note ALGORITHM: The function checks to see if the source node is 
 * empty or not.  If it is not empty then it creates a new node in the dest
 * tree with the source's data item.  The new node's left and right pointers
 * will be set equal to null.  After the new node it created the copyHelper
 * is called again with the dest node's left pointer and the source node's
 * left pointer.  The copyHelper is then called with the right pointers of
 * the source and dest nodes.  This process is recursive and helps copy
 * the tree over in pre-order.
 * 
 */ 
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::copyHelper( BSTreeNode* &dest, BSTreeNode* source )
{
	if( source != NULL )
	{
		dest = new BSTreeNode( source->dataItem, NULL, NULL );
		copyHelper( dest->left, source->left );
		copyHelper( dest->right, source->right );
	}
	else
	{
		dest = NULL;
	}
}

/**
 * Insert.
 *
 * This function inserts a new data item into the tree.  It does this by
 * calling the insertHelper.
 * 
 * @pre A tree must exist.
 * @post A new node will be inserted to the tree.
 * 
 * @param DataType newDataItem
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::insert( const DataType& newDataItem )
{
	insertHelper( root, newDataItem );
}

/**
 * Insert Helper.
 * 
 * This function helps the insert function insert a new data item into the
 * tree.  It inserts the data item into a specific position which is dependent
 * on the key of the data item.  It does this process recursively.
 * 
 * @pre A tree will not have data item in it.
 * @post The tree will contain the new data item.
 * 
 * @param BSTree node pointer source passed by reference.
 * @param DataType new item passed by reference.
 * 
 * @note ALGORITHM: This function checks to see if the source pointer 
 * is equal to null.  If it is equal to null then a new node is created and
 * the new data item is inserted to the tree.  If it is not equal to null
 * then the newItem's key is compared to source's dataItem's key to see 
 * if it is less than.  If it is less than then the insertHelper is called
 * again with the source's left node and the newItem.  Other wise the 
 * insert helper is called with the source's right and newItem because
 * it is greater than the source's key.  This process is done recursively.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::insertHelper( BSTreeNode* &source, const DataType &newItem )
{
	if( source == NULL )
	{
		source = new BSTreeNode( newItem, NULL, NULL );
	}
	else if( newItem.getKey() == source->dataItem.getKey() )
	{
		source->dataItem = newItem;
	}
	else
	{
		if( newItem.getKey() < source->dataItem.getKey() )
		{
			insertHelper( source->left, newItem );
		}
		else
		{
			insertHelper( source->right, newItem );
		}
	}
}

/**
 * Retrieve.
 * 
 * This function retrieves a data item from the tree. It calls retrieve
 * helper in order to do this.
 * 
 * @pre Data item that needs to be searched for is sent to function.
 * @post If the data item is found then it is returned by reference.
 * 
 * @param KeyType searchKey passed by reference.
 * @param DataType searchDataItem passed by reference.
 * 
 * @return Returns a bool regarding if data item was found or not.
 * 
 */
template< typename DataType, class KeyType >
bool BSTree< DataType, KeyType >::retrieve( 
const KeyType& searchKey, DataType& searchDataItem ) const
{
	return retrieveHelper( root, searchKey, searchDataItem );
}

/**
 * Retrieve Helper.
 * 
 * This function helps the retrieve function search for and retrieve a
 * data item.  If the data item is found then it returns it by reference
 * and returns a bool regarding if the data item was found or not.
 * 
 * @pre A data item is not retreieved.
 * @post If a data item is found it returns by reference and returns a
 * bool if the data itemw as found or not.  It does this recursively.
 * 
 * @param BSTreeNode pointer source.
 * @param KeyType searchKey passed by reference.
 * @param DataType searchDataItem passed by reference.
 * 
 * @return Bool if data item was found or not.
 * @return DataType searchDataItem if item was found.
 * 
 * @note ALGORITHM: This function checks to see if the source node is 
 * empty or not.  If it is then it returns fasle.  Other wise it checks
 * to see if the source's dataItem's key is equal to the search key.
 * if it is then the source's dataItem is set equal to searchDataItem 
 * and the function returns true while searchDataItem is returned by 
 * reference.  If it is not equal to the search key then the function 
 * checks to see if the searchKey is less that the source's dataItems's
 * key.  If it is then retrieveHelper is called with the source's left
 * pointer and the searchKey and searchDataItem.  Other wise it is greater
 * and then retrieveHelper is called with source's right pointer and the
 * searchKey and searchDataItem.  This process is recursive.
 * 
 */
template< typename DataType, class KeyType >
bool BSTree< DataType, KeyType >::retrieveHelper( BSTreeNode* source, 
const KeyType& searchKey, DataType& searchDataItem ) const
{
	if( source == NULL )
	{
		return false;
	}
	
	if( source->dataItem.getKey() == searchKey )
	{
		searchDataItem = source->dataItem;
		return true;
	}
	else
	{
		if( searchKey < source->dataItem.getKey() )
		{
			return retrieveHelper( source->left, searchKey, searchDataItem );
		}
		else
		{
			return retrieveHelper( source->right, searchKey, searchDataItem );
		}
	}
}

/**
 * Remove.
 * 
 * This function removes a node from the tree.  It does this by using the 
 * deleteKey to search through the tree to find the node.  It uses the
 * removeHelper to do this.  This process is done recursively.
 * 
 * @pre If a tree exists it will have dataItems.
 * @post If a tree exists then if the dataItem is found it will be removed.
 * 
 * @param KeyType deleteKey passed by reference.
 * 
 * @return Returns a bool if the item was or was not removed.
 * 
 */
template< typename DataType, class KeyType >
bool BSTree< DataType, KeyType >::remove( const KeyType& deleteKey )
{
	return removeHelper( root, deleteKey );
}

/**
 * Remove Helper.
 * 
 * This function helps remove to remove a node from the tree.  Using the
 * deleteKey if the item is found then it is removed from the tree.  There
 * are three different cases that apply to a node when it is being removed.
 * A node can have no children, one child or two children.  It accounts for
 * all these conditions when removed the node.  This process is done recursively.
 * 
 * @pre A tree must exists to have a dataItem removed from it.
 * @post If a tree exists and if the dataItem is found using the deleteKey
 * then it is removed from the tree.
 * 
 * @param BSTreeNode pointer source passed by reference.
 * @param KeyType deleteKey passed by reference.
 * 
 * @return Returns a bool if the item was or was not removed.
 * 
 * @note ALGORITHM:  This function checks to see if the source node is 
 * empty.  If it is empty then it returns false.  Other wise it checks to see
 * if the source's dataItem's key is equal to the delete key.  If it is 
 * equal to the key then it goes into one of three cases with the children.
 * If the source's left and right pointers are equal to null then it has
 * no children.  The source is delted, set to null and the true is returned.
 * The function then checks to see if the left or right node of the source
 * has a child.  If it does then a tempNode pointer is set equal to the
 * source. Source is moved to the appropirate left or right node and then
 * temp is deleted.  Moving source to left or right links the tree up.
 * True is returned.  If the node has two children then a tempNode is set
 * equal to the source. The tempNode is the moved to the left child once
 * and then the temp node travels down the tree to the right until it can't
 * go right any more.  This action grabs the dataItem that will replace
 * the dataItem at the source.  Once the tempNode has reached to right most
 * node it copies it's data to the source data.  The removeHelper is then
 * called with the source's left pointer and the tempNode's dataItem.
 * This allows the rightmost node to get removed from the tree while also
 * keeping the tree linked up and in order.  If the delete key is not found
 * then the removeHelper is called with the source's left if the deleteKey
 * is less than the source's dataItem's key.  Other wise removeHelper is
 * called with the source's right pointer.  This process is recursive.
 * 
 */
template< typename DataType, class KeyType >
bool BSTree< DataType, KeyType >::removeHelper( BSTreeNode* &source, const KeyType& deleteKey )
{
	if( source == NULL )
	{
		return false;
	}
	
	if( source->dataItem.getKey() == deleteKey )
	{
		// NO CHILDREN
		if( source->left == NULL && source->right == NULL )
		{
			delete source;
			source = NULL;
			return true;
		}
		
		// ONE CHILD
		else if( source->left != NULL && source->right == NULL )
		{
			BSTreeNode* tempNode = source;
			source = source->left;
			delete tempNode;
			tempNode = NULL;
			return true;
		}
		else if( source->right != NULL && source->left == NULL )
		{
			BSTreeNode* tempNode = source;
			source = source->right;
			delete tempNode;
			tempNode = NULL;
			return true;
		}
		
		// TWO CHILDREN
		else
		{
			BSTreeNode* tempNode = source;
			tempNode = tempNode->left;
			
			while( tempNode->right != NULL )
			{
				tempNode = tempNode->right;
			}
				
			source->dataItem = tempNode->dataItem;
			
			removeHelper( source->left, tempNode->dataItem.getKey() );
				
			return true;
		}
	}
	else
	{
		if( deleteKey < source->dataItem.getKey() )
		{
			return removeHelper( source->left, deleteKey );
		}
		else
		{
			return removeHelper( source->right, deleteKey );
		}
	}
}

/**
 * Write Keys.
 * 
 * This function writes the keys out in ascending order.  It calls the
 * writeKeyHelper to do this.
 * 
 * @pre A tree must exist.
 * @post If a tree exists then it will write the keys out in acesnding order.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::writeKeys() const
{
	writeKeysHelper( root );
	cout << endl;
}

/**
 * Write Key Helper.
 * 
 * This function helps writeKey function.  It takes in a source node and
 * write the keys in acsending order.  The writeKeyHelper calls it self
 * recursively in order to do this.
 * 
 * @pre A tree must exist.
 * @post If a tree exists then it will write the keys out in acesnding order.
 * 
 * @param BSTreeNode pointer source.
 * 
 * @note ALGORITHM: This function checks to see if the soure is not null.
 * If the source is not empty then it calls itself with the source's left.
 * After that it outputs the key and the calls itself with the source's right.
 * This process is a in order traversal of the list and it outputs the 
 * keys in ascending order. This is recursive function.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::writeKeysHelper( BSTreeNode* source ) const
{
	if( source != NULL )
	{
		writeKeysHelper( source->left );
		cout << source->dataItem.getKey() << " ";
		writeKeysHelper( source->right );
	}
}

/**
 * Clear.
 * 
 * This function clears a tree if it is not empty. It does this by calling
 * the clearHelper function.
 * 
 * @pre A tree must exist to get cleared.
 * @post If a tree exists then it will be cleared.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::clear()
{
	if( !isEmpty() )
	{
		clearHelper( root );
	}
}

/**
 * Clear Helper.
 * 
 * This function helps the clear function in clearing the tree.  It does
 * this recursively.
 * 
 * @pre A source will be passed to the function.
 * @post The source's node will be deleted.
 * 
 * @param BSTreeNode pointer source passed by reference.
 * 
 * @note ALGORITHM: The function checks to see if the source's left is
 * not equal to null.  If this is true then it will call itself with 
 * source's left pointer.  It the source's right pointer is not equal to
 * null then it will call itself with source's right pointer.  After all
 * the traversal the source node is deleted and set to null.  The tree
 * is traversed in post order recursively.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::clearHelper( BSTreeNode* &source )
{
	if( source->left != NULL )
	{
		clearHelper( source->left );
	}
	if( source->right != NULL )
	{
		clearHelper( source->right );
	}
	
	delete source;
	source = NULL;	
}

/**
 * Empty Check.
 * 
 * This function checks to see if the tree is empty.
 * 
 * @return Returns a bool with result of if root is equal to null.
 * 
 */
template< typename DataType, class KeyType >
bool BSTree< DataType, KeyType >::isEmpty() const
{
	return ( root == NULL );
}

/**
 * Get Count.
 * 
 * This function gets the number of nodes within the tree.  It calls 
 * countHelper to do this.  It returns the number of nodes counted.
 * 
 * @return int count
 * 
 */
template< typename DataType, class KeyType >
int BSTree< DataType, KeyType >::getCount() const
{
	int count = 0;
	
	if( !isEmpty() )
	{
		countHelper( root, count );
	}
	
	return count;
}

/**
 * Count Helper.
 * 
 * This function helps the getCount function count the nodes within a tree.
 * 
 * @pre no nodes are counted.
 * @post all the nodes are counted. 
 * 
 * @param BSTreeNode pointer source
 * @param int count passed by referenece
 * 
 * @note ALGORITHM: This function uses a in order traversal to count all
 * the nodes within in a tree.  If the source node is not empty then it
 * calls itself with the source's left pointer and the count.  The count
 * is incremented and then countHelper is called with the source's right
 * and the count. This is done recursively.  
 * 
 * @return count is returned by reference.
 * 
 */
template< typename DataType, class KeyType >
void BSTree< DataType, KeyType >::countHelper( BSTreeNode* source, int &count ) const
{
	if( source != NULL )
	{
		countHelper( source->left, count );
		count++;
		countHelper( source->right, count );
	}	
}

/**
 * Get Height.
 * 
 * This function gets the height of the tree.  It does this by calling
 * the heightHelper function.
 * 
 * @return The height of the tree.
 * 
 */
template< typename DataType, class KeyType >
int BSTree< DataType, KeyType >::getHeight() const
{	
	return heightHelper( root );
}

/**
 * Height Helper.
 * 
 * This function helps the getHeight function get the height of the tree.
 * It does this recursively until the max height of the tree is found.
 * 
 * @pre A tree must exist to get the height.
 * @post The height of the tree is returned.
 * 
 * @param BSTreeNode pointer source
 * 
 * @return The hieght is returned.
 * 
 */
template< typename DataType, class KeyType >
int BSTree< DataType, KeyType >::heightHelper( BSTreeNode* source ) const
{
	if( source == NULL )
	{
		return 0;
	}
	else
	{
		int leftHeight = heightHelper( source->left );
		int rightHeight = heightHelper( source->right );
		
		if( leftHeight > rightHeight )
		{
			return ( leftHeight + 1 );
		}
		else
		{
			return ( rightHeight + 1 );
		}
	}
}
