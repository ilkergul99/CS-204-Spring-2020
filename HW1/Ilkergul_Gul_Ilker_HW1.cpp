#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/******************************************************************************


CS204 First Homework
Purpose = This program is to determine an enclosed space in a 2D matrix containing the "x" and "o" elements
and to display appropriate messages related to the content

******************************************************************************/


void Enclosed_area_finder(vector<vector<char>> & Matrix, const int & initial_X_coordinate, const int & initial_Y_coordinate);
// In order to determine whether we have an enclosed area or not for the given input if it only contains
// Aforementioned characters in line 14 and detailed rules given in the homework file

bool matrix_creator(vector<vector<char>> & Matrix, ifstream & given_resource, const string & filename);
// We are going to define this function in order to use txt files' characters for our program
// It will help us to store the characters that are included in the txt files to a 2D-char matrix

void Enclosed_area_coordinate_checker(vector<vector<char>> & Matrix, int & X_coordinate, int & Y_coordinate);
// When the necessary conditions specified in the homework details are covered
// We are going to use this function to have start point in our program to find whether there is an enclosed area or not

void General_Print_function(vector<vector<int>> & occurrence_checker, bool & enclosed_or_not, const int & initial_X_coordinate, const int & initial_Y_coordinate);
// In order to print whether it is an enclosed area or not and to display the coordinates of the followed path
// by the program we are going to use this function

void Pathway_Print_function(vector<vector<int>> & occurrence_checker, const int & initial_X_coordinate, const int & initial_Y_coordinate);
// to display the coordinates of the followed path we are going to call this function
// in General_Print_function to make the program more modular

int main()
{
	string fileNameOfTextFile;						
	// In order to keep the given input name we are going to use this variable

	ifstream file_Of_Wanted_Matrix;					
	// This variable is to use necessary input files for the program

	vector<vector<char>> matrix_Gonna_Be_Used;		
	// This matrix variable is to keep the 'x' and 'o' for the program in a 2D matrix from input 

	int X_coordinate, Y_coordinate;					
	// I am going to use these integer variables to keep x and y coordinates and use in functionsas reference parameters

	cout << "Please enter file name: " ;
	cin >> fileNameOfTextFile;
	file_Of_Wanted_Matrix.open(fileNameOfTextFile.c_str());

	// I am checking whether the given input file from the user is opened succesfully or not
	// If it is not successful I will use a while statement to take the name of the file until I have a successully opened file
	while (file_Of_Wanted_Matrix.fail())			
	{                                         
		cout << "Cannot find a file named " << fileNameOfTextFile << endl;
		file_Of_Wanted_Matrix.clear(); 
		cout << "Please enter file name: " ;
		cin >> fileNameOfTextFile;
		file_Of_Wanted_Matrix.open(fileNameOfTextFile.c_str());
	}

	if(matrix_creator(matrix_Gonna_Be_Used, file_Of_Wanted_Matrix, fileNameOfTextFile ))
	{
		int i,k;
		cout << "Input Matrix:" << endl;
		
		//The below process is for printing the 2D Matrix if it contains the prerequisites given in the homework details
		for(i= 0; i < matrix_Gonna_Be_Used.size(); i++)
		{
			for(k= 0; k < matrix_Gonna_Be_Used[0].size(); k++)
			{
				if(k == matrix_Gonna_Be_Used[0].size() -1)
				{
					cout << matrix_Gonna_Be_Used[i][k];
				}
				else
				{
					cout << matrix_Gonna_Be_Used[i][k] << " " ;
				}
			}
			cout << endl;
		}
		// I will use the below function for the process of the rest of the program which will
		// be used in the proceedings of the code by the given parameters
		// which will use other functions inside of it
		// in order to check and process important aspects of the homework
		Enclosed_area_coordinate_checker(matrix_Gonna_Be_Used, X_coordinate, Y_coordinate);			
	}
	return 0;
}

bool matrix_creator(vector<vector<char>> & Matrix, ifstream & given_resource, const string & filename)
{
	string matrix_line;
	char elements_of_the_matrix;


	while (!given_resource.eof())
	{
		getline(given_resource, matrix_line);					// I will check the lines of the input file line by line
		istringstream line_checker(matrix_line);

		vector<char> temporary_vector;
		while(line_checker >> elements_of_the_matrix)
		{
			if(elements_of_the_matrix == 'x' || elements_of_the_matrix == 'o')
			{
				temporary_vector.push_back(elements_of_the_matrix);
			}
			else if(elements_of_the_matrix == ' ' || elements_of_the_matrix == '\n' || elements_of_the_matrix == '\t')
			{
			// If it is a newline or tab or empty space character skip it
			}
			else
			{
				cout << filename << " includes invalid char(" << elements_of_the_matrix << ")" << endl;
				// If there is an invalid character return false since the file is not suitable for our program

				return false;
			}
		}

		// I am going to use below statements in order to check the equality of character number of each row
		if(Matrix.size() == 0)
		{
			Matrix.push_back(temporary_vector);
		}
		else if( temporary_vector.size() == Matrix[0].size())
		{
			Matrix.push_back(temporary_vector);
		}
		else if( temporary_vector.size() != Matrix[0].size())
		{
			cout << filename << " is invalid matrix, does not contain same amount of char each row!" << endl;
			return false;
		}

	}
	given_resource.clear();
	given_resource.seekg(0);
	return true;
}

