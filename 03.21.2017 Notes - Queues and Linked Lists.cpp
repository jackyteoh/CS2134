// 03.21.2017 Notes - Queues and Linked Lists
// 03.28.2017 Exam 3 - Design Patterns, Recursions, Stacks, and Queues
// SATURDAY EXTRA CLASS SESSION CANCELLED
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

template <class T>
class Queue {
	list<T> data;
public:
	void push(T newitem) { data.push_back(newitem); }
	T pop();
	T& top() { return *data.begin(); }
	T top()const { return *data.begin(); }
	bool isEmpty()const { return data.begin() == data.end(); }
	void clear() { data.clear(); }
};

template <class T>
T Queue<T>::pop() {
	T retval = top();
	data.pop_front();
	return retval;
}

template <class T>
class VQueue {
	T* data;
	int start;//location of the oldest element
	int end; //location of the newest element
	int size; //number of elements in the queue
	int capacity; //capacity of the dynamic array
public:
	VQueue();
	virtual ~VQueue() { delete[] data; }
	VQueue(const VQueue& rhs) : data(nullptr) { *this = rhs; }
	T& top() { return data[start]; }
	T top()const { return data[start]; }
	bool isEmpty()const { return size == 0; }
	int numOfElements()const { return size; }

	VQueue& operator=(const VQueue& rhs);
	void push(const T& newdata);
	T pop();
};
template <class T>
VQueue<T>& VQueue<T>::operator=(const VQueue& rhs) {
	if (this == &rhs)
		return *this;
	delete[] data;
	if (rhs.size >= 5)
		capacity = rhs.size + 1;
	else
		capacity = 5;
	data = new T[capacity];
	if (rhs.start == -1) {
		start = end = -1;
		size = 0;
		return;
	}
	start = 0;
	int i = rhs.start;
	size = 0;
	do {
		data[size++] = rhs.data[i++];
		if (i == rhs.capacity)
			i = 0;
	} while (i != rhs.end);
	data[size++] = rhs.data[i]; //copy the last element
	end = size - 1;
}

template <class T>
void VQueue<T>::push(const T& newdata) {
	size++;
	if (start == -1) { //special case for an empty queue
		start = end = 0;
		data[start] = newdata;
		return;
	}
	end++;
	if (end == capacity)
		end = 0;
	data[end] = newdata;
	if (size == capacity) { //time to grow!!!
		int newsize = size * 2;
		T* temp = new T[newsize];
		int tempcount = 0;
		int i = start;
		do {
			temp[tempcount++] = data[i++];
			if (i == capacity)
				i = 0;
		} while (i != start);
		delete[] data;
		data = temp;
		start = 0;
		end = tempcount - 1;
		capacity = newsize;
	}
}
template <class T>
T VQueue<T>::pop() {
	if (size == 0)
		return T();
	T retval = top();
	size--;
	start++;
	if (start == capacity) //ran off the end here
		start = 0;
	if (isEmpty())
		start = end = -1;
	return retval;
}

template <class T>
VQueue<T>::VQueue() {
	capacity = 5;
	size = 0;
	start = -1;
	end = -1;
	data = new T[capacity];
}

/*
Linked Lists
Singularly Linked List - X
| 1 | -> | 2 | -> | 3 |
          ptr
Hard to delete ptr

Doubly Linked List
| 1 | <-> | 2 | <-> | 3 | 
	       ptr
easy to delete ptr

Circularly Linked Lists
No nulls in a circularly linked list
last node links back to the first
Each node has 1 pointer

Doubly Circularly Linked List - X
Same as a circularly linked list, except there is a prev and next pointer for each node
Each node has 2 pointers

MAINLY GOING TO BE USING DOUBLY LINKED LISTS AND CIRCULARLY LINKED LISTS.
*/

int main() {
	VQueue<int> vq;
	srand(time(NULL));
	int val = 0;
	for (int i = 0; i < 10; i++) {
		int pushes = rand() % 20;
		int pops = rand() % 20;
		if (pops > pushes)
			swap(pushes, pops);
		for (int j = 0; j < pushes; j++)
			vq.push(val++);
		for (int j = 0; j < pops; j++)
			cout << vq.pop() << endl;
		cout << "***********looping******" << endl;
	}
}

/*
Rule: there is always one empty space in the queue(?)
s = start, e = end

| 1 | 2 | 3 | 4 |  |  |  |  |
  s           e
push(1)
push(2)
push(3)
push(4)

push(5)
| 1 | 2 | 3 | 4 | 5 |  |  |  |
  s               e
pop() -> pops 1
| 1 | 2 | 3 | 4 | 5 |  |  |  |
      s           e
pop() -> pops 2
pop() -> pops 3

| 1 | 2 | 3 | 4 | 5 |  |  |  |
              s   e
push(6)
push(7)
push(8)

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
              s               e
push(9)

| 9 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
  e           s 
after they're popped, they're still there in main memory but the positions of the 2 and 3 aren't relevant anymore
Can be overwritten
*/