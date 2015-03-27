#include <ctype.h>
#include <stdlib.h>
#include "ExpressionTree.h"

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;	
}

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

template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
	if( !isEmpty() )
	{
		clear();
	}
}

template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode( char item, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr )
{
	dataItem = item;
	left = leftPtr;
	right = rightPtr;
}

template <typename DataType>
void ExprTree<DataType>::build()
{
	if( isEmpty() )
	{
		buildHelper( root );
	}
}

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

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{	
	return evalHelper( root );
}

template <typename DataType>
int ExprTree<DataType>::evalHelper( ExprTreeNode* source ) const
{
	int number; 
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
}

template <typename DataType>
void ExprTree<DataType>::clear()
{
	if( !isEmpty() )
	{
		clearHelper( root );
		root = NULL;
	}
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	return( root == NULL );
}

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

template <typename DataType>
void ExprTree<DataType>::commute()
{
	ExprTree <DataType> tempTree;
	
	commuteHelper( tempTree.root, root );
	
	clear();
	
	copyHelper( root, tempTree.root );
	
	tempTree.clear();
}

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

template <typename DataType>
bool ExprTree<DataType>::isEquivalent( const ExprTree &source ) const
{
	return true;
}

template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if ( isEmpty() )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