void Enclosed_area_coordinate_checker(vector<vector<char>> & Matrix, int & X_coordinate, int & Y_coordinate)
{
	cout << "Please enter starting coordinates, first row X then column Y: " ;
	cin >> X_coordinate >> Y_coordinate;
	bool progress_of_looking_coordinates = true;
	while (progress_of_looking_coordinates) 
	{
		if (cin.fail())
		{	
			// I am going to use this if statement in order to get a correct coordinates for the progress of our program
			cout << "Invalid Coordinates" << endl << endl ;
			cin.clear();
			cin.sync();
			cout << "Please enter starting coordinates, first row X then column Y: " ;
			cin >> X_coordinate >> Y_coordinate;
		}

		// If cell is occupied and in the correct range of our 2D matrix, this statement will be used 
		else if (X_coordinate >= 0 && X_coordinate < Matrix.size() && Y_coordinate >= 0 && Y_coordinate < Matrix[0].size() && Matrix[X_coordinate][Y_coordinate] == 'x')
		{
			Enclosed_area_finder(Matrix, X_coordinate, Y_coordinate);
			cout << endl;
			cout << "Please enter starting coordinates, first row X then column Y: " ;
			cin >> X_coordinate >> Y_coordinate;
		}

		// If cell is not occupied and in the correct range of our 2D matrix, it will print the necessary information
		else if(X_coordinate >= 0 && X_coordinate < Matrix.size() && Y_coordinate >= 0 && Y_coordinate < Matrix[0].size() && Matrix[X_coordinate][Y_coordinate] != 'x')
		{
			cout << "This cell is not occupied!" << endl << endl << "Please enter starting coordinates, first row X then column Y: " ;
			cin >> X_coordinate >> Y_coordinate;
		}

		// If user entered -1 -1, then program will be terminated
		else if ( X_coordinate == -1 && Y_coordinate == -1)
		{
			cout << "Terminating..." << endl;
			progress_of_looking_coordinates = false;
		}

		else 
		{
			cout << "Invalid Coordinates" << endl << endl << "Please enter starting coordinates, first row X then column Y: " ;
			cin >> X_coordinate >> Y_coordinate;
		}
	}
	
}	

void Enclosed_area_finder(vector<vector<char>> & Matrix, const int & initial_X_coordinate, const int & initial_Y_coordinate)
{
	int row_coordinate = initial_X_coordinate, column_coordinate = initial_Y_coordinate;
	// These local variables are significant to manipulate the coordinates swiftly for the program
	// It will be used for finding the followed path

	vector<vector<int>>occurrence_checker(Matrix.size(),vector<int>(Matrix[0].size(),0));
	// In initialization since we have not used any coordinates all elements are assigned as zero
	// If we come to a certain coordinates in the followed path, we will change that row and column's value from 0 to 1
	
	bool enclosed_or_not, pathway = true;
	occurrence_checker[row_coordinate][column_coordinate] = 1; // Since it is the initial point we change the value from 0 to 1

	while(pathway)
	{
		// In order to check the right direction
		// I am going to use this statement and change the coordinates accordingly
		if(column_coordinate + 1 < Matrix[0].size() && Matrix[row_coordinate][column_coordinate + 1] == 'x' 
			&& occurrence_checker[row_coordinate][column_coordinate + 1] == 0 )
		{
			column_coordinate++;
			occurrence_checker[row_coordinate][column_coordinate ] = 1;
		}

		// In order to check the down direction
		// I am going to use this statement and change the coordinates accordingly
		else if(row_coordinate + 1 < Matrix.size() && Matrix[row_coordinate + 1][column_coordinate] == 'x' 
			&& occurrence_checker[row_coordinate + 1][column_coordinate ] == 0 )
		{
			row_coordinate++;
			occurrence_checker[row_coordinate ][column_coordinate ] = 1;
		}
		
		// In order to check the left direction
		// I am going to use this statement and change the coordinates accordingly
		else if(column_coordinate - 1 >= 0 && Matrix[row_coordinate][column_coordinate - 1] == 'x' 
			&& occurrence_checker[row_coordinate][column_coordinate - 1] == 0 )
		{
			column_coordinate--;
			occurrence_checker[row_coordinate][column_coordinate ] = 1;
		}

		// In order to check the up direction
		// I am going to use this statement and change the coordinates accordingly
		else if(row_coordinate -1 >= 0 && Matrix[row_coordinate - 1 ][column_coordinate ] == 'x' 
			&& occurrence_checker[row_coordinate - 1][column_coordinate ] == 0 )
		{
			row_coordinate--;
			occurrence_checker[row_coordinate ][column_coordinate ] = 1;
		}
		
		// I am going to check the program by this statement
		// in order to understand whether I have turned back to the initial coordinates or not
		// And I will use the necessary the boolean operation in order to keep the relevant information about enclosement for printing process
		else if((row_coordinate == initial_X_coordinate && column_coordinate + 1 == initial_Y_coordinate) || (row_coordinate == initial_X_coordinate && column_coordinate - 1 == initial_Y_coordinate)
			|| (row_coordinate + 1 == initial_X_coordinate && column_coordinate == initial_Y_coordinate) || (row_coordinate - 1 == initial_X_coordinate && column_coordinate == initial_Y_coordinate))
		{
			enclosed_or_not = true;
			pathway = false;
		}
		
		// If this statement is used, it means the area is not enclosed
		// And I will use the necessary the boolean operation in order to keep the relevant information about enclosement for printing process
		else
		{
			enclosed_or_not = false;
			pathway = false;
		}
	}
	
	// I am calling this user-defined function in order to output the relevant and wanted information
	General_Print_function(occurrence_checker, enclosed_or_not, initial_X_coordinate, initial_Y_coordinate);
}

