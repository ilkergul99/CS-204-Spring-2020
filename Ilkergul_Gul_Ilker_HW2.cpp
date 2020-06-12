#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/******************************************************************************

Username = ilkergul 
Name, Surname = Ilker Gul
ID Number = 26352
Date = 2/25/2020
CS204 Second Homework
Purpose = Implement a program which stores blacklisted credit cards organized by their expiration dates

******************************************************************************/

struct node
{
	int expiration_month, expiration_year;					// I took this content from homework2 explanation pdf file
	vector<string> Blacklisted_creditCards;                 // It is storing the needed content in our program
	node* next_pointed_list_element;
	
	node::node()
	{
		next_pointed_list_element = NULL;
	}

	node::node(int month, int year)
		:expiration_month(month), expiration_year(year),next_pointed_list_element(NULL)
	{}
	
};


//This functions are the prototypes of functions which are going to be defined and used

void Displaying_List_Function(node * & head);
void Card_Search_Function(node * & head);
void Deletion_of_Wanted_Card_Function(node * & head);
void Sorting_Linked_List_with_Bubble_Sort(node * & head);
void Deleting_the_Whole_Left_Linked_List(node * & head);

bool string_checker(const string & cardnumber);
void Adding_a_Node_to_the_Linked_list(node * & head, const string & creditCards_number, const int & related_expiration_month, const int & related_expiration_year);

int main()
{
	string Txt_filename;						
	ifstream Txtfile_of_creditCards;
	string option_selection;
	node *head;
	head = NULL;
	
	cout << "Please enter file name: " ;
	cin >> Txt_filename;
	Txtfile_of_creditCards.open(Txt_filename);

	// While we can not open txt file it will ask the user to enter the file name again

	while (Txtfile_of_creditCards.fail())			
	{  
		cout << "Cannot find a file named " << Txt_filename << endl;
		Txtfile_of_creditCards.clear();
		cout << "Please enter file name: " ;
		cin >> Txt_filename;
		Txtfile_of_creditCards.open(Txt_filename);
	}
	
	string txt_line_checker; 
	string creditCards_number;
	int related_expiration_month;
	int related_expiration_year;

	// This while function is to read the elements in the txt file one by one 
	// by using parsing technique with using istringstream
	// and to create the nodes if there is a related content which is going to be stored

	while(getline(Txtfile_of_creditCards, txt_line_checker))
	{
		istringstream line_parser_operator(txt_line_checker);
		line_parser_operator >> creditCards_number >> related_expiration_month >> related_expiration_year;
		Adding_a_Node_to_the_Linked_list(head, creditCards_number, related_expiration_month, related_expiration_year);
		
	}	

	if(head != NULL)
	{
		Sorting_Linked_List_with_Bubble_Sort(head);
	}
	
	
	cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date" << endl
		<< "4)Exit" << endl << endl;

	cout << "Please choose option from the menu: ";
	cin >> option_selection;

	// This loop is to get options done unless the input is not equal to 4

	while( option_selection != "4")
	{
		if(option_selection == "1")
		{
			Displaying_List_Function(head);
		}
		else if( option_selection == "2")
		{
			Card_Search_Function(head);
		}
		else if(option_selection == "3")
		{
			Deletion_of_Wanted_Card_Function(head);
		}
		else
		{
			cout << "Invalid option choice !!! Please try again." << endl << endl;		
		}
		
		cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date" << endl
		<< "4)Exit" << endl << endl;
		cout << "Please choose option from the menu: ";
		cin >> option_selection;
		
	}
	Deleting_the_Whole_Left_Linked_List(head);
	cout << "Terminating!!!" << endl;
	

	
	return 0;
}

// This below function will add new nodes to our linked list if it necessary
// if there is an already existed linked list element then
// it will add its credit card number to the already existed linked lists members vector by using push back
// the below function will cover different cases
// to add the first linked list element to the linked list
// check the elements of the linked lists and find the existed elements with the same expiration date in accordance with the respested parameters
// add new linked list elements if it not existed in the list

