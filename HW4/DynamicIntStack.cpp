#include <iostream>
#include "DynamicIntStack.h"

using namespace std;

//Constructor
DynamicIntStack::DynamicIntStack()
{
	top_of_stack = NULL;
}

//Destructor
DynamicIntStack::~DynamicIntStack()
{
	NodeforDynamicStack * temp;
	while(top_of_stack != NULL)
	{
		temp = top_of_stack->next_node;
		delete top_of_stack;
		top_of_stack = temp;
	}
}

//Checking whether stack is empty or not
bool DynamicIntStack::isStackEmpty()
{
	if(top_of_stack == NULL)
		return true;
	else
		return false;
}

//Pushing the related coordinates to the stack
void DynamicIntStack::push(const int & x_coordinate, const int & y_coordinate)
{
	NodeforDynamicStack * Going_to_be_added = new NodeforDynamicStack(x_coordinate, y_coordinate);
	if(top_of_stack == NULL)
	{
		top_of_stack = Going_to_be_added;
	}
	else
	{
		Going_to_be_added->next_node = top_of_stack;
		top_of_stack = Going_to_be_added;
	}
}

//Popping the stack elements when needed
void DynamicIntStack::pop(int & x_coordinate, int & y_coordinate)
{
	NodeforDynamicStack * temp;
	if(!isStackEmpty())
	{
		x_coordinate = top_of_stack->x_coordinate;
		y_coordinate = top_of_stack->y_coordinate;
		temp = top_of_stack->next_node;
		delete top_of_stack;
		top_of_stack = temp; 
	}
	
}
