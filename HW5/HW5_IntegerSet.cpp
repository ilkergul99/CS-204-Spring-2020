
#include "Ilkergul_Gul_Ilker_HW5_IntegerSet.h"
using namespace std;

/******************************************************************************


Date = 4/12/2020
CS204 Fifth Homework
Purpose = Implement an IntegerSet class without using linkedlist

******************************************************************************/



/* ------------------Member Functions ---------------------------------*/

IntegerSet::IntegerSet()
{
	size = 0;					//Default constructor
	number_of_elements = NULL;
}

IntegerSet::IntegerSet(const int & input)		//Constructor with parameter
{

	if(input >0)
	{                                      
		size = input;
		number_of_elements = new int[size];
		for(int i=0; i < size; i++)
		{
			number_of_elements[i]= i;
		}
	}
	else
	{
		size = 0;
		number_of_elements = NULL;
	}


}

IntegerSet::IntegerSet(const IntegerSet & copy)  //Deep copy constructor
{
	size = copy.size;
	number_of_elements = copy.createClone();

}

int * IntegerSet::createClone() const   //Deep copy constructor clone creator function
{
	if(number_of_elements == NULL)
	{
		return NULL;
	}
	else
	{
		int * clone = new int[size];
		for(int i= 0; i < size ; i++)
		{
			clone[i] = number_of_elements[i];
		}
		return clone;
	}
}


IntegerSet::~IntegerSet()				//Destructor
{
	size = 0;
	delete [] number_of_elements;

}


const IntegerSet & IntegerSet::operator = (const IntegerSet & rhs)  //Assignment operator
{
	if(&rhs != this)
	{
		delete []number_of_elements;
		size = rhs.size;
		number_of_elements = new int[size];
		for(int i = 0; i < size; i++)
		{
			number_of_elements[i] = rhs.number_of_elements[i]; // assign content
		}
	}
	return *this;
}



bool IntegerSet::Set_Equality_Checker(const IntegerSet & rhs) const  //important for boolean operations
{
	if(rhs.size != size)
	{
		return false;
	}
	else 
	{
		for(int i = 0; i < size; i++)
		{
			if(number_of_elements[i] != rhs.number_of_elements[i])
			{
				return false;
			}
		}
		return true;
	}
}





bool IntegerSet::In_or_not_checker(const int & lhs) const   //For subset checking process if lhs is an integer
{
	if(size != 0)
	{
		for(int i = 0; i < size ; i++)
		{
			if(number_of_elements[i] == lhs)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}





bool IntegerSet::In_or_not_checker(const IntegerSet & lhs) const // checking whether lhs is a subset or not
{
	if(lhs.size == 0 && size == 0)
	{
		return true;
	}
	else if(lhs.size > size)
	{
		return false;
	}
	else if(lhs.size <= size)
	{
		int count = 0;
		for(int i = 0 ; i <lhs.size; i++)
		{
			for(int k = 0; k < size ; k++)
			{
				if(number_of_elements[k] == lhs.number_of_elements[i])
				{
					count++;
				}
			}
		}
		if(count == lhs.size)
		{
			return true;
		}
	}
	return false;

}


const IntegerSet & IntegerSet::operator += (const IntegerSet & second_set)  //The crucial operator overloading function of plus assignment
{
	if(second_set.size != 0 )
	{
		int final_size = size;
		int * temp = new int [size + second_set.size];

		for(int i = 0; i < size ; i++)
		{
			temp[i] = number_of_elements[i];
		}
		for(int k = 0; k < second_set.size; k++)
		{
			bool existence = false;
			for(int m = 0; m< size; m++)
			{
				if(second_set.number_of_elements[k] == number_of_elements[m])
				{
					existence = true;
				}
			}
			if(existence == false)
			{
				temp[final_size] = second_set.number_of_elements[k];
				final_size++;
			}
		}
		int * final_array = new int[final_size];
		for(int index = 0; index < final_size; index++)
		{
			final_array[index] = temp[index];
		}
		delete []temp;
		size = final_size;
		number_of_elements = new int[size]; 
		for(int i = 0; i < size; i++)
		{
			number_of_elements[i] = final_array[i];
		}
		delete []final_array;

	}
	return *this;
}

string IntegerSet::Printing() const   //for printing process in ostream 
{
	ostringstream output;
	output << "{";
	for(int i = 0; i < size; i++)
	{
		output << number_of_elements[i];
		if(i != size -1)
		{
			output << ", ";
		}
	}
	output << "}";
	return output.str();

}




void IntegerSet::Takeinputs(const int & integer_to_be_added)
{
	size = 1;
	number_of_elements = new int [size];
	number_of_elements[0] = integer_to_be_added;

}



IntegerSet IntegerSet::operator *(const IntegerSet & rhs)  // to operate intersection in the program
{
	IntegerSet intersection_set;
	if(rhs.size != 0 && size != 0)
	{
		for(int i = 0; i < rhs.size ; i++)
		{
			for(int k = 0; k < size; k++)
			{
				if(number_of_elements[k] == rhs.number_of_elements[i])
				{
					intersection_set = intersection_set + number_of_elements[k];
				}
			}
		}
		return intersection_set;
	}
	else
	{
		return intersection_set;
	}


}
/*-----------------------------Member Functions---------------------------------------------------*/


/*-----------------------------Free Functions---------------------------------------------------*/

ostream & operator <<(ostream & os, const IntegerSet & integerset)  //to print set members
{
	os << integerset.Printing();
	return os;
}

IntegerSet operator +(const IntegerSet & lhs, const IntegerSet & rhs) // adding rhs to lhs as a free function
{
	IntegerSet result(lhs);
	result += rhs;
	return result;
}

IntegerSet operator +(const IntegerSet & lhs, const int & integer_to_be_added) // same process in above fnction with having different parameters
{
	IntegerSet rhs;
	rhs.Takeinputs(integer_to_be_added);
	IntegerSet result;
	result = lhs + rhs;
	return result;

}

bool operator == (const IntegerSet & lhs, const IntegerSet & rhs) //It is similar to the function in the lecture slides
{
	return lhs.Set_Equality_Checker(rhs);
}


bool operator != (const IntegerSet & lhs, const IntegerSet & rhs) //It is similar to the function in the lecture slides
{
	return !(lhs == rhs);
}

bool operator <= (const int & lhs, const IntegerSet & rhs)
{
	return rhs.In_or_not_checker(lhs);
}


bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs)
{
	return rhs.In_or_not_checker(lhs);
}


/*-----------------------------Free Functions---------------------------------------------------*/