void Adding_a_Node_to_the_Linked_list(node * & head, const string & creditCards_number, const int & related_expiration_month, const int & related_expiration_year)
{
	node *ptr;
	if(head == NULL)
	{		
		ptr = new node(related_expiration_month, related_expiration_year);
		ptr->Blacklisted_creditCards.push_back(creditCards_number);
		
		cout <<"New node is created with expiration date: " << related_expiration_month << " " << related_expiration_year 
			<< endl << "Credit card " << creditCards_number << " added to node " << ptr->expiration_month << " " << ptr->expiration_year 
			<< endl << "***************" << endl;
		head = ptr;
	}
	else
	{
		ptr = head;
		bool added_or_not = false;
		while(ptr->next_pointed_list_element != NULL)
		{
			if(ptr->expiration_month == related_expiration_month && ptr->expiration_year == related_expiration_year)
			{
				ptr->Blacklisted_creditCards.push_back(creditCards_number);
				
				cout << "Node with expiration date " << related_expiration_month << " " << related_expiration_year 
					<< " already exists" << endl << "Credit card " << creditCards_number << " added to node " << ptr->expiration_month
					<< " " << ptr->expiration_year << endl << "***************" << endl;

				added_or_not = true;
				break;
			}
			ptr= ptr->next_pointed_list_element;
		}
		if(added_or_not == false)
		{
			if(ptr->expiration_month == related_expiration_month && ptr->expiration_year == related_expiration_year)
			{
				ptr->Blacklisted_creditCards.push_back(creditCards_number);
				
				cout << "Node with expiration date " << related_expiration_month << " " << related_expiration_year 
					<< " already exists" << endl << "Credit card " << creditCards_number << " added to node " << ptr->expiration_month
					<< " " << ptr->expiration_year << endl << "***************" << endl;
			}
			else
			{
				node * next;
				next = new node(related_expiration_month, related_expiration_year);
				next->Blacklisted_creditCards.push_back(creditCards_number);

				cout <<"New node is created with expiration date: " << related_expiration_month << " " << related_expiration_year 
					<< endl << "Credit card " << creditCards_number << " added to node " << next->expiration_month << " " << next->expiration_year 
					<< endl << "***************" << endl;
				ptr->next_pointed_list_element = next;
			}
			
		}
	}
	
}

// I used bubble sort technique in our linked list
// I am swapping the elements of node struct if it is not in the wanted order
// It is helping me to use number one option which is to display

void Sorting_Linked_List_with_Bubble_Sort(node * & head)
{
	node * ptr1;
	node * ptr2;
	
	ptr1 = head;
	ptr2 = head->next_pointed_list_element;
	
	while(ptr1 != NULL)
	{
		ptr2 = ptr1->next_pointed_list_element;

		while(ptr2 != NULL)
		{
			
			if(ptr1->expiration_year > ptr2->expiration_year)
			{
				swap(ptr1->expiration_year, ptr2->expiration_year);
				swap(ptr1->expiration_month, ptr2->expiration_month);
				swap(ptr1->Blacklisted_creditCards, ptr2->Blacklisted_creditCards);
			}
			else if(ptr1->expiration_year == ptr2->expiration_year)
			{
				if(ptr1->expiration_month > ptr2->expiration_month)
				{
					swap(ptr1->expiration_year, ptr2->expiration_year);
					swap(ptr1->expiration_month, ptr2->expiration_month);
					swap(ptr1->Blacklisted_creditCards, ptr2->Blacklisted_creditCards);
				}
			}
			ptr2 = ptr2->next_pointed_list_element;
		}		
		ptr1 = ptr1->next_pointed_list_element;
		
	}
}

// This function is to display the wanted elements in our linked list
// it will use head as a reference parameter and will check the linked list content by
// by using another pointer and travelling every element if it exists
// if it does not it will display as the list is empty
// It will also display the content of the deleted linked list element

void Displaying_List_Function(node * & head)
{
	if(head == NULL)
	{
		cout << "List is empty!" << endl << endl;
	}
	else
	{
		node *ptr;
		ptr = head;
		while(ptr != NULL)
		{
			cout << "Expiration Date: " << ptr->expiration_month << " " << ptr->expiration_year << endl;
			for(int k = 0; k < ptr->Blacklisted_creditCards.size(); k++)
			{
				cout << k+1 << ")  " << ptr->Blacklisted_creditCards[k] << endl;
			}
			cout << "------------------------------" << endl << endl;
			ptr = ptr->next_pointed_list_element;
		}
	}		
}

// This below function will delete a linked list element if it exists and
// will connect previous and next members of the going to be deleted element in linked lists
// if it is necessary

