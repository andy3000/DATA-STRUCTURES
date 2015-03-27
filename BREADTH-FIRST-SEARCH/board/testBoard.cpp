#include <iostream>
#include <fstream>
#include "ListLinked.cpp"

using namespace std;

class Vehicle
{
	public:
	
		Vehicle();
		Vehicle( const Vehicle &source );
		Vehicle& operator=( const Vehicle &source );
		
		void setVehicleType( int );
		int getVehicleType();
		
		void setVehicleOrientation( char );
		char getVehicleOrientation() const;
		
		void setVehicleFront( int, int );
		void getVehicleFront( int &, int & );
	
	private:
		
		int frontOfVehicleRow;
		int frontOfVehicleCol;
		
		int vehicleType;
		char direction;
};

class GameBoard
{
	public:
	
		GameBoard();
		GameBoard( const GameBoard &source );
		GameBoard& operator=( const GameBoard &source );
		
		bool moveVehicleForward( int );
		bool moveVehicleBackward( int );
		
		void setVehicles( ifstream & );
		
		void setBoard();
		
		void showBoard();
		
		friend ifstream& operator>>( ifstream &fin, GameBoard &source );
	
	private:
	
		bool vehiclesHaveBeenSet;
		int numberOfVehicles;
	
		char board[ 6 ][ 6 ];
		List <Vehicle> vehiclesOnTheBoard;	
};

int main()
{
	GameBoard test;
	
	ifstream fin;
	
	fin.clear();
	fin.open( "testBoard" );
	
	test.setVehicles( fin );
	test.setBoard();
	test.showBoard();
	
	char move;
	int car;
	
	while( true )
	{
		cin >> car;

		cin >> move;
		
		if( move == 'f' )
		{
			test.moveVehicleForward( car );
		}
		else
		{
			test.moveVehicleBackward( car );
		}
		
		test.showBoard();
	}
								
	
	return 0;
}

Vehicle::Vehicle()
{
	vehicleType = -1;
	
	frontOfVehicleRow = frontOfVehicleCol = -1;
	
	direction = '0';
}

Vehicle::Vehicle( const Vehicle &source )
{	
	frontOfVehicleRow = source.frontOfVehicleRow;
	frontOfVehicleCol = source.frontOfVehicleCol;
	
	vehicleType = source.vehicleType;
	direction = source.direction;
}

Vehicle& Vehicle::operator=( const Vehicle &source )
{
	if( this == &source )
	{
		return *this;
	}
	else
	{	
		frontOfVehicleRow = source.frontOfVehicleRow;
		frontOfVehicleCol = source.frontOfVehicleCol;
		
		vehicleType = source.vehicleType;
		direction = source.direction;
	}
	
	return *this;
}

void Vehicle::setVehicleType( int type )
{
	vehicleType = type;
}

int Vehicle::getVehicleType()
{
	return vehicleType;
}

void Vehicle::setVehicleOrientation( char orientation )
{
	direction = orientation;
}

char Vehicle::getVehicleOrientation() const
{
	return direction;
}

void Vehicle::setVehicleFront( int row, int col )
{
	frontOfVehicleRow = row;
	frontOfVehicleCol = col;	
}

void Vehicle::getVehicleFront( int &row, int &col )
{
	row = frontOfVehicleRow;
	col = frontOfVehicleCol;
}

GameBoard::GameBoard()
{
	vehiclesHaveBeenSet = false;
}
	
void GameBoard::setVehicles( ifstream &fin )
{
	Vehicle temp;
	
	char orientation;
	int vehicleType;
	int number;
	int row, col;
	
	if( !vehiclesHaveBeenSet )
	{
		fin >> number;
		
		if( number > 0 )
		{
			numberOfVehicles = number;		
			
			fin >> vehicleType;
			
			while( vehicleType != 0 )
			{
				temp.setVehicleType( vehicleType );
				fin >> orientation;
				temp.setVehicleOrientation( orientation );
				fin >> row;
				fin >> col;
				temp.setVehicleFront( row, col );
				
				vehiclesOnTheBoard.insertAfter( temp );
				
				fin >> vehicleType;
			}
			
			vehiclesOnTheBoard.gotoBeginning();	
		}
		
		vehiclesHaveBeenSet = true;
	}
}

bool GameBoard::moveVehicleForward( int vehicleNumber )
{
	Vehicle temp;
	int row, col, type;
	char orientation;
	char number = vehicleNumber + '0';
	
	if( vehicleNumber > numberOfVehicles )
	{
		return false;
	}
	else
	{
		for( int i = 0; i < vehicleNumber; i++ )
		{
			vehiclesOnTheBoard.gotoNext();
		}
		
		vehiclesOnTheBoard.getCursor( temp );
		
		temp.getVehicleFront( row, col );
		orientation = temp.getVehicleOrientation();
		type = temp.getVehicleType();
		
		if( orientation == 'H' )
		{
			if( type == 2 )
			{
				if( col + 1 == 5 )
				{
					return false;
				}
				
				if( board[ row ][ col + 2 ] == 'X' )
				{
					board[ row ][ col + 2 ] = number;
					board[ row ][ col ] = 'X';
					
					temp.setVehicleFront( row, col + 1 );
					vehiclesOnTheBoard.replace( temp );
					vehiclesOnTheBoard.gotoBeginning();
					return true;
				}
			}
			else
			{
				if( col + 2 == 5 )
				{
					return false;
				}
				
				if( board[ row ][ col + 3 ] == 'X' )
				{
					board[ row ][ col + 3 ] = number;
					board[ row ][ col ] = 'X';
					
					temp.setVehicleFront( row, col + 1 );
					vehiclesOnTheBoard.replace( temp );
					vehiclesOnTheBoard.gotoBeginning();
					return true;
				}
			}
		}
		else
		{
			if( row == 0 )
			{
				return false;
			}
			
			if( board[ row - 1 ][ col ] == 'X' )
			{
				board[ row - 1 ][ col ] = number;
				
				if( type == 2 )
				{
					board[ row + 1 ][ col ] = 'X';
				}
				else
				{
					board[ row + 2 ][ col ] = 'X';
				}
				
				temp.setVehicleFront( row - 1, col );
				vehiclesOnTheBoard.replace( temp );
				vehiclesOnTheBoard.gotoBeginning();
				return true;
			}
		}
		
		vehiclesOnTheBoard.gotoBeginning();
	}
	
	return false;
}

