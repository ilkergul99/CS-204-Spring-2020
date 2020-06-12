#ifndef Ilkergul_Gul_Ilker_hw5_IntegerSet_h
#define Ilkergul_Gul_Ilker_hw5_IntegerSet_h

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class IntegerSet
{
	private:
		int * number_of_elements;
		int size;

	public:
		IntegerSet();
		IntegerSet(const int & input);
		IntegerSet(const IntegerSet & copy);  //Deep copy constructor
		int * createClone() const;
		~IntegerSet();						 // Destructor

		const IntegerSet & IntegerSet::operator = (const IntegerSet & rhs); //assigment operator overloading
		const IntegerSet & IntegerSet::operator += (const IntegerSet & second_set); // plus and assignment operator
		IntegerSet IntegerSet::operator *(const IntegerSet & rhs); // intersection operator with overloading product operator
		
		bool Set_Equality_Checker(const IntegerSet & rhs) const;
		bool In_or_not_checker(const int & rhs) const;
		bool In_or_not_checker(const IntegerSet & rhs) const;
		string Printing() const;
		void Takeinputs(const int & integer_to_be_added);

						

};

	ostream & operator <<(ostream & os, const IntegerSet & integerset);    //free function due to lhs type
	IntegerSet operator +(const IntegerSet & lhs, const IntegerSet & rhs);  
	// it can be also member function but I have chosen this one to be free
	IntegerSet operator +(const IntegerSet & lhs, const int & integer_to_be_added); // free function with diffrent two parameters
	
	bool operator == (const IntegerSet & lhs, const IntegerSet & rhs);
	bool operator != (const IntegerSet & lhs, const IntegerSet & rhs);
	bool operator <= (const int & lhs, const IntegerSet & rhs);
	bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs);


#endif
