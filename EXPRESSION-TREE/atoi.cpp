#include <iostream>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

int main()
{
	float one, two;
	
	cin >> one >> two;
	
	cout << one/two << endl;
	
	return 0;
}

/*
int function()
{
	int one, two;
	
	cin >> one;
	cin >> two;
	
	if( two == 0 )
	{
		throw "Division By Zero";
	}
	
	return one / two;
}

int main()
{
	int number;
	
	try
	{
		number = function();
	}
	catch( const char* message )
	{
		cout << message << endl;
	}
	
	cout << number << endl;
	
	return 0;
}

int main()
{
	char dummy[ 2 ];
	int number;
	
	cout << 1/0 << endl;;
	
	while( true )
	{
		cin >> dummy;
		
		if( isdigit( dummy[ 0 ] ) )
		{
			number = atoi( dummy );
			cout << number << endl;
		}
		else
		{
			cout << dummy << endl;
		}
	}	
	
	int number, number2, result;
	char test[ 16 ];
	
	cin.getline( test, 16 );
	
	while( test[ 0 ] != '\0' )
	{
		number = atoi( test );
		
		cin.getline( test, 16 );
		
		number2 = atoi( test );
		
		result = number + number2;
		
		cout << endl;
		
		cout << result << endl;
		
		cin.getline( test, 16 );
	}
	
	return 0;
}
*/
