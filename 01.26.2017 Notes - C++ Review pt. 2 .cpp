// 01.26.2017 Notes - C++ Review pt. 2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Student {
public:
	int id;
	int* testScores;
};

void sayHello(ostream& outs) {
	outs << "Hello world!" << endl;
}

void openInputFile(ifstream& inFile) {
	string filename;
	cout << "Open which file?" << endl;
	cin >> filename;
	inFile.open(filename);
	while (!inFile) {
		cout << "BAD FILENAME!!" << endl;
		cout << "Open what filename?";
		cin >> filename;
		inFile.clear(); // need to clear before opening again
		inFile.open(filename);
	}
}

class SomeClass {
public:
	SomeClass() : temp(new int(0)) {}
	virtual ~SomeClass() {
		delete temp;
	}
	SomeClass(const SomeClass& rhs) {
		*temp = *rhs.temp;
	}
	SomeClass& operator=(const SomeClass& rhs) {
		if (&rhs == this) {
			return *this;
		}
		delete temp;
		temp = new int(*rhs.temp);
		return *this;
	}
private:
	int* temp;
};

void func(const list<int>& l) {
	for (list<int>::const_iterator i = l.begin; i != l.end(); i++) { // const parameter needs const_iterator, reg iterator can still alter stuff inside 
		cout << *i << endl;
		// *i += 2;         does not work, parameter is const, can't alter anything
	}
}

int main() {
	vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.push_back(i*100);
	}
	
	cout << v[3] << endl; // [ ] = random access iterator. access to any element takes the same amount of time. [3] = [100]


	list<int> l;
	for (int i = 0; i < 100; i++) {
		l.push_front(i * 10);
	}

	for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
		cout << *i << endl;
	}

	list<int>::iterator temp = l.end();
	temp--; // This now points temp to the last element in the list
	cout << *temp; // prints out last element in the list

	for (list<int>::reverse_iterator ri = l.rbegin(); ri != l.rend(); ri++) { // reverse iterators use .rbegin and .rend. ++ goes backwards (reverse)
		cout << *ri << endl;
	}


	ifstream inFile;
	openInputFile(inFile);
	int iarr[50];
	double darr[50];
	int count;
	while (count < 50 && inFile >> iarr[count]) {
		inFile >> darr[count];
		count++;
	}
	// Skip leading white space, reads valid characters, until trailing whitespace ?
	ofstream outFile;
	outFile.open("output.txt");
	outFile << "Hello world!" << endl;
	sayHello(outFile);
	sayHello(cout);

	int* y;
	y = new int(0);
	*y = 100;

	delete y;
	y = nullptr;

	Student* sptr;
	sptr = new Student;
	sptr->id = 1000;
	sptr->testScores = new int[3];
	sptr->testScores[0] = 100;
	sptr->testScores[1] = 90;
	sptr->testScores[2] = 95;

	delete[] sptr->testScores;
	delete sptr;
}

/*
Heap - no organization, kept track of by pointers
Scope - where the variable is created/located
Lifetime - how long the variable exists
Heap dynamic variables do not have a scope
Liftime of heap dynamic variables is whatever you say it is (new/delete)
Delete = delete what the pointer is pointing to (on the heap)

Arrays:
Stack Array = static in size.
if int arr[20], size cannot be changed. Only an array of size 20 can be created
Cannot pass in a variable into arr[ ], only if it's const, but can't change after.

int* arr = new int[x];
*arr === arr[0] pointer to an array points to the first element in the array

Heap Dynamic Array


STL - Standard Template Library
Each has diff removal/add procedure

Vectors
insert:
push_back()
pop_back()

access:
iterators: 
forward only, bidirectional, random access
reverse iterator
const iterator


Common functions:
empty() - returns boolean if vector is empty or not
clear() - empties the entire vector
size() - gives the size of the vector
capacity()
begin()
end()

Lists:
push_back
push_front
pop_back
pop_front
insert

accessors:
reverse iterators

Lists do not have random access !! no bracket. only forward only and bidirectional
the end is not the last item in the list, it's the item after the last item in the list
*/