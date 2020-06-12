#include <iostream>
#include "CardListClass.h"

using namespace std;

CardList ::CardList()
{
	head = NULL;
	tail = NULL;
}

//default constructor that creates an empty list 

void CardList::insertCard (string & creditCardNo, int & month, int & year)
{
	if(head == NULL)						// for empty list creation
	{
		head = new expirationNode(month, year);
		head->creditcardHead = new creditCardNode(creditCardNo);
		cout << creditCardNo << " " << month << " " << year <<": added to a new expiration date node"<< endl;
		tail = head;
	}

	else if((year <= head->year && month < head->month)|| year < head->year) 		//adding a new node to the beginning
	{
		head = new expirationNode(month, year, head);
		head->creditcardHead = new creditCardNode(creditCardNo);
		if(head->next != NULL)
		{
			head->next->prev = head;
		}
		cout << creditCardNo << " " << month << " " << year <<": added to a new expiration date node"<< endl;
	}

	else
	{
		expirationNode * ptr;
		ptr = head;

		while(year > ptr->year && ptr != tail)
		{
			ptr = ptr->next;
		}
		while(year == ptr->year && month > ptr->month && ptr != tail)
		{
			ptr = ptr->next;
		}

		if((year > ptr->year || (month > ptr->month && year >= ptr->year)) && ptr->next == NULL)				// to the end of the list
		{
			ptr->next = new expirationNode(month,year);
			ptr->next->creditcardHead = new creditCardNode(creditCardNo);
			cout << creditCardNo << " " << month << " " << year <<": added to a new expiration date node"<< endl;
			ptr->next->prev = ptr;
			tail = ptr->next;
		}
		else if(year == ptr->year && month == ptr->month )				// any same expiration node
		{

			if(creditCardNo < ptr->creditcardHead->creditCardNo)
			{
				ptr->creditcardHead = new creditCardNode(creditCardNo,ptr->creditcardHead);  // added to the beginning
				cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
			}
			else
			{
				creditCardNode * card_searcher = ptr->creditcardHead;
				bool already_existed = false;
				while(card_searcher != NULL && already_existed == false)
				{
					if(creditCardNo == card_searcher->creditCardNo)
					{
						cout << creditCardNo << " " << month << " " << year <<": this card was already inserted" << endl;
						already_existed = true;
					}
					else
					{
						if(card_searcher->next	== NULL && creditCardNo > card_searcher->creditCardNo)
						{
							card_searcher->next = new creditCardNode(creditCardNo);	
							// to the end of the list
							cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
							already_existed = true;
						}
						else if(creditCardNo > card_searcher->creditCardNo && card_searcher->next != NULL &&
							creditCardNo < card_searcher->next->creditCardNo)
						{
							creditCardNode * temp = new creditCardNode(creditCardNo,card_searcher->next);
							cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
							card_searcher->next = temp;
							already_existed = true;
						} 
					}
					card_searcher = card_searcher->next;
				}
			}

		}
		else
		{
			if(ptr->prev != NULL && (year < ptr->year || (month < ptr->month && year == ptr->year)))					//adding between nodes															
			{
				expirationNode * temp = new expirationNode(month, year, ptr, ptr->prev);
				temp->creditcardHead = new creditCardNode(creditCardNo);
				cout << creditCardNo << " " << month << " " << year <<": added to a new expiration date node"<< endl;
				ptr->prev->next = temp;
				temp->next->prev = temp;
			}
		}


	}
} 

//inserts a new card to the structure in sorted fashion 

void CardList::displayListChronological()
{
	if(head == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		expirationNode * chronological_pointer;
		chronological_pointer = head;
		while(chronological_pointer != NULL)
		{
			cout << "Expiration Date: " << chronological_pointer->month << "  "<< chronological_pointer->year << endl;
			creditCardNode * credit_pointer;
			credit_pointer = chronological_pointer->creditcardHead;
			int count = 1;
			while(credit_pointer != NULL)
			{
				cout << count << ") " << credit_pointer->creditCardNo << endl;
				count++;
				credit_pointer = credit_pointer->next;
			}
			cout << "-------------------" << endl;
			chronological_pointer = chronological_pointer->next;
		}
	}
}

//displays entire structure in chronological order 

