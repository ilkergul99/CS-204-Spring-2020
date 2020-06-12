#ifndef Ilkergul_Gul_Ilker_Player_h
#define Ilkergul_Gul_Ilker_Player_h

#include <iostream>
#include "Ilkergul_Gul_Ilker_HW6_Board.h"
using namespace std;

class Player
{
private:
	// key for sharing concept related to reference variable
	Board &Game_board;
	char identity_character;
	int row_coordinate;
	int column_coordinate;
	int direction;
	


public:
	// Constructor with parameters
	Player(Board &myBoard, const char & id_character, const int & direction_determiner);
	// moving player in the matrix
	void move(int & move_size);
	// changing the character if it is vacant
	void claimOwnership();
	// checking which character win the game
	bool wins();
	// getting the column coordinate of the player
	int getCol();
	// getting the row coordinate of the player
	int getRow();

};
#endif