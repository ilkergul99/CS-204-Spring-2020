
#include <iostream>
#include "Ilkergul_Gul_Ilker_HW6_Board.h"
using namespace std;

// Board Class Functions

Board::Board()  // Creating the Board 
{
	for(int i=0; i < 2; i++)
	{
		for(int k = 0; k < 6 ; k++)
		{
			theBoard[i][k] = '-';
		}
	}
}

void Board::displayBoard()
{
	for(int i=0; i < 2; i++)
	{
		for(int k = 0; k < 6 ; k++)
		{
			if(k != 5)
			{
				cout << theBoard[i][k] << " " ;
			}
			else
			{
				cout << theBoard[i][k] ;
			}
		}
		cout << endl;
	}
}

char Board::getOwner(int & row, int & column)
{
	return theBoard[row][column];
}

void Board::setOwner(int & row,int & column, char & owner)
{
	theBoard[row][column] = owner;
}

bool Board::isFull() const
{
	int count = 0;
	for(int i=0; i < 2; i++)
	{
		for(int k = 0; k < 6 ; k++)
		{
			if(theBoard[i][k] == '-')
			{
				count++;
			}
		}
	}
	if(count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Board::countOwnedCells(char & owner)
{
	int count = 0;
	for(int i=0; i < 2; i++)
	{
		for(int k = 0; k < 6 ; k++)
		{
			if(theBoard[i][k] == owner)
			{
				count++;
			}
		}
	}
	return count;
}

// Board Class Functions