void CardList::displayListReverseChronological()
{
	if(tail == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		expirationNode * reverse_chronological_pointer;
		reverse_chronological_pointer = tail;
		while(reverse_chronological_pointer != NULL)
		{
			cout << "Expiration Date: " << reverse_chronological_pointer->month << "  "<< reverse_chronological_pointer->year << endl;
			creditCardNode * credit_card_pointer;
			credit_card_pointer = reverse_chronological_pointer->creditcardHead;
			int count = 1;
			while(credit_card_pointer != NULL)
			{
				cout << count << ") " << credit_card_pointer->creditCardNo << endl;
				count++;
				credit_card_pointer = credit_card_pointer->next;
			}
			cout << "-------------------" << endl;
			reverse_chronological_pointer = reverse_chronological_pointer->prev;
		}
	}
}


//displays entire structure in reverse chronological order 

void CardList::cardSearch (string creditCardNo)
{
	if(head == NULL)
	{
		cout << "There is no credit card with given credit card number: " 
			<< creditCardNo << endl;
	}
	else
	{
		expirationNode * search_pointer = head;
		bool founded_any = false;
		while(search_pointer != NULL)
		{
			creditCardNode * credit_ptr = search_pointer->creditcardHead;
			bool card_founded = true;
			while(credit_ptr != NULL && card_founded)
			{
				if(creditCardNo == credit_ptr->creditCardNo)
				{
					cout << "There exists a credit card given number " << creditCardNo << " with expiration date:" 
						<< endl << search_pointer->month << "  " << search_pointer->year << endl;

					founded_any = true;
					card_founded = false;
				}
				else
				{
					credit_ptr = credit_ptr->next;
				}	
			}
			search_pointer = search_pointer->next;
		}
		if(founded_any == false)
		{
			cout << "There is no credit card with given credit card number: " 
				<< creditCardNo << endl ;
		}
	}
}

//displays all of the occurrences of the given card number 

void CardList::bulkDelete (int month, int year)
{
	expirationNode * deleter_ptr;
	deleter_ptr = head;


	while(head != NULL && year > head->year)
	{
		cout << "Node with expiration date " << head->month << " " << head->year << " the following credit cards have been deleted!" << endl;
		creditCardNode * deletion_pointer2;
		int count = 1;
		while(head->creditcardHead != NULL)
		{
			cout << count << ") " << head->creditcardHead->creditCardNo << endl;
			count++;
			deletion_pointer2 = head->creditcardHead->next;
			delete head->creditcardHead;
			head->creditcardHead = deletion_pointer2;
		}
		if(head->next != NULL)
		{
			deleter_ptr = head->next;
			deleter_ptr->prev = NULL;
			delete head;
			head = deleter_ptr;
			
		}
		else
		{
			deleter_ptr = head->next;				//key point of the bulk delete
			delete head;
			head = deleter_ptr;
			tail = head;
			
		}
		
		
	}
	while(head != NULL && year == head->year && month >= head->month )
	{
		cout << "Node with expiration date " << head->month << " " << head->year << " the following credit cards have been deleted!" << endl;
		creditCardNode * deletion_pointer2;
		int count = 1;
		while(head->creditcardHead != NULL)
		{
			cout << count << ") " << head->creditcardHead->creditCardNo << endl;
			count++;
			deletion_pointer2 = head->creditcardHead->next;
			delete head->creditcardHead;
			head->creditcardHead = deletion_pointer2;
		}
		if(head->next != NULL)
		{
			deleter_ptr = head->next;
			deleter_ptr->prev = NULL;
			delete head;
			head = deleter_ptr;
		}
		else
		{
			deleter_ptr = head->next;					//key point of the bulk delete
			delete head;
			head = deleter_ptr;
			tail = head;
		}
		

	}
	
	
}

//deletes all nodes up to and including given expiration date 

void CardList::deleteAll()
{
	expirationNode * pointer;
	
	while(head != NULL)
	{
		creditCardNode * pointer2;
		while(head->creditcardHead != NULL)
		{
			pointer2 = head->creditcardHead->next;
			delete head->creditcardHead;
			head->creditcardHead = pointer2;
		}
		pointer = head->next;
		
		delete head;
		head = pointer;
		
		
	}
	if(head == NULL)
	{
		tail = head;
	}
	

}

//deletes the entire structure