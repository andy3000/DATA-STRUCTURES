#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	double number;
	char name[ 256 ];
	long position;
	
	ifstream fin;
	fin.clear();
	fin.open( "accounts.dat" );
	
	position = fin.tellg();
	
	fin >> number;
	cout << number << " ";
	fin >> name;
	cout << name << " ";
	fin >> name;
	cout << name << " ";
	fin >> number;
	cout << number << " ";
	cout << endl;
	
	fin.clear();
	
	//fin.seekg( position );
	
	fin >> number;
	cout << number << " ";
	fin >> name;
	cout << name << " ";
	fin >> name;
	cout << name << " ";
	fin >> number;
	cout << number << " ";
	cout << endl;
	
	//position = fin.tellg();
	
	//fin.seekg( position );
	
	/*
	fin >> number;
	cout << number << " ";
	fin >> name;
	cout << name << " ";
	fin >> name;
	cout << name << " ";
	fin >> number;
	cout << number << " ";
	cout << endl;	
	
	while( fin.good() )
	{
		fin >> number;
		cout << number << " ";
		fin >> name;
		cout << name << " ";
		fin >> name;
		cout << name << " ";
		fin >> number;
		cout << number << " ";
		cout << endl;
	}
	*/
	
	return 0;
}
