/** @file rush.cpp
@author Ben Wendell
@version Version 1.0
@brief This program sets up a Rush Hour game board and solves it.
@details The program reads in from the console the pieces of the Rush
* Hour game. They are different sizes and different locations, and the
* program sets up the board and moves the pieces around to solve it.
@date Wednesday, February 26, 2014
*/

/**
@mainpage
This program introduces us to the idea of branch and bounds. The idea is
* a little tricky to wrap your head around at first, but it becomes easier
* after working with it for a while. The idea is that you call a function 
* recursively and that function calls itself recursively and so on until 
* you reach a stopping condition. This stopping condition bounds the rest
* of the recursive calls to make it easier to solve.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

#include <iostream>
#include <fstream>

using namespace std;

const int maxRows = 6;
const int maxCols = 6;
const int maxPieces = 25;

struct car
{
	int size;
	int row;
	int col;
	char orientation;
};

void setUpBoard( char board[ maxRows ][ maxCols ], car gamePieces[],
				int totalPieces );
				
bool moveBackward( char board[ maxRows ][ maxCols ], car gamePieces[],
				int carNumber );
				
bool moveForward( char board[ maxRows ][ maxCols ], car gamePieces[],
				int carNumber );
				
bool solveIt( char board[ maxRows ][ maxCols ], car gamePieces[],
				int movesSoFar, int& movesToBeat, int totalPieces );

int main()
{
	ifstream fin;
	char board[ maxRows ][ maxCols ];
	int totalPieces = 0;
	bool solved = false;
	int movesToBeat = 10;
	int movesSoFar = 0;
	
	int scenarioNum = 1;
	
	cin >> totalPieces;
	car gamePieces[ totalPieces ];
	
	while( totalPieces > 0 )
	{			
		for( int i = 0; i < totalPieces; i++ )
		{
			cin >> gamePieces[ i ].size;
			cin >> gamePieces[ i ].orientation;
			cin >> gamePieces[ i ].row;
			cin >> gamePieces[ i ].col;		
		}
		
		setUpBoard( board, gamePieces, totalPieces );
		
		solved = solveIt( board, gamePieces, movesSoFar, movesToBeat, totalPieces );

		cout << "Scenario " << scenarioNum << " requires " << movesToBeat << " moves" << endl;
	
		cin >> totalPieces;
		scenarioNum++;	
	}

	return 0;
}

/**
 * This function reads in all of the game pieces from the console and
 * creates the game board. 
 * 
 * The program has to set up a board of game pieces and it has to get
 * car 0 off of the board. This function takes the game pieces that have
 * been read from the keyboard and puts them into their correct spot. 
 * Each game pieces has a location, size, and orientation. This function
 * sets up the cars into their correct spots and then fills the empty 
 * spaces with an X. This allows the program to see if it a location is
 * empty because there will be an X there. 
 * 
 * This function has no other functionality than to set up the two
 * dimensional array and put the cars and trucks into their positions.
 * 
 * @param board[][]  the 2D array for the game
 * @param gamePieces[]  the array of cars for the game pieces
 * @param totalPieces  the total pieces in the gamePieces array
 * @return This function is a void.
 * 
 * @pre The board will be empty.
 * @post The board will have all the game pieces in their position.
 * 
*/
void setUpBoard( char board[ maxRows ][ maxCols ], car gamePieces[],
				int totalPieces )
{
	int i = 0, j = 0;
	
	// fill board with Xs
	for( i = 0; i < maxRows; i++ )
	{
		for( j = 0; j < maxCols; j++ )
		{
			board[ i ][ j ] = 'X';
		}
	}
	
	// put cars in correct spot
	for( i = 0; i < totalPieces; i++ )
	{
		board[ gamePieces[ i ].row ][ gamePieces[ i ].col ] = (i + 48 );
		
		for( j = 1; j < ( gamePieces[ i ].size ); j++ )
		{
			if( gamePieces[ i ].orientation == 'H' )		
				board[ gamePieces[ i ].row ][ gamePieces[ i ].col + j ] = ( i + 48 );
			else
				board[ gamePieces[ i ].row + j ][ gamePieces[ i ].col ] = ( i + 48 );
		}
	}
}

/**
 * This function moves the game piece backward if possible. 
 * 
 * The program has to move each piece backward to check if it helps to 
 * solve the board. This function moves the location of the current car
 * back one space and fills the space in front with an empty location. 
 * This function has to make sure that the game piece will not go off 
 * of the board. It does this by checking to make sure it isn't at the
 * top or the left of the board. It also has to check if there is another
 * game piece in behind of it. It checks if there is a number behind 
 * indicating that there is a car in back. If both of these conditions
 * fail, then it is possible for the car to move backward. It will then
 * move the game piece backwards one position, either up or left based
 * on the orientation of the car.
 * 
 * This function has no other functionality than to move the piece backwards.
 * 
 * @param board[][]  the 2D array for the game
 * @param gamePieces[]  the array of cars for the game pieces
 * @param carNumber  the car that is trying to move backward
 * @return This function returns a bool.
 * 
 * @pre The car will be in its current position.
 * @post The car will be moved backward if possible.
 * 
*/
bool moveBackward( char board[ maxRows ][ maxCols ], car gamePieces[],
				int carNumber )
{
	int rowLoc, colLoc;
	char orient;
	orient = gamePieces[ carNumber ].orientation;
	rowLoc = gamePieces[ carNumber ].row;
	colLoc = gamePieces[ carNumber ].col;
	
	if( ( orient == 'V' && rowLoc == 0 ) || ( orient == 'H' && colLoc == 0 ) )
	{
		return false;
	}
	else if( ( orient == 'V' && board[ rowLoc - 1 ][ colLoc ] != 'X' ) ||
		( orient == 'H' && board[ rowLoc ][ colLoc - 1 ] != 'X' ) )
	{
		return false;
	}
	else if( orient == 'V' )
	{
		board[ rowLoc - 1 ][ colLoc ] = ( carNumber + 48 );
		board[ rowLoc + gamePieces[ carNumber ].size - 1 ][ colLoc ] = 'X';
		gamePieces[ carNumber ].row = ( rowLoc - 1 );
		return true;
	}
	else if( orient == 'H' )
	{
		board[ rowLoc ][ colLoc - 1 ] = ( carNumber + 48 );
		board[ rowLoc ][ colLoc + gamePieces[ carNumber ].size - 1 ] = 'X';
		gamePieces[ carNumber ].col = ( colLoc - 1 );
		return true;
	}		
	
	return false;
}

