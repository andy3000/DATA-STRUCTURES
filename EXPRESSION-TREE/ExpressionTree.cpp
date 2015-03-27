/** 
 * @file ExpressionTree.cpp
 * @author Amardeep Singh
 * @brief This program creates and expression tree and evaluates it.
 * @date March 4th 2014
*/
#include <ctype.h>
#include <stdlib.h>
#include "ExpressionTree.h"
#include "show8.cpp"

/**
 * Default constructor.
 * 
 * The default constructor initializes the root to null.
 * 
 * @post root is equal to null.
 * 
 */
template <typename DataType>
ExprTree<DataType>::ExprTree()
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
 * @param ExprTree source.
 * 
 */ 
template <typename DataType>
ExprTree<DataType>::ExprTree( const ExprTree &source )
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
 * @param ExprTree source
 * @return *this
 * 
 */
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=( const ExprTree &source )
{
	if( this != &source )
	{
		if( source.isEmpty() )
		{
			clear();
			root = NULL;
		}
		else
		{
			clear();
			copyHelper( root, source.root );
		}	
	}
	
	return *this;
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
 * @param ExprTreeNode pointer dest pass by reference
 * @param ExprTreeNode pointer source
 * 
 * @note ALGORITHM: The function accpets a dest tree node by reference and a
 * source tree node that contains the data to be copied.  The function checks
 * to see if the data contained in the source node is a digit.  If it is
 * a digit then the dest pointer creates a new node and copies the data
 * from the source.  The left and right of the node are set to null.  The
 * function then checks to see if the source data is an operator.  If it
 * is an operator then it creates a new node and copies the data and sets
 * left and right equal to null.  The function then calls it self recursively
 * with the dest node's left pointer and the source node's left pointer.
 * The function then calls itself with the dest node's right pointer
 * and the source node's right pointer.  Through recursion all of the nodes
 * are visited and copied over to the dest tree.
 * 
 */ 
template <typename DataType>
void ExprTree<DataType>::copyHelper( ExprTreeNode* &dest, ExprTreeNode* source )
{
	if( isdigit( source->dataItem ) )
	{
		dest = new ExprTreeNode( source->dataItem, NULL, NULL );
	}
	
	if( source->dataItem == '+' || source->dataItem == '-' || 
		source->dataItem == '*' || source->dataItem == '/' )
	{
		dest = new ExprTreeNode( source->dataItem, NULL, NULL );
		copyHelper( dest->left, source->left );
		copyHelper( dest->right, source->right );
	}
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
template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	if( !isEmpty() )
	{
		clear();
	}
}

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
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode( char item, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr )
{
	dataItem = item;
	left = leftPtr;
	right = rightPtr;
}

/**
 * Build.
 * 
 * The build function builds the tree.  It does this by calling the build
 * helper function.
 * 
 * @pre The tree is empty.
 * @post The tree is built.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::build()
{
	if( isEmpty() )
	{
		buildHelper( root );
	}
}

/**
 * Build Helper.
 * 
 * This function accepts a node pointer by reference and builds the tree.
 * It calls itself recursively until the tree is built.  
 * 
 * @pre The tree is empty.
 * @post The tree is built.
 * 
 * @param ExprTreeNode pointer source which is passed by reference.
 * 
 * @note ALGORITHM: The function reads in a character from the user.
 * The function then determines if it is a digit.  If it is a digit then
 * a new node is created with the digit and left and right pointers set
 * to null.  The function then checks to see if the character entered is
 * a operator.  If it is then the operator is stored in a new node with
 * it's left and right pointer set to null.  The function calls itself
 * with the new nodes left and then the new nodes right.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::buildHelper( ExprTreeNode* &source )
{
	char dummy;
	
	cin >> dummy;
	
	if( isdigit( dummy ) )
	{
		source = new ExprTreeNode( dummy, NULL, NULL );
	}
	
	if( dummy == '+' || dummy == '-' || dummy == '*' || dummy == '/' )
	{
		source = new ExprTreeNode( dummy, NULL, NULL );
		buildHelper( source->left );
		buildHelper( source->right );
	}	
}

/**
 * Evalutate.
 * 
 * This function evalutes the tree and returns the DataType.  It does this
 * by calling the evalHelper function.
 * 
 * @pre A tree will note be evaluated.
 * @post The tree will be evaluated.
 * 
 * @return DataType
 * 
 */
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{	
	return evalHelper( root );
}

/**
 * Evaluate Helper.
 * 
 * This function helps to evaluate the function.  It calls itself 
 * recursively and evaluates all of the terms within the tree.  It takes
 * in a node pointer and checks to see if the source's data is a digit.
 * If it is a digit then it is converted to an float and returned.
 * Otherwise the function checks to see if the source's data is an operator.
 * If it is an operator then it returns what will be returned when the
 * evalHelper is called with the left pointer, the operator that is used
 * and what will be returned when the evalHellper is called with the right
 * pointer of the source.
 * 
 * @pre A tree will note be evaluated.
 * @post The tree will be evaluated.
 * 
 * @param ExprTreeNode pointer source.
 * 
 * @return The evaluated expression(s).
 * 
 */
template <typename DataType>
float ExprTree<DataType>::evalHelper( ExprTreeNode* source ) const
{
	float number; 
	char tempString[ 2 ];

	if( isdigit( source->dataItem ) )
	{
		tempString[ 0 ] = source->dataItem;
		tempString[ 1 ] = '\0';
		number = atoi( tempString );
		return number;
	}
	
	if( source->dataItem == '+' )
	{
		return ( evalHelper( source->left ) + evalHelper( source->right ) );
	}
	
	if( source->dataItem == '-' )
	{
		return ( evalHelper( source->left ) - evalHelper( source->right ) );
	}
	
	if( source->dataItem == '*' )
	{
		return ( evalHelper( source->left ) * evalHelper( source->right ) );
	}
	
	if( source->dataItem == '/' )
	{
		return ( evalHelper( source->left ) / evalHelper( source->right ) );
	}
	
	return 0.0;	
}

/**
 * Clear.
 * 
 * The clear function deallocates any memory that was used for a tree.
 * It does this by calling clear helper.
 * 
 * @pre A tree will have memory and root will contain a value.
 * @post Any memory a tree had will be deallocated and root is set to null.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::clear()
{
	if( !isEmpty() )
	{
		clearHelper( root );
		root = NULL;
	}
}

/**
 * Clear Helper.
 * 
 * This function calls it self recursively until all the nodes are deleted.
 * It checks to see if left not equal to null and calls itself with 
 * left node of source until it reaches one that is a leaf.  Then it is 
 * deleted and set to null.  The same process is repeated for the right.
 * 
 * @pre A tree will have memory and root will contain a value.
 * @post Any memory a tree had will be deallocated and root is set to null.
 * 
 * @param ExprTreeNode pointer source.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::clearHelper( ExprTreeNode* source )
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
template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	return( root == NULL );
}

/**
 * Expression.
 * 
 * This function outputs the tree in an expression format.  It checks
 * to see if the tree is not empty.  It it contains data then it checks
 * to see if the root is a digit.  If it is then it outputs the digit.
 * Otherwise it calls expressionHelper to express the expression.
 * 
 * @pre A tree will not be expressed.
 * @post A tree will be expressed.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::expression() const
{
	if( !isEmpty() )
	{
		if( isdigit( root->dataItem ) )
		{
			cout << root->dataItem;
		}
		else
		{
			cout << "(";
			expressionHelper( root );
			cout << ")";
		}
	}
}

/**
 * Expression Helper.
 * 
 * This function helps to express the tree.  It recieves a node pointer 
 * as a source and checks to see if the data item is a digit.  If it is
 * then it is converted to an interger and output.  It also checks to see
 * if the source's data is an operator.  If it is then it calls itself
 * recursively with the source's left pointer and then it outputs the
 * data item and then it calls recursively to the right.  
 * 
 * @pre A tree will not be expressed.
 * @post A tree will be expressed.
 * 
 * @param ExprTreeNode pointer source.
 */
template <typename DataType>
void ExprTree<DataType>::expressionHelper( ExprTreeNode* source ) const
{
	int number; 
	char tempString[ 2 ];
	
	if( isdigit( source->dataItem ) )
	{
		tempString[ 0 ] = source->dataItem;
		tempString[ 1 ] = '\0';
		number = atoi( tempString );		
		cout << number;
	}
	
	if( source->dataItem == '+' || source->dataItem == '-' || 
		source->dataItem == '*' || source->dataItem == '/' )
	{
		if( root != source )
		{
			cout << "(";
		}
		
		expressionHelper( source->left );
		cout << source->dataItem;
		expressionHelper( source->right );
		
		if( root != source )
		{
			cout << ")";
		}		
	}	
}

/**
 * Commute.
 * 
 * This funciton applies the commutative property to the tree.  The 
 * function checks to see if the tree is empty.  If its not empty then
 * it calls commuteHelper.  It clears the dest tree and uses copy helper
 * to create the new commuted tree.  
 * 
 * @pre A tree must exist.
 * @post A tree is recreated with the commutive properties applied.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::commute()
{
	ExprTree <DataType> tempTree;
	
	if( !isEmpty() )
	{
		commuteHelper( tempTree.root, root );
		
		clear();
		
		copyHelper( root, tempTree.root );
		
		tempTree.clear();
	}
}

/**
 * Commute Helper.
 * 
 * This function applies the commuted property to an existing tree.
 * The source and dest pointers are input to the function and it calls
 * it self recursively until the tree is copied over.  The function 
 * checks to see if the source's data is a digit.  If it is then the dest
 * node pointer creates a new node with the source's data.  The function
 * then checks to see if the source's data is an operator. If it is
 * then the function creates a new node in dest tree with the operator
 * and then recursively calls itself with the dest tree's left node and
 * the source tree's right node.  Then it calls itself with the tree's
 * right node and the source tree's left node.  This mirrors the tree
 * thus applying the commutive property.
 * 
 * @pre A tree must exist.
 * @post A tree is recreated with the commutive properties applied.
 * 
 * @param ExprTreeNode pointer by reference tempTree.
 * @param ExprTreeNode pointer source.
 * 
 */
template <typename DataType>
void ExprTree<DataType>::commuteHelper( ExprTreeNode* &tempTree, ExprTreeNode* source )
{
	if( isdigit( source->dataItem ) )
	{
		tempTree = new ExprTreeNode( source->dataItem, NULL, NULL );
	}
	
	if( source->dataItem == '+' || source->dataItem == '-' || 
		source->dataItem == '*' || source->dataItem == '/' )
	{
		tempTree = new ExprTreeNode( source->dataItem, NULL, NULL );
		commuteHelper( tempTree->left, source->right );
		commuteHelper( tempTree->right, source->left );
	}
}

/**
 * isEquvialent.
 * 
 * This function checks to see if two trees are equal. It does this by
 * calling equalHelper.
 * 
 * @return Returns a bool with the result if it is equal or not.
 */
template <typename DataType>
bool ExprTree<DataType>::isEquivalent( const ExprTree &source ) const
{
	return equalHelper( root, source.root );
}

/**
 * Equal Helper.
 * 
 * This function calls itself recursively and checks to see if two
 * trees are equal. It checks to see if both trees are empty. If so then
 * it returns true. If one of the trees nodes is null then it returns
 * false.  Otherwise it checks to see if the data in the each node is the 
 * same and calls itself recursively with the left and the right nodes
 * of each tree.  It returns the bool result of the equivalence.  
 * 
 * @return Returns a bool with the result if it is equal or not.
 * 
 */
template <typename DataType>
bool ExprTree<DataType>::equalHelper( ExprTreeNode* original, ExprTreeNode* compare ) const
{
	if( original == NULL && compare == NULL )
	{
		return true;
	}
	else if( original == NULL )
	{
		return false;
	}
	else if( compare == NULL )
	{
		return false;
	}
	if( original != NULL && compare != NULL )
	{
		return ( original->dataItem == compare->dataItem && 
				 equalHelper( original->left, compare->left ) &&
				 equalHelper( original->right, compare->right ) );
	}
	
	return true;
}
