#include <iostream>
#include <fstream>

#include <string>
#include "DynamicIntStack.h"
using namespace std;

/******************************************************************************


Date = 3/22/2020
CS204 Third Homework
Purpose = Implement an "area filling" program which makes use of stack

******************************************************************************/

void matrix_size_checker(int & row_size_checker, int & column_size_checker)
{
	string wrong_one;
	cout << "Enter the number of rows: " ;
	cin >> row_size_checker;
	while(cin.fail() || row_size_checker < 3 )								//two options for inputs that we do not want we are checking in this loop
	{
		if(cin.fail())
		{
			cin.clear();													// you need to clear the error flags
			cin >> wrong_one;												// cin stream should also be cleared from wrong input
			cout << wrong_one << " is not valid!" << endl;
		}
		else
		{
			cout << row_size_checker << " is not valid!" << endl;
		}	
		cin.sync();
		cout << "Enter the number of rows: " ;
		cin >> row_size_checker;
	}

	cout << "Enter the number of columns: " ;
	cin >> column_size_checker;
	while(cin.fail() || column_size_checker < 3 )							//two options for inputs that we do not want we are checking in this loop
	{
		if(cin.fail())
		{
			cin.clear();													// you need to clear the error flags 
			cin >> wrong_one;												// cin stream should also be cleared from wrong input
			cout << wrong_one << " is not valid!" << endl;
		}
		else
		{
			cout << column_size_checker << " is not valid!" << endl;
		}
		cin.sync();
		cout << "Enter the number of columns: " ;
		cin >> column_size_checker;
	}
}

void StartingPointChecker(int & startpoint_x, int & startpoint_y, const int & rowsize, const int & columnsize)
{
	cout << "Enter the starting point: ";
	cin >> startpoint_x >> startpoint_y;
	bool checking_inputs = true;
	while(checking_inputs)
	{
		if(cin.fail())					// I am clearing the cin stream if input is not an integer
		{
			cin.clear();
			cin.sync();
			cout << "Invalid coordinate!" << endl
				<< "Enter the starting point: ";
			cin >> startpoint_x >> startpoint_y;
		}
		else if((startpoint_x >= rowsize || startpoint_x < 0) || (startpoint_y >= columnsize || startpoint_y < 0))
		{
			cout << "Invalid coordinate!" << endl
				<< "Enter the starting point: ";
			cin >> startpoint_x >> startpoint_y;
		}
		else
		{
			checking_inputs = false;
		}
	
	}
}

// I took the main concept of the function from   >>>> 2.2-pointers-linkedlists file slide 28 <<<<<<

void deletion_of_dynamic_matrix( char ** & Matrix, const int & rows, const int & columns)
{
	for(int i = 0; i < rows; i++)
	{
		delete [] Matrix[i];
		// In order to delete the columns since we need to return used memory back to the heap 
	}
	delete [] Matrix;
	// In order to delete the rows since we need to return used memory back to the heap 
}


void ParsingOperation(char ** & Matrix, ifstream & input_file)
{
	char character_of_input;
	
	int i = 0, j = 0;
	while(input_file.get(character_of_input))
	{
		if(character_of_input == '\n')			// I am getting to a new line so I should increase x coordinate and set y_coordinate to zero
		{
			i++;
			j = 0;
		}
		else
		{
			Matrix[i][j] = character_of_input;
			j++;
		}
	}
	input_file.clear();
	input_file.seekg(0);
}

void Printing_function(char ** & Matrix, const int & rowsize, const int & columnsize)
{
	for(int i = 0; i < rowsize ; i++)
	{
		for(int j = 0; j < columnsize ; j++)
		{
			cout << Matrix[i][j];
		}
		cout << endl;
	}
}

void Area_Filling_Function(DynamicIntStack & DynamicStack, char ** & Matrix, const char & character, const int & start_point_x, const int & start_point_y);

void character_checker(char & character)
{
	bool checker = true;
	while(checker)
	{
		cout << "Enter the filling char: " ;
		cin >> character;
		
		if(character == 'X' || character == 'x')		// I am checking the character whether it is eligible or not
		{
			cout << "Filling char is not valid!" << endl;
		}
		else
		{
			checker = false;
		}

	}

}