/**
 * This function moves the game piece forward if possible. 
 * 
 * The program has to move each piece forward to check if it helps to 
 * solve the board. This function moves the location of the current car
 * forward one space and fills the space behind it with an empty location. 
 * This function has to make sure that the game piece will not go off 
 * of the board. It does this by checking to make sure it isn't at the
 * botton or the right of the board. It also has to check if there is another
 * game piece in front of it. It checks if there is a number in front 
 * indicating that there is a car in front. If both of these conditions
 * fail, then it is possible for the car to move forward. It will then
 * move the game piece forward one position, either down or right based
 * on the orientation of the car.
 * 
 * This function has no other functionality than to move the piece forward.
 * 
 * @param board[][]  the 2D array for the game
 * @param gamePieces[]  the array of cars for the game pieces
 * @param carNumber  the car that is trying to move forward
 * @return This function returns a bool.
 * 
 * @pre The car will be in its current position.
 * @post The car will be moved forward if possible.
 * 
*/
bool moveForward( char board[ maxRows ][ maxCols ], car gamePieces[],
				int carNumber )
{
	int rowLoc, colLoc, carSize;
	char orient;
	orient = gamePieces[ carNumber ].orientation;
	rowLoc = gamePieces[ carNumber ].row;
	colLoc = gamePieces[ carNumber ].col;
	carSize = gamePieces[ carNumber ].size;
	
	if( ( orient == 'V' && rowLoc == 5 ) || ( orient == 'H' && colLoc == 5 ) )
	{

		return false;
	}
	else if( ( orient == 'V' && board[ rowLoc + carSize ][ colLoc ] != 'X' ) ||
		( orient == 'H' && board[ rowLoc ][ colLoc + carSize ] != 'X' ) )
	{
		return false;
	}
	else if( orient == 'V' )
	{
		board[ rowLoc + carSize ][ colLoc ] = ( carNumber + 48 );
		board[ rowLoc ][ colLoc ] = 'X';
		gamePieces[ carNumber ].row = ( rowLoc + 1 );
		return true;
	}
	else if( orient == 'H' )
	{
		board[ rowLoc ][ colLoc + carSize ] = ( carNumber + 48 );
		board[ rowLoc ][ colLoc ] = 'X';
		gamePieces[ carNumber ].col = ( colLoc + 1 );
		return true;
	}
	
	return false;
}

/**
 * This function is called to solve the game.
 * 
 * The program solves the game by moving each piece forward and backward
 * many times to see if it is possible to solve the board. This function
 * is called recursively to try to solve the problem. The base case of 
 * this recursive function is if the game piece is at the ending position
 * or if the current number of moves is greater than the movestobeat.
 * This recursive function will start by moving a piece forward if possible.
 * It will then call itself recursively and so on. If a branch fails, it will
 * return all the way back and move onto another branch. If a solution is
 * found and it is less moves than the previous solution, then this will 
 * become the new base case. These two properties are exactly what branch
 * and bound is. You look for a solution and snip any of the branches
 * that are longer than that solution.
 * 
 * This function has no other functionality than to move the piece backwards.
 * 
 * @param board[][]  the 2D array for the game
 * @param gamePieces[]  the array of cars for the game pieces
 * @param movesSoFar  the current number of moves for the board
 * @param movesToBeat  the number of moves that bound the function
 * @param totalPieces  the total number of pieces on the board
 * @return This function returns a bool.
 * 
 * @pre The board won't have been moved.
 * @post The board will be solved if possible.
 * 
*/
bool solveIt( char board[ maxRows ][ maxCols ], car gamePieces[],
				int movesSoFar, int& movesToBeat, int totalPieces )
{			
	if( gamePieces[ 0 ].col == 4 )
	{
		cout << "Here" << endl;
		movesToBeat = movesSoFar;
		return true;
	}
	else if( movesSoFar >= movesToBeat )
	{
		return false;
	}
	else
	{
		for( int i = 0; i < totalPieces; i++ )
		{
			if( moveForward( board, gamePieces, i ) )
			{
				solveIt( board, gamePieces, movesSoFar + 1,	movesToBeat, totalPieces );
				moveBackward( board, gamePieces, i );
			}
			if( moveBackward( board, gamePieces, i ) )
			{
				solveIt( board, gamePieces, movesSoFar + 1, movesToBeat, totalPieces );
				moveForward( board, gamePieces, i );
			}
		}
	}
	
	return false;
}





