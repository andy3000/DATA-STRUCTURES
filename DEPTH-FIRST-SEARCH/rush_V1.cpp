/** 
 * @file rush.cpp
 * @author Amardeep Singh
 * @brief This program sets up a game board with vehicles on it and solves
 * the game of rush hour in the least amount of moves.
 * @date April 29th 2014
*/
#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct Vehicle
{
		int vehicleRow;
		int vehicleCol;
		int vehicleType;
		char vehicleDirection;
};

struct Board
{
	char gameBoard[ 6 ][ 6 ];
	Vehicle vehiclesOnBoard[ 25 ];
	int moveCount;
};

string boardToString( Board gameBoard );

bool dejaVu( string board, map<string, string> dejaVuBoard );

void setBoard( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int numberOfVehicles );

bool moveVehicleForward( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int vehicleNumber );

bool moveVehicleBackward( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int vehicleNumber );
				
int solveIt( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int numberOfVehicles );

int main()
{	
	Vehicle vehiclesInGame[ 25 ];
	int vehicleCount = 0;
	int scenarioNumber = 1;
	
	ifstream fin;
	
	char gameBoard[ 6 ][ 6 ];

	cin >> vehicleCount;
	
	while( vehicleCount > 0 )
	{
		for( int i = 0; i < vehicleCount; i++ )
		{
			cin >> vehiclesInGame[ i ].vehicleType;
			cin >> vehiclesInGame[ i ].vehicleDirection;
			cin >> vehiclesInGame[ i ].vehicleRow;
			cin >> vehiclesInGame[ i ].vehicleCol;
		}
		
		setBoard( gameBoard, vehiclesInGame, vehicleCount );
		
		cout << "Scenario " << scenarioNumber << " requires " << 
		solveIt( gameBoard, vehiclesInGame, vehicleCount ) << " moves" << endl;
		
		cin >> vehicleCount;
		scenarioNumber++;
	}
					
	return 0;
}



/**
 * This functions sets the game board up.
 * 
 * This function sets up the game board with vehicles so the game will be
 * ready for playing.  The front of the vehicle is already set and it is
 * used to mark the board with the appropriate amount of spaces taken up
 * by the vehicle given its a car or a truck.  Before the vehicles are 
 * place upon the board, the entire board is marked with an 'X' to represent
 * a empty slot which contains no vehicle.
 * 
 * @param gameBoard[][]		The 2D char array to represent the game board.
 * @param vehiclesInGame	An array of vehicles containing all vehicles in current game.
 * @param numberOfVehicles	The number of vehicles in the current game.
 * 
 * @pre The gameBoard is empty and uninitialized.
 * @post The gameBoard contains all the vehicles and is marked with an 'X'
 * for empty spaces and the number of the vehicle in the appropriate amount
 * of spaces.
 */
void setBoard( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int numberOfVehicles )
{	
	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			gameBoard[ i ][ j ] = 'X';
		}
	}	
		
	for( int i = 0; i < numberOfVehicles; i++ )
	{
		gameBoard[ vehiclesInGame[ i ].vehicleRow ][ vehiclesInGame[ i ].vehicleCol ] = i + '0';
		
		for( int j = 1; j < ( vehiclesInGame[ i ].vehicleType ); j++ )
		{
			if( vehiclesInGame[ i ].vehicleDirection == 'H' )
			{
				gameBoard[ vehiclesInGame[ i ].vehicleRow ][ vehiclesInGame[ i ].vehicleCol + j ] = i + '0';
			}
			else
			{
				gameBoard[ vehiclesInGame[ i ].vehicleRow + j ][ vehiclesInGame[ i ].vehicleCol ] = i + '0';
			}
		}
	}
}

/**
 * This function moves a vehicle forward.
 * 
 * This function moves a vehicle forward on the game board.  The vehicle
 * checks a few different scenarios to see if it is actually possibel to 
 * move the vehicle forward before it actually does.  The function 
 * checks the bounds to see if the vehicle is already not at the edge of 
 * the gameBoard.  If the vehicle is at the edge then it returns false.
 * Given the type of vehicle & it's orientation it checks to see if there
 * is a 'X' in front of the vehicle.  If there is an 'X' this means that
 * there is an empty spot in front of the vehicle and it is okay for it 
 * to move forward.  If there is any other symbol there it means that the
 * car cannot move forward and it returns false.  If the vehicle can move
 * forward then the function moves the vehicle forward, marks the new 
 * location on the board and updates the row or column of the vehicle.
 * 
 * @param gameBoard[][]		The 2D char array to represent the game board.
 * @param vehiclesInGame	An array of vehicles containing all vehicles in current game.
 * @param vehicleNumber		This number represents the vehicle to be moved.
 * 
 * @pre The vehicle is in it's current location
 * @post If the vehicle can move forward the vehicle is moved forward
 * and the gameBoard is updated with the new location of the vehicle.
 * 
 * @return The function returns a bool of whether or not the vehicle was
 * moved backward. 
 */
