#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;
const int MAX = 1000;

template <class Type>
class my_queue
{
private:
	Type the_queue[MAX];
	int count = 0;
public:
	Type front();
	Type back();
	void pop();
	void push(const Type&);
	bool isempty();
};

template <class Type>
Type my_queue<Type>::front() {
	if (count) {
		return the_queue[0];
	}
	else {
		throw runtime_error("The queue is empty!");
	}
}

template <class Type>
Type my_queue<Type>::back() {
	if (count) { // if the count is more than 0 (i.e. the number of elements in the queue is more than 0)
		return the_queue[count - 1]; // the last element in the queue
	}
	else 
		throw runtime_error("The queue is empty!"); // throw an exception/runtime error
}

template <class Type>
void my_queue<Type>::pop() {
	if (count) { // if the number of elements is more than 0, we can pop
		for (int i = 1; i < count; i++) // iterating through the queue
			the_queue[i - 1] = the_queue[i]; // initializing each element to the element after it
		count--; // decrement the number of elements in the queue
	}
	else // if there're no elements
		throw runtime_error("The queue is empty!"); // throw an exception/runtime error
}

template <class Type>
void my_queue<Type>::push(const Type& element) {
	if (count < MAX) { // only if the number of elements is less than the maximum number allowable
		the_queue[count] = element; // initialize the the (n+1)th element 
									// (where n is the number of elements in the queue)
		count++; // increment the number of elements in the queue
	}
	else  // if the number of elements in the queue is equal to the maximum size of the queue
		throw runtime_error("The maximum size has been reached!");  // throw an exception/runtime error
}

template <class Type>
bool my_queue<Type>::isempty() {
	return (count == 0); 
}