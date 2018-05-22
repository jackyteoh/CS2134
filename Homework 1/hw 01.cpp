/*
Jacky Teoh
jt2908
CS 2134 - Data Structures & Algorithms : Homework Assignment 1
02.08.2017
hw 01.cpp
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

// Task 1 - Combination Lock
class CombinationLock {
public:
	// Constructor, taking in 3 #s for combination, defaulting state to locked.
	CombinationLock(int first, int second, int third) : combination(new int[3]), state(false) {
		combination[0] = first;
		combination[1] = second;
		combination[2] = third;
	}
	virtual ~CombinationLock() { // Destructor (Virtual)
		delete[] combination;
	}
	CombinationLock(const CombinationLock& rhs) = delete; // Forbidding copying of lock
	// Checks if attempt matches with actual combination, if yes opens, if not stays locked.
	void open(int* attempt) {
		for (int i = 0; i < 3; i++) {
			if (combination[i] == attempt[i]) {
				state = true;
				cout << "The combination is correct, and the lock is now open!" << endl;
			}
			else {
				cout << "This combination is not correct.." << endl;
			}
		}
	}
	// Opens the lock (open function tests if attempt is correct), if it is opened, changes the combination and locks it
	// If attempt is not correct, or the lock is locked, cannot change combination.
	void changeCombo(int* attempt, int* newCombination) {
		open(attempt);
		if (state) {
			for (int i = 0; i < 3; i++) {
				combination[i] = newCombination[i];
			}
			cout << "Your combination is now changed! Your new combination is: " << combination[0] << ", " << combination[1] << ", " << combination[2] << endl;
			state = false; // Lock the lock
		}
		else {
			cout << "Unable to change the combination." << endl;
		}
	}
private:
	int* combination;
	bool state;
};

// Task 2 - DynArray
template <typename J>
class DynArray {
public:
	DynArray() : arraySize(0), arrayCapacity(0), bracket(false), data(nullptr) {} // Constructor
	virtual ~DynArray() { // Destructor
		delete[] data;
	}
	DynArray& operator=(const DynArray& rhs) { // Assignment Operator
		if (this == &rhs) {
			return *this;
		}
		else {
			arraySize = rhs.arraySize;
			arrayCapacity = rhs.arrayCapacity;
			bracket = rhs.bracket;

			delete[] data;
			data = new J[arrayCapacity];
			for (int i = 0; i < arrayCapacity; i++) {
				data[i] = rhs.data[i];
			}

			return *this;
		}
	}
	DynArray(const DynArray& rhs) { // Copy Constructor
		*this = rhs;
	}
	size_t size() const {
		return arraySize;
	}
	size_t capacity() const {
		return arrayCapacity;
	}
	J operator[](int index) {
		bracket = true;
		return data[index];
	}
	void resize(int newSize) {
		J* temp = new J[newSize];
		if (newSize < arraySize) {            // Checks to see if the new size is smaller than old size
			arraySize = newSize;              // Changes to smaller size, to deletes old data
			arrayCapacity = newSize;
		}
		else {
			arraySize = newSize;
			arrayCapacity = newSize;
			for (int i = 0; i < arraySize; i++) {
				temp[i] = data[i];                    // Sets new data to old data
			}
			delete[] data;                            // Deletes old data
			data = temp;                              // puts new "resized" array back into data
		}
	}                                           // End of function call, temp deleted. Data is now the new resized array
	void push_back(J element) {
		if (bracket) {
			cout << "You cannot push_back anything onto this DynArray, brackets have been used." << endl;
			return;
		}
		else {
			if (arraySize == arrayCapacity) {
				resize(arraySize*2);
				data[arraySize++] = element;
			}
			else {
				data[arraySize++] = element;
			}
		}
	}
	int pop_back() {
		int retVal;
		if (arraySize > 0) {
			retVal = data[arraySize--];
		}
		return retVal;
	}
private:
	bool bracket;
	J* data;
	size_t arraySize;
	size_t arrayCapacity;
};

// Task 3 - Point of Sale (PoS) System
double PoS(map<int, double> prices, vector<int> shoppingBag) {
	double total = 0;

	//for (int i = 0; i < shoppingBag.size(); i++) { Why does this not work ??
	//	total += prices[i];
	//}

	for (int x : shoppingBag) { 
		total += prices[x];
	}

	return total;
}

int main() {
	ifstream shoppingList;
	shoppingList.open("HW1data.txt");

	if (shoppingList.is_open()) {
		cout << "Your file has opened successfully!" << endl;
	}
	else {
		cout << "There was an error in opening your file." << endl;
	}

	map<int, double> prices;
	int itemNumber;
	double itemPrice;

	while (shoppingList >> itemNumber >> itemPrice) {
		prices[itemNumber] = itemPrice;
		cout << "Item " << itemNumber << " = $" << itemPrice << endl;
	}

	vector<int> thingsToBuy = { 1, 99, 47, 22 };

	cout << "The total price of all the items is: $" << PoS(prices, thingsToBuy) << endl;

	shoppingList.close();
	system("pause");
}