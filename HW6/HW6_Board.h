#ifndef Ilkergul_Gul_Ilker_HW6_Class_Board_h
#define Ilkergul_Gul_Ilker_HW6_Class_Board_h

#include <iostream>
using namespace std;

class Board
{
private:
	char theBoard[2][6];

public:
	// Default constructor
	Board();
	// Displaying the the board
	void displayBoard();
	// returning the char element of wanted coordinates
	char getOwner(int & row,int & column);
	// setting the char element of wanted coordinates
	void setOwner(int & row, int & column, char & owner);
	// checking whether there is vacant place or not
	bool isFull() const;
	// counting how many elements are equal to given character in our matrix
	int countOwnedCells(char & owner);

};



#endif
