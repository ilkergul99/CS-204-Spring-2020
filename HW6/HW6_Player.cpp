#include <iostream>
#include "Ilkergul_Gul_Ilker_HW6_Player.h"
using namespace std;

// Player Class Functions


Player::Player(Board &myBoard, const char & id_character, const int & direction_determiner)
		:Game_board(myBoard), identity_character(id_character), direction(direction_determiner)
	{
		row_coordinate = 0;
		column_coordinate = 0;

	}

void Player::move(int & move_size)
{
	int move = 0;
	if(direction == 0) // for counter clockwise operations
	{
		if(row_coordinate == 0)
		{
			if((column_coordinate - move_size)	< 0)
			{
				row_coordinate = 1;
				move = abs(column_coordinate - move_size);
				column_coordinate = move -1;
			}
			else
			{
				column_coordinate = column_coordinate - move_size;
			}
		}
		else
		{
			if((column_coordinate + move_size) > 5)
			{
				row_coordinate = 0;
				move = column_coordinate + move_size - 6;
				column_coordinate = 5 - move; 
			}
			else
			{
				column_coordinate = column_coordinate + move_size;
			}
		}
	}
	else				// for clockwise operations
	{
		if(row_coordinate == 0)
		{
			if((column_coordinate + move_size) > 5)
			{
				row_coordinate = 1;
				move = column_coordinate + move_size - 6;
				column_coordinate = 5 - move; 
			}
			else
			{
				column_coordinate = column_coordinate + move_size;
			}
		}
		else
		{
			if((column_coordinate - move_size)	< 0)
			{
				row_coordinate = 0;
				move = abs(column_coordinate - move_size);
				column_coordinate = move -1;
			}
			else
			{
				column_coordinate = column_coordinate - move_size;
			}
		}
	}
}

void Player::claimOwnership()
{
	if(Game_board.getOwner(row_coordinate, column_coordinate) == '-')
	{
		Game_board.setOwner(row_coordinate, column_coordinate, identity_character);
	}
}

bool Player::wins()
{
	if( Game_board.countOwnedCells(identity_character) > 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::getCol()
{
	return column_coordinate;
}

int Player::getRow()
{
	return row_coordinate;
}

