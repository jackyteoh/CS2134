// 03.02.2017 Notes - Design Patterns & Recursion
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class lessThanOnAge; // pre-define class

class Person {
private:
	string name;
	int age;
	double salary;
public:
	Person(string newname = "", int age=0, double newsalary = 0) : name(newname), age(age), salary(newsalary) {}
	int getAge() const { return age; }
	double getSalary() const { return salary; }
	string getName() const { return name; }
	void printInfo() const {
		cout << "Name: " << name << ", Age: " << age << ", Salary: " << salary << endl;
	}

	friend class lessThanOnAge; // Make it a friend so the functor can access the private data member (age)
};

// Functor = function inside an object to do one thing?
class lessThanOnAge { // Functor used for sorting
public:
	bool operator()(const Person& a, const Person& b) { // Functor (function object)
		return a.age < b.age;
	}
};

class lessThanOnSalary { // Functor used for sorting
public:
	bool operator()(const Person& a, const Person& b) { // Functor (function object)
		return a.getSalary() < b.getSalary();
	}
};

template <class T, class S>
void insertionSort(vector<T>& v, int start, int end, S comparator) { // O(n^2)
	for (int i = start + 1; i < end; i++) { // Starts out with i = 1; til v.size(). <- O(n)
		T temp = v[i];					 // make a copy of v[i], "hole" inside the array. Copies items that are greater than our value in the array
		int j = i;
		for (j = i; j > 0 && comparator(v[j - 1], temp); j--) {
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

template <class T, class S>
// O(n log n) as long as the pivot is chosen well
void quickSort(vector<T>& v, int start, int end, S comparator) {
	if ((start + 10) > end) {
		insertionSort(v, start, end, comparator);
		return;
	}

	int center = (start + end) / 2;
	if (comparator(v[center], v[start])) { // begin median-of-three partitioning
		swap(v[center], v[start]);
	}
	if (comparator(v[end], v[start])) {
		swap(v[end], v[start]);
	}
	if (comparator(v[end], v[center])) {
		swap(v[end], v[center]);
	}

	T pivot = v[center];
	swap(v[center], v[end - 1]);
	int i = start;
	int j = end - 1;
	for (;;) { // only runs through once
		while (comparator(v[++i], pivot)) {

		}
		while (comparator(pivot, v[--j])) {

		}
		if (i < j) {
			swap(v[i], v[j]);
		}
		else {
			break;
		}
	}
	swap(v[i], v[end - 1]); // Moves pivot into its final position!

	quickSort(v, start, i - 1);
	quickSort(v, i + 1, end);
}

template <class T>
void quickSort(vector<T>& v) {
	quickSort(v, 0, v.size() - 1);
}

class findWealthyDrinkers {
public:
	bool operator()(const Person& p){
		if (p.getAge() > 21 && p.getSalary() >= 100000) {
			return true;
		}
	}
};

template<class T> 
vector<Person> ofAcceptableAge(vector<Person> v, T comparator) {
	vector<Person> acceptable;
	for (Person p : v) {
		if (comparator(p) == true) {
			acceptable.push_back(p);
		}
	}
	return acceptable;
}

bool lessThanOnName(const Person& a, const Person& b) {
	return a.getName() < b.getName();
}

void printInfo(Person arr[], int size) { // O(n)
	if (size <= 0) {
		return;
	}
	arr->printInfo();
	printInfo(arr + 1, size - 1); // You reduce by 1 each time, until size <= 0. Therefore you call the function n times
}

int binarySearch(vector<int> v, int start, int end, int toFind) { // O(log n) halving your search every recursive call
	if (start > end) {
		return -1;
	}
	int mid = (start + end) / 2;
	if (v[mid] == toFind) {
		return mid;
	}
	else if (v[mid] > toFind) {
		return binarySearch(v, start, mid - 1, toFind); // Recursion call eliminates 50% of the search values
	}
	else {
		return binarySearch(v, mid + 1, end, toFind); // Recursion call eliminates 50% of the search values
	}
}

int fib(int n) { // O(2^n) Exponential
	if (n > 2) {
		return fib(n - 1) + fib(n - 2); // 2 recursive function calls to the same set, but just a little smaller. Doubling amount of work, reducing set by 3, doubling, reduce, doubling, etc.
	}
	return 1;
}


void printBinary(int n) { // O(log n) Reducing the work by half each recursive call (n / 2);
	if (n < 2) {
		cout << n;
	}
	else {
		printBinary(n / 2);
		cout << n % 2;
	}
}

void printOct(int n) { // O(log BASE 8 n) Reducing the work each recursive call (n / 8);
	if (n < 8) {
		cout << n;
	}
	else {
		printOct(n / 8);
		cout << n % 8;
	}
}

const char HEX_LETTERS[] = "0123456789ABCDEF";
void printHex(int n) { // O(log BASE 16 n) Reducing the work each recursive call (n / 16);
	if (n < 16) {
		cout << HEX_LETTERS[n];
	}
	else {
		printHex(n / 16);
		cout << HEX_LETTERS[n % 16];
	}
}

// enumerated data type - NOT ON ANY UPCOMING EXAMS.
enum HAIR_COLOR { BROWN, BLOND, GRAY, WHITE, BLACK, RED };


int main() {
	vector<Person> v;
	v.push_back(Person("John Doe", 40, 50000));
	v.push_back(Person("James Dolittle", 29, 25000));
	v.push_back(Person("Claryssa Santana", 20, 1000000));

	// insertionSort(v, 0, v.size() - 1, lessThanOnAge()); // This also works, the parentheses "makes an object" of lessThanOnAge
	lessThanOnAge sorter;
	insertionSort(v, 0, v.size() - 1, sorter);

	for (Person p : v) {
		p.printInfo();
	}

	insertionSort(v, 0, v.size() - 1, lessThanOnSalary());
	cout << endl << endl;

	for (Person p : v) {
		p.printInfo();
	}

	insertionSort(v, 0, v.size() - 1, lessThanOnName); //Pointer to lessThanOnName ?
	cout << endl << endl;

	for (Person p : v) {
		p.printInfo();
	}

	vector<Person> wealthyDrinkers = ofAcceptableAge(v, findWealthyDrinkers());
	cout << "The wealthy drinkers are: " << endl;
	for (Person p : wealthyDrinkers) {
		p.printInfo();
	}

	for (int i = 0; i < v.size(); i++) { // O(n)
		cout << i << endl;
	}

	printHex(255);


	// part of enumerated data types. EXTRA INFO. NOT PART OF ANY UPCOMING EXAMS
	HAIR_COLOR h = BLOND;
}

/*
C++ treats every function as if it were a variable
You can pass a function to a function as a parameter

Parentheses after a class calls the constructor of the class, makes an object
Parentheses after a function calls the function itself 

Recursion: A function that calls itself
1) Base Case - The simplest possible problem we can generate/find
2) The Simple Case
3) The Reduction of the set by the Simple Case to get to the Base Case

Key to find the time complexity of recursion functions is in step 3 ^ The reduction of the set by the simple case to get to the base case

For loop inside a recursive call:
Depends on what each is reducing
for(;; --)
recursive(n-1)
O(n + n - 1 + n - 2 + n - 3 + n - 4 + etc) = O(n^2)

Stack: Like a stack of plates you can only take the top one
FILO - First In Last Out
LIFO - Last In First Out


EXTRA INFO. NOT ON ANY UPCOMING TESTS
RESEARCH TO LOOK INTO IF YOU WANT TO USE THESE.

C++11 : autoptr in STL
gets rid of some complexities of pointers
takes care of double delete + garbage on the heap problems
*/