bool moveVehicleForward( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int vehicleNumber )
{
	int row, col, type;
	char direction;
		
	row = vehiclesInGame[ vehicleNumber ].vehicleRow;
	col = vehiclesInGame[ vehicleNumber ].vehicleCol;
	type = vehiclesInGame[ vehicleNumber ].vehicleType;
	direction = vehiclesInGame[ vehicleNumber ].vehicleDirection;
	
	if( type == 2 )
	{
		if( ( direction == 'V' && row == 4 ) || ( direction == 'H' && col == 4 ) )
		{
			return false;
		}
	}
	else
	{
		if( ( direction == 'V' && row == 3 ) || ( direction == 'H' && col == 3 ) )
		{
			return false;
		}
	}
		
	if( ( direction == 'V' && gameBoard[ row + type ][ col ] != 'X' ) ||
		( direction == 'H' && gameBoard[ row ][ col + type ] != 'X' ) )
	{
		return false;
	}		
	
	if( direction == 'H' )
	{
		gameBoard[ row ][ col + type ] = vehicleNumber + '0';
		gameBoard[ row ][ col ] = 'X';
		vehiclesInGame[ vehicleNumber ].vehicleCol = col + 1;		
		return true;
	}
	else
	{
		gameBoard[ row + type ][ col ] = vehicleNumber + '0';
		gameBoard[ row ][ col ] = 'X';
		vehiclesInGame[ vehicleNumber ].vehicleRow = row + 1;		
		return true;
	}
	
	return false;
}

/**
 * This function moves a vehicle backward.
 * 
 * This function moves a vehicle backward on the game board.  The vehicle
 * checks a few different scenarios to see if it is actually possible to 
 * move the vehicle backward before it actually does.  The function 
 * checks the bounds to see if the vehicle is already not at the edge of 
 * the gameBoard.  If the vehicle is at the edge then it returns false.
 * Given the type of vehicle & it's orientation it checks to see if there
 * is a 'X' behind of the vehicle.  If there is an 'X' this means that
 * there is an empty spot in front of the vehicle and it is okay for it 
 * to move backward.  If there is any other symbol there it means that the
 * car cannot move backward and it returns false.  If the vehicle can move
 * backward then the function moves the vehicle backward, marks the new 
 * location on the board and updates the row or column of the vehicle.
 * 
 * @param gameBoard[][]		The 2D char array to represent the game board.
 * @param vehiclesInGame	An array of vehicles containing all vehicles in current game.
 * @param vehicleNumber		This number represents the vehicle to be moved.
 * 
 * @pre The vehicle is in it's current location
 * @post If the vehicle can move backward the vehicle is moved backward
 * and the gameBoard is updated with the new location of the vehicle.
 * 
 * @return The function returns a bool of whether or not the vehicle was
 * moved backward.
 */
bool moveVehicleBackward( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int vehicleNumber )
{
	int row, col, type;
	char direction;
		
	row = vehiclesInGame[ vehicleNumber ].vehicleRow;
	col = vehiclesInGame[ vehicleNumber ].vehicleCol;
	type = vehiclesInGame[ vehicleNumber ].vehicleType;
	direction = vehiclesInGame[ vehicleNumber ].vehicleDirection;
	
	if( ( direction == 'V' && row == 0 ) || ( direction == 'H' && col == 0 ) )
	{
		return false;
	}	

	if( ( direction == 'V' && gameBoard[ row - 1 ][ col ] != 'X' ) ||
		( direction == 'H' && gameBoard[ row ][ col - 1 ] != 'X' ) )
	{
		return false;
	}		

	if( direction == 'H' )
	{
		gameBoard[ row ][ col - 1 ] = vehicleNumber + '0';
		gameBoard[ row ][ col + type - 1 ] = 'X';
		vehiclesInGame[ vehicleNumber ].vehicleCol = col - 1;
		return true;
	}
	else
	{
		gameBoard[ row - 1 ][ col ] = vehicleNumber + '0';
		gameBoard[ row + type - 1 ][ col ] = 'X';
		vehiclesInGame[ vehicleNumber ].vehicleRow = row - 1;
		return true;		
	}
	
	return false;
}