bool GameBoard::moveVehicleBackward( int vehicleNumber )
{
	Vehicle temp;
	int row, col, type;
	char orientation;
	char number = vehicleNumber + '0';
	
	if( vehicleNumber > numberOfVehicles )
	{
		return false;
	}
	else
	{
		for( int i = 0; i < vehicleNumber; i++ )
		{
			vehiclesOnTheBoard.gotoNext();
		}
		
		vehiclesOnTheBoard.getCursor( temp );
		
		temp.getVehicleFront( row, col );
		orientation = temp.getVehicleOrientation();
		type = temp.getVehicleType();			
		
		if( orientation == 'H' )
		{
			if( col == 0 )
			{
				return false;
			}
			
			if( board[ row ][ col - 1 ] == 'X' )
			{
				board[ row ][ col - 1 ] = number;
				
				if( type == 2 )
				{
					board[ row ][ col + 1 ] = 'X';
				}
				else
				{
					board[ row ][ col + 2 ] = 'X';
				}
				
				temp.setVehicleFront( row, col - 1 );
				vehiclesOnTheBoard.replace( temp );
				vehiclesOnTheBoard.gotoBeginning();
				return true;
			}
		}
		else
		{
			if( type == 2 )
			{
				
				if( row + 1 == 5 )
				{
					return false;
				}
			
				if( board[ row + 2 ][ col ] == 'X' )
				{
					board[ row + 2 ][ col ] = number;
					
					board[ row ][ col ] = 'X';
					
					temp.setVehicleFront( row + 1, col );
					vehiclesOnTheBoard.replace( temp );
					vehiclesOnTheBoard.gotoBeginning();
					return true;
				}
			}
			else
			{
				if( row + 2 == 5 )
				{
					return false;
				}
				
				if( board[ row + 3 ][ col ] == 'X' )
				{
					board[ row + 3 ][ col ] = number;
					
					board[ row ][ col ] = 'X';
					
					temp.setVehicleFront( row + 1, col );
					vehiclesOnTheBoard.replace( temp );
					vehiclesOnTheBoard.gotoBeginning();
					return true;
				}
			}
		}
		
		vehiclesOnTheBoard.gotoBeginning();
	}
	
	return false;
}

void GameBoard::setBoard()
{
	
	Vehicle temp;
	int row, col, type;
	char orientation;
	char number = '0';
	
	if( vehiclesHaveBeenSet )
	{
		for( int i = 0; i < 6; i++ )
		{
			for( int j = 0; j < 6; j++ )
			{
				board[ i ][ j ] = 'X';
			}
		}	
		
		for( int i = 0; i < numberOfVehicles; i++ )
		{
			vehiclesOnTheBoard.getCursor( temp );
			
			temp.getVehicleFront( row, col );
			orientation = temp.getVehicleOrientation();
			type = temp.getVehicleType();
			
			if( orientation == 'H' )
			{
				board[ row ][ col ] = number;
				board[ row ][ col + 1 ] = number;
				
				if( type == 3 )
				{
					board[ row ][ col + 2 ] = number;
				}
			}
			else
			{
				board[ row ][ col ] = number;
				board[ row + 1 ][ col ] = number;
				
				if( type == 3 )
				{
					board[ row + 2 ][ col ] = number;
				}
			}

			number++;
			vehiclesOnTheBoard.gotoNext();
		}
		
		vehiclesOnTheBoard.gotoBeginning();
	}
}

void GameBoard::showBoard()
{
	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			cout << board[ i ][ j ];
		}
		
		cout << endl;
	}
	
	cout << endl;
}

/*	
ifstream& operator>>( ifstream &fin, GameBoard &source )
{
	Vehicle temp;
	
	char orientation;
	int vehicleType;
	int numberOfCars;
	int row, col;
	
	fin >> numberOfCars;
	
	if( numberOfCars > 0 )
	{
		source.numberOfCars = numberOfCars;		
		
		fin >> vehicleType;
		
		while( vehicleType != 0 )
		{
			temp.setVehicleType( vehicleType );
			fin >> orientation;
			temp.setVehicleOrientation( orientation );
			fin >> row;
			fin >> col;
			temp.setVehicleFront( row, col );
			
			source.vehiclesOnTheBoard.insertAfter( temp );
			
			fin >> vehicleType;
		}	
	}
	
	return fin;
}
*/
