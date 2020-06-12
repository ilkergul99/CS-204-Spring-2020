#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "CardListClass.h"


using namespace std;

/******************************************************************************

Username = ilkergul 
Name, Surname = Ilker Gul
ID Number = 26352
Date = 03/09/2020
CS204 Third Homework
Purpose = Implement a program that stores blacklisted credit cards organized according to their expiration dates.
Use a hybrid data structure that contains both Doubly Linked List and Singly Linked Lists

******************************************************************************/

void Uploading_Cards(CardList & mylist )
{
	string filename;
	ifstream input_opener;
	cout << "Please enter a filename: " ;
	cin >> filename;
	input_opener.open(filename);									// structure of the function can be similar to 
	if(input_opener.fail())											// one of my second homework function
	{  
		cout << "Could not find a file named " << filename << endl;
		input_opener.clear();	
		
	}
	else
	{
		string file_line_checker;
		string Number_of_creditCards;
		int expiration_month;
		int expiration_year;

		while(getline(input_opener, file_line_checker))
		{
			istringstream parsing_operator(file_line_checker);
			parsing_operator >> Number_of_creditCards >> expiration_month >> expiration_year;
			mylist.insertCard(Number_of_creditCards, expiration_month, expiration_year);
		}
		input_opener.clear();
		input_opener.seekg(0);
		
		
	}
	

}

bool string_format_checker(const string & cardnumber)
{
	if(cardnumber.length() == 16)                           // is less than 16 than it will return false
	{
		for(int i = 0; i < cardnumber.length(); i++)
		{
			if(cardnumber.at(i) < 48 || cardnumber.at(i) > 57)
			{
				return false;
			}
		}								// I have taken this from my second homework
		return true;
	}
	else
	{
		return false;
	}
}



int main()
{
	string option_selection;
	CardList my_hybrid_list;

	cout << "1) Upload Card(s) from a File" << endl 
		<< "2) Display List Chronological" << endl 
		<< "3) Display List Reverse Chronological" << endl
		<< "4) Card Search" << endl
		<< "5) Bulk Delete" << endl
		<< "6) Exit" << endl
		<< "Please choose option from the menu: ";
	cin >> option_selection;
	while(option_selection != "6")
	{
		if(option_selection != "1" && option_selection != "2" && option_selection != "3"
			&& option_selection != "4" && option_selection != "5" )
		{
			cout << "Invalid operation!" << endl ;
			cout << endl << "1) Upload Card(s) from a File" << endl 
				<< "2) Display List Chronological" << endl 
				<< "3) Display List Reverse Chronological" << endl
				<< "4) Card Search" << endl
				<< "5) Bulk Delete" << endl
				<< "6) Exit" << endl
				<< "Please choose option from the menu: ";
			cin >> option_selection;
		}
		else
		{
			if(option_selection == "1")
			{
				Uploading_Cards(my_hybrid_list);
			}
			else if(option_selection == "2")
			{
				my_hybrid_list.displayListChronological();
			}
			else if(option_selection == "3")
			{
				my_hybrid_list.displayListReverseChronological();
			}
			else if(option_selection == "4")
			{
				string creditcardno;
				cout << "Please enter the credit card number: ";
				cin >> creditcardno;
				if(string_format_checker(creditcardno))
				{
					my_hybrid_list.cardSearch(creditcardno);
				}
				else
				{
					cout << "Invalid format!" << endl;
				}
			}
			else if(option_selection == "5")
			{
				int month, year;
				cout << "Please enter month and year: " ;
				cin >> month >> year;

				if(cin.fail())
				{
					cout << "Invalid format!" << endl;
					cin.clear();
					cin.sync();
				}
				else if(month <= 0 || month > 12 )
				{
					cout << "Invalid format!" << endl;
				}
				else
				{
					my_hybrid_list.bulkDelete(month,year);
				}
			}
			cout << endl << "1) Upload Card(s) from a File" << endl				// For choosing options
				<< "2) Display List Chronological" << endl 
				<< "3) Display List Reverse Chronological" << endl
				<< "4) Card Search" << endl
				<< "5) Bulk Delete" << endl
				<< "6) Exit" << endl
				<< "Please choose option from the menu: ";
			cin >> option_selection;
			
		}
	}

	my_hybrid_list.deleteAll();
	cout <<"All the nodes have been deleted!" << endl 
		<< "Terminating!!!" << endl;

	return 0;
}
// End of of Homework 3
// Yours sincerely
// ilker gul