void General_Print_function(vector<vector<int>> & occurrence_checker, bool & enclosed_or_not, const int & initial_X_coordinate, const int & initial_Y_coordinate)
{
	if(enclosed_or_not)
	{
		cout << "Found an enclosed area. The coordinates of the followed path:" << endl;	
		// This one is to state the enclosed area
	}
	else
	{
		cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path:" << endl;
		// This one is to state the area is not enclosed
	}
	
	// I am going to call the below function in order to print the followed path's coordinates
	Pathway_Print_function(occurrence_checker, initial_X_coordinate, initial_Y_coordinate);

}

void Pathway_Print_function(vector<vector<int>> & occurrence_checker, const int & initial_X_coordinate, const int & initial_Y_coordinate)
{
	int row_output_coordinate = initial_X_coordinate, column_output_coordinate = initial_Y_coordinate;
	bool output_of_the_pathway = true;

	// In this below while loop I will use the same algorithm process for printing the ccordinates therefore
	// the details of the algorithm is given can be found between the lines 203 and 233
	// I just modified that algorithm in order to make it useful in the output process
	while (output_of_the_pathway)
	{
		if(column_output_coordinate + 1 < occurrence_checker[0].size() && occurrence_checker[row_output_coordinate][column_output_coordinate] == 1 
			&& occurrence_checker[row_output_coordinate][column_output_coordinate + 1] == 1 )
		{
			cout << row_output_coordinate << " " << column_output_coordinate << endl;
			occurrence_checker[row_output_coordinate][column_output_coordinate] += 1;
			column_output_coordinate++;
		}
		else if(row_output_coordinate + 1 < occurrence_checker.size() && occurrence_checker[row_output_coordinate][column_output_coordinate] == 1 
			&& occurrence_checker[row_output_coordinate + 1][column_output_coordinate] == 1 )
		{
			cout << row_output_coordinate << " " << column_output_coordinate << endl;
			occurrence_checker[row_output_coordinate][column_output_coordinate] += 1;
			row_output_coordinate++;
		}
		else if(column_output_coordinate - 1 >= 0 && occurrence_checker[row_output_coordinate][column_output_coordinate] == 1 
			&& occurrence_checker[row_output_coordinate][column_output_coordinate - 1] == 1 )
		{
			cout << row_output_coordinate << " " << column_output_coordinate << endl;
			occurrence_checker[row_output_coordinate][column_output_coordinate] += 1;
			column_output_coordinate--;
		}
		else if(row_output_coordinate - 1 >= 0 && occurrence_checker[row_output_coordinate][column_output_coordinate] == 1 
			&& occurrence_checker[row_output_coordinate - 1][column_output_coordinate] == 1 )
		{
			cout << row_output_coordinate << " " << column_output_coordinate << endl;
			occurrence_checker[row_output_coordinate][column_output_coordinate] += 1;
			row_output_coordinate--;
		}
		else
		{
			cout << row_output_coordinate << " " << column_output_coordinate << endl;
			output_of_the_pathway = false;
		}
	}	
}

// End of Homework 1
// Yours sincerely
// Ilker Gul