int main()
{
	int row_size, column_size;	
	int startpoint_x, startpoint_y;

	matrix_size_checker(row_size, column_size);  
	// I am checking the size of matrix with wanted prerequisites that are stated in homework file

	string Filename;
	ifstream input_opener_for_matrixfile;

	// I am trying to get a correct filename from the use so that I can proceed in my program
	do
	{
		cout << "Please enter file name: " ;
		cin >> Filename;
		input_opener_for_matrixfile.open(Filename);
		if(input_opener_for_matrixfile.fail())
		{
			cout << "Cannot open a file named " << Filename << endl;
		}

	}while(input_opener_for_matrixfile.fail());
	

	// Now we are creating a dynamic char matrix so that we can extract txt file for usage in filling program phase

	char ** Matrix_for_Map = new char * [row_size];
	for( int i = 0 ; i < row_size ; i++)
	{
		Matrix_for_Map[i] = new char[column_size];
	}

	ParsingOperation(Matrix_for_Map, input_opener_for_matrixfile);
	// I am parsing the file by get function so that I am filling the dynamic matrix
	
	StartingPointChecker(startpoint_x, startpoint_y, row_size, column_size);
	// I am getting starting point input but before proceeding I am trying to get a correct with specified boundaries by Homework pdf
	
	if(Matrix_for_Map[startpoint_x][startpoint_y] == 'X' || Matrix_for_Map[startpoint_x][startpoint_y] == 'x')
	{
		cout << "Starting point is already occupied." << endl
			<< "Terminating..." << endl;
	}
	else
	{
		char filling_character;
		character_checker(filling_character);
		DynamicIntStack StackforFilling;     // I am initializing a stack variable 

		Area_Filling_Function(StackforFilling, Matrix_for_Map,filling_character, startpoint_x, startpoint_y);
		// I am filling the area finded by the algorithm
		
		Printing_function(Matrix_for_Map, row_size, column_size);
		// I am printing the newly changed matrix so that we can see the  wanted changes given by the user

		StackforFilling.~DynamicIntStack();
		// I am calling the destructor to free the allocated memory for the heap
	}

	deletion_of_dynamic_matrix(Matrix_for_Map, row_size, column_size);
	// I am deleting the dynamic matrix so that allocated memory is turned back to the heap

	return 0;
}

void Area_Filling_Function(DynamicIntStack & dynamicStack, char ** & Matrix, const char & character, const int & start_point_x, const int & start_point_y)
{
	int x_coordinate = start_point_x, y_coordinate = start_point_y;
	
	bool empty_in_area = true;			// Important variable to have a correct while loop for filling the empty coordinates
	while(empty_in_area)
	{
		Matrix[x_coordinate][y_coordinate] = character;
		if(Matrix[x_coordinate][y_coordinate + 1] == ' ') // For going right
		{
			dynamicStack.push(x_coordinate, y_coordinate);
			Matrix[x_coordinate][y_coordinate + 1] = character;
			y_coordinate++;
		}
		else if(Matrix[x_coordinate + 1][y_coordinate] == ' ') // For going down
		{
			dynamicStack.push(x_coordinate, y_coordinate);
			Matrix[x_coordinate + 1][y_coordinate] = character;
			x_coordinate++;
		}	
		else if(Matrix[x_coordinate][y_coordinate - 1] == ' ') // For going left
		{
			dynamicStack.push(x_coordinate, y_coordinate);
			Matrix[x_coordinate][y_coordinate - 1] = character;
			y_coordinate--;
		}
		else if(Matrix[x_coordinate - 1][y_coordinate] == ' ') // for going up
		{
			dynamicStack.push(x_coordinate, y_coordinate);
			Matrix[x_coordinate - 1][y_coordinate] = character;
			x_coordinate--;
		}
		else if(Matrix[x_coordinate][y_coordinate + 1] != ' ' && Matrix[x_coordinate +1][y_coordinate] != ' '
			&& Matrix[x_coordinate][y_coordinate - 1] != ' ' && Matrix[x_coordinate - 1][y_coordinate] != ' ' && !dynamicStack.isStackEmpty())
		{
				// Stack is important to backtrack the cells to find empty cells in area if there is left any

				dynamicStack.pop(x_coordinate, y_coordinate);
		}
		else 
		{
			empty_in_area = false;

			// It means no more empty place in the specific area so function is going to finish
		}

	}
}

// End of Homework 4
// Yours sincerely
// ilker
