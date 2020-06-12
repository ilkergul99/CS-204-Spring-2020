#ifndef _DynamicIntStack_
#define _DynamicIntStack_

#include <iostream>

using namespace std;

// Node will include x-coordinate and y-coordinate and a pointer 
struct NodeforDynamicStack
{
	int x_coordinate;
	int y_coordinate;
	NodeforDynamicStack * next_node;

	NodeforDynamicStack::NodeforDynamicStack(int number_x = -1, int number_y = -1)
	{
		x_coordinate = number_x;
		y_coordinate = number_y;
		next_node = NULL;
	}
	
};

class DynamicIntStack
{
	private:
		NodeforDynamicStack * top_of_stack;

	public:
		//Constructor
		DynamicIntStack();
		//Destructor
		~DynamicIntStack();
		// In order to push elements when needed
		void push(const int & x_coordinate, const int & y_coordinate);
		//In order to pop elements when needed
		void pop(int & x_coordinate, int & y_coordinate);
		//In order to check whether the stack is empty or not
		bool isStackEmpty();
};

#endif