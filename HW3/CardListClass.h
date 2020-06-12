#ifndef _CardListClass
#define _CardListClass

#include <iostream>
#include <string>

using namespace std;

struct creditCardNode 
{ 
	string creditCardNo; 
	creditCardNode * next;

// constructors come here 

	creditCardNode::creditCardNode()
	{
		next = NULL;
	}

	creditCardNode::creditCardNode(const string & creditcard)
		:creditCardNo(creditcard), next(NULL)
	{}
	creditCardNode::creditCardNode(const string & creditcard, creditCardNode * next)
		:creditCardNo(creditcard), next(next)
	{}
};

struct expirationNode
{ 
	int month, year;
	creditCardNode * creditcardHead; 
	expirationNode * next;
	expirationNode * prev;

// constructors come here 
	expirationNode::expirationNode()
	{
		month = 0;
		year = 0;
		creditcardHead = NULL;
		next = NULL;
		prev = NULL;
	}
	expirationNode::expirationNode(const int & month, const int & year)				//just int and month entry for beginning
		:month(month), year(year), next(NULL), prev(NULL), creditcardHead(NULL)
	{}

	expirationNode::expirationNode(const int & month, const int & year, expirationNode* next)  
		:month(month), year(year), next(next), prev(NULL), creditcardHead(NULL)
	{}
	expirationNode::expirationNode(const int & month, const int & year, expirationNode* next ,expirationNode* prev)  
		:month(month), year(year), next(next), prev(prev), creditcardHead(NULL)
	{}


};

class CardList							// I have taken this from hw3 pdf file
{ 
	public: 
		CardList(); 

		//default constructor that creates an empty list 
		
		void insertCard (string & creditCardNo, int & month, int & year); 

		//inserts a new card to the structure in sorted fashion 
		
		void displayListChronological (); 

		//displays entire structure in chronological order 

		void displayListReverseChronological ();

		//displays entire structure in reverse chronological order 

		void cardSearch (string creditCardNo); 

		//displays all of the occurrences of the given card number 

		void bulkDelete (int month, int year); 

		//deletes all nodes up to and including given expiration date 

		void deleteAll ();

		//deletes the entire structure 

	private: 
		expirationNode * head; 
		expirationNode * tail;

		// any helper functions you see necessary
};

#endif