/**
 * This funciton solves the rush hour game.
 * 
 * This function moves the vehicles forward and backward until a solution
 * ten moves or under has been reached.  The function uses recursion to
 * accomplish this task.  The base case of the function includes two 
 * stopping conditions.  The first stopping condtion is attained if the
 * vehicle reaches the end of the board.  The second stopping condition
 * is if the numberOfMoves exceeds the bestMoves or the least amount of 
 * moves required to solve the game.  If neither stopping condition applies
 * then the funciton calls itself recursively.  The function loops through
 * all of the vehicles and checks to see if they can move forward or if 
 * they can move backward.  If either is true then it calls the function
 * again by with numberOfMoves incremented by one. Once the recursive call
 * reaches an end it backtracks and moves the vehicle back to it's original
 * location.  The lowest number of moves it took to solve the game is recorded
 * and the function returns if the game was solved or not.
 * 
 * @param gameBoard[][]		The 2D char array to represent the game board.
 * @param vehiclesInGame	An array of vehicles containing all vehicles in current game.
 * @param numberOfVehicles	The number of vehicles in the current game.
 * 
 * @pre the board will be in its original state
 * @post all possible solutions will have been found and the lowest number
 * of moves required to solve the game will be records
 * 
 * @return The function will return a int stating the number of moves.
 * 
 */
int solveIt( char gameBoard[ 6 ][ 6 ], Vehicle vehiclesInGame[], int numberOfVehicles )
{
	Board tempBoard;
	queue<Board> boardQueue;
	map<string, int> dejaVuMap;
	
	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			tempBoard.gameBoard[ i ][ j ] = gameBoard[ i ][ j ];
		}
	}
	
	for( int i = 0; i < numberOfVehicles; i++ )
	{
		tempBoard.vehiclesOnBoard[ i ] = vehiclesInGame[ i ];
	}
	
	tempBoard.moveCount = 0;
	
	boardQueue.push( tempBoard );
	dejaVuMap[ boardToString( tempBoard ) ] = 1;		
	
	while( !boardQueue.empty() )
	{
		tempBoard = boardQueue.front();
		boardQueue.pop();	
		
		if( ( tempBoard.gameBoard[ tempBoard.vehiclesOnBoard[ 0 ].vehicleRow ][ 4 ] == '0' && 
			  tempBoard.gameBoard[ tempBoard.vehiclesOnBoard[ 0 ].vehicleRow ][ 5 ] == '0' ) ||
			( tempBoard.gameBoard[ tempBoard.vehiclesOnBoard[ 0 ].vehicleRow ][ 3 ] == '0' && 
			  tempBoard.gameBoard[ tempBoard.vehiclesOnBoard[ 0 ].vehicleRow ][ 4 ] == '0' && 
			  tempBoard.gameBoard[ tempBoard.vehiclesOnBoard[ 0 ].vehicleRow ][ 5 ] == '0' ) )
		{			
			return tempBoard.moveCount;
		}		
		
		for( int i = 0; i < numberOfVehicles; i++ )
		{			
			if( moveVehicleForward( tempBoard.gameBoard, tempBoard.vehiclesOnBoard, i ) )
			{				
				if( dejaVuMap.find( boardToString( tempBoard ) ) == dejaVuMap.end() )
				{							
					tempBoard.moveCount++;
					dejaVuMap[ boardToString( tempBoard ) ] = 1;
					boardQueue.push( tempBoard );
					tempBoard.moveCount--;
				}
				
				moveVehicleBackward( tempBoard.gameBoard, tempBoard.vehiclesOnBoard, i );
			}		
			
			
			if( moveVehicleBackward( tempBoard.gameBoard, tempBoard.vehiclesOnBoard, i ) )
			{			
				if( dejaVuMap.find( boardToString( tempBoard ) ) == dejaVuMap.end() )
				{
					tempBoard.moveCount++;
					dejaVuMap[ boardToString( tempBoard ) ] = 1;
					boardQueue.push( tempBoard );
					tempBoard.moveCount--;
				}
				
				moveVehicleForward( tempBoard.gameBoard, tempBoard.vehiclesOnBoard, i );
			}			
		}			
	}		
	
	return -9999;
}

/**
 * boardToString
 * 
 * This function converts a board into a string.
 * 
 * @param Board tempBoard
 * 
 * @pre A board exists
 * @post A board is converted to a string
 * 
 * @return string board
 * 
 */
string boardToString( Board tempBoard  )
{
	string board;
	
	for( int i = 0; i < 6; i++ )
	{
		for( int j = 0; j < 6; j++ )
		{
			board += tempBoard.gameBoard[ i ][ j ];
		}
	}		
	
	return board;
}