void Deletion_of_Wanted_Card_Function(node * & head)
{
	int year, month;
	cout << "Please enter month and year: " ;
	cin >> month >> year;
	bool checking_inputs = true;

	// This while loop will check the inputs and if it is invalid
	// will ask the user again to give valid inputs

	while(checking_inputs)
	{
		if(cin.fail())
		{
			cout << "Invalid Date!" << endl;
			cin.clear();
			cin.sync();
			cout << "Please enter month and year: " ;
			cin >> month >> year;
		}
		else if(month <= 0 || month > 12 )
		{
			cout << "Invalid Date!" << endl;
			cout << "Please enter month and year: " ;
			cin >> month >> year;
		}
		else
		{
			checking_inputs = false;
		}
	}
	
	if(head == NULL)
	{
		cout << "There is no node with expiration date " << month << " " << year << endl << endl;
	}
	else
	{
		if(month == head->expiration_month && year == head->expiration_year)
		{
			node * temp;
			temp = head;
			head = head->next_pointed_list_element;
			cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
			for(int k = 0; k < temp->Blacklisted_creditCards.size(); k++)
			{
				cout << k+1 << ")  " << temp->Blacklisted_creditCards[k] << endl;
			}
			cout << endl;
			delete temp;
		}
		else
		{
			node * prev;
			prev = head;

			// This while loop is important to check the elements of the linked list in accordance with the given inputs

			while(prev->next_pointed_list_element != NULL && (prev->next_pointed_list_element->expiration_month != month || prev->next_pointed_list_element->expiration_year != year))
			{
				prev= prev->next_pointed_list_element;
			}
		
			// This below if loop will delete the given input node from the linked list if it existed in the list

			if(prev->next_pointed_list_element != NULL && prev->next_pointed_list_element->expiration_month == month
				&& prev->next_pointed_list_element->expiration_year == year)
			{
				node * temp;
				temp = prev->next_pointed_list_element;
				prev->next_pointed_list_element = prev->next_pointed_list_element->next_pointed_list_element;
			
				cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
				for(int k = 0; k < temp->Blacklisted_creditCards.size(); k++)
				{
					cout << k+1 << ")  " << temp->Blacklisted_creditCards[k] << endl;
				}
				cout << endl;
				delete temp;
			}
			else
			{
				cout << "There is no node with expiration date " << month << " " << year << endl << endl;
			}
		
		}
	}
}

bool string_checker(const string & cardnumber)				// This function is to return true or false about the content of taken string
{                                                           // if string characters are different than digits or the length of the string 
	if(cardnumber.length() == 16)                           // is less than 16 than it will return false
	{
		for(int i = 0; i < cardnumber.length(); i++)
		{
			if(cardnumber.at(i) < 48 || cardnumber.at(i) > 57)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

// In Card_Search_Function we are checking whether the given credit card number is valid or not
// then, we are checking whether it is existed in our linked list by checking every element in the list

void Card_Search_Function(node * & head)
{
	
	string card_number_will_be_searched;
	cout << "Please enter the credit card number: ";
	cin >> card_number_will_be_searched;
	while(string_checker(card_number_will_be_searched) != true)
	{
		cout << "Invalid format!" << endl;
		cout << "Please enter the credit card number: " ;
		cin >> card_number_will_be_searched;
	}
	if(head == NULL)
	{
		cout << "There is no credit card with given credit card number: " << endl
			<< card_number_will_be_searched << endl << endl;
	}
	else
	{
		node * ptr;
		ptr = head;
		bool finding_card_number = false;

		// This while loop is checking whether the given number is in the linked list or not

		while(ptr != NULL)
		{
			for(int i = 0; i < ptr->Blacklisted_creditCards.size(); i++)
			{
				if(ptr->Blacklisted_creditCards[i] == card_number_will_be_searched)
				{
					cout << "There exists a credit card given number " << card_number_will_be_searched
						<< " with expiration date: " << ptr->expiration_month << " " << ptr->expiration_year << endl << endl;
					finding_card_number = true;
					break;
				}
			}
			if(finding_card_number)
			{
				break;
			}
			else
			{
				ptr = ptr->next_pointed_list_element;		
			}
			
		}
		if(finding_card_number == false)
		{
			cout << "There is no credit card with given credit card number: " << endl
			<< card_number_will_be_searched << endl << endl;
		}
	}
}

// This below function is to prevent memory leak in the program before terminating it
// it is deleting the elements by recursive approach
// Furthermore, its content can be also seen in lecture notes

void Deleting_the_Whole_Left_Linked_List(node * & head)
{
	if(head != NULL)
	{
		Deleting_the_Whole_Left_Linked_List(head->next_pointed_list_element);
		delete head;
	}
}

// End of Homework 2
// Yours sincerely
// ilker gul