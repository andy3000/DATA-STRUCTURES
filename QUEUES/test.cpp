#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int num;
	srand( 7 );
	
	while( true )
	{
		num = rand();
		cout << num << endl;
		cin.get();
	}
	
	return 0;
}
