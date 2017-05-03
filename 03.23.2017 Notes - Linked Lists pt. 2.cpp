// 03.23.2017 Notes - Linked Lists pt. 2
// Exam 3 on Tuesday 03.28.2017 - Design Patterns(Functors), Recursions, Stacks, and Queues
// Homework 3 due on 03.27.2017
// Exam 4 on Thursday 04.13.2017 - 
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
class LList;

template <class T>
class LListItr;

template <class T>
class LListNode {
	LListNode<T>* prev, *next;
	T data;
public:
	LListNode(const T& newdata = T(), LListNode<T>* prev = nullptr, LListNode<T>* next = nullptr) :
		data(newdata), prev(prev), next(next) {}
	friend class LList < T >;
	friend class LListItr < T >;
};

template <class T>
class LListItr {
	LListNode<T>* ptr;
public:
	LListItr(LListNode<T>* item = nullptr) :ptr(item) {}
	T operator*()const { return ptr->data; }
	T& operator*() { return ptr->data; }
	bool operator==(const LListItr<T>& rhs) { return ptr == rhs.ptr; }
	bool operator!=(const LListItr<T>& rhs) { return ptr != rhs.ptr; }
	LListItr<T> operator++(int);
	LListItr<T> operator--(int);
	LListItr<T>& operator++();
	LListItr<T>& operator--();

	friend class LList < T >;
};

template <class T>
LListItr<T> LListItr<T>::operator++(int) {
	LListItr<T> temp = *this;
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return temp;
}
template <class T>
LListItr<T> LListItr<T>::operator--(int) {
	LListItr<T> temp = *this;
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator++() {
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return *this;
}
template <class T>
LListItr<T>& LListItr<T>::operator--() {
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return *this;
}
template <class T>
class LList {
	LListNode<T> *head, *tail;
	int numOfNodes;
public:
	bool isEmpty()const { return size() == 0; }
	LListItr<T> begin()const { return head->next; } // actually returns a LListNode<T>* but the LListItr constructor automatically makes it a LListItr
	LListItr<T> end() const { return tail; }
	int size() const { return numOfNodes; }
	void clear() { while (!isEmpty()) pop_front(); }
	LList();
	~LList();
	T pop_back() { return remove(LListItr<T>(tail->prev)); }
	T pop_front() { return remove(LListItr<T>(head->next)); }
	void push_back(const T& data) { insertBefore(tail, data); }
	void push_front(const T& data) { insertAfter(head, data); }
	T remove(LListItr<T>& itr);
	void insertAfter(LListItr<T> itr, const T& newdata) { insertBefore(itr.ptr->next, newdata); }
	void insertBefore(LListItr<T> itr, const T& newdata);
	LListItr<T> find(const T& item) const;
	LList<T>& operator=(const LList<T>& rhs);
	LList(const LList<T>& rhs);
};


template <class T>
LList<T>::LList(const LList<T>& rhs) {
	numOfNodes = 0;
	head = new LListNode < T >;
	tail = new LListNode < T >;
	head->next = tail;
	tail->prev = head;
	*this = rhs;
}
template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs) {
	if (this == &rhs)
		return *this;
	clear();
	for (LListItr<T> i = rhs.begin(); i != rhs.end(); i++)  // copies everything in rhs and pushes back into original
		push_back(*i);
	return *this;
}

template <class T>
LListItr<T> LList<T>::find(const T& item) const {
	LListNode<T>* temp = head->next;
	while (temp != tail && temp->data != item)
		temp = temp->next;
	return temp;
}
template <class T>
void LList<T>::insertBefore(LListItr<T> itr, const T& newdata) {
	numOfNodes++;
	itr.ptr->prev = new LListNode<T>(newdata, itr.ptr->prev, itr.ptr);
	itr.ptr->prev->prev->next = itr.ptr->prev;
}

template <class T>
T LList<T>::remove(LListItr<T>& itr) {
	numOfNodes--;
	T retval = itr.ptr->data;
	itr.ptr->prev->next = itr.ptr->next;
	itr.ptr->next->prev = itr.ptr->prev;
	delete itr.ptr;
	itr.ptr = tail;
	return retval;
}


template <class T>
void LList<T>::clear() { // long way
	LListNode<T>* temp = head->next;
	LListNode<T>* toDelete = head->next;
	while (temp != tail) {
		temp = temp->next;
		delete toDelete;
		toDelete = temp;
	}
	head->next = tail;
	tail->prev = head;
}

template<class T>
void LList<T>::clear() { // shorter way
	while (!isEmpty()) {
		pop_front();
	}
}

template <class T>
LList<T>::LList() {
	numOfNodes = 0;
	head = new LListNode < T >;
	tail = new LListNode < T >;
	head->next = tail;
	tail->prev = head;

	// ALTERNATIVE METHOD
	head = new LListNode<T>(T(), nullptr, tail = new LListNode<T>);
	tail->prev = head;
}

template <class T>
LList<T>::~LList() {
	clear();
	delete head;
	delete tail;
}


int main() {
	LList<int> l;
	for (int i = 0; i < 10; i++) {
		l.push_front(i);
	}
	while (!l.isEmpty()) {
		cout << l.pop_back();
	}
}

/*
LListNode (data, prev, next)
LList (first, last) / (head, tail)
LListItr (LListIterator) - Pointer that has access to data but not access to next (?)

LList with one element. INCORRECT
head		tail
   |  | 1 |  |

in iterator
begin - returns node
end - returns null

LList a;
a.push_back(1);
LListItr i = a.end();
i--;
if you didn't have dummy nodes and you tried to decrement the iterator, it wouldn't point to anywhere?
Need dummy nodes

LList with one element. CORRECT
head				  tail
||| <-> | | 1 | | <-> |||
dummy nodes needed

LList class functions:
begin
end
size
push_back
push_front
pop_back
pop_front
insertAfter
insertBefore
remove
find
clear
isEmpty
constructor
destructor
assignment operator
copy constructor
*/