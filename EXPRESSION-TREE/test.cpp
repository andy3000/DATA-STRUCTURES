#include "ExpressionTree.cpp"

int main()
{
	ExprTree<int> test;
	ExprTree<int> test2;
	
	test.build();
	//test.showStructure();
	
	test2.build();
	
	test.showStructure();
	test2.showStructure();
	
	cout << endl;
	
	/*
	cout << "evaluation: " << test2.evaluate() << endl;
	
	test2.expression();
	cout << endl << endl;
	
	//test2.commute();
	
	test2.showStructure();
	test2.expression();
	cout << endl << endl;
	*/
	
	if ( test.isEquivalent( test2 ) )
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	
	return 0;
}
