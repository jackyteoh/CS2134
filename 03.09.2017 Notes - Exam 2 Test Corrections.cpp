// 03.09.2017 Notes - Exam 2 Test Corrections and Queues
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

// Question 1 - If you sort the vector, pass by value. If you don't sort, pass by reference
int q1(vector<int> v) { // YOU CAN SORT ON THE TEST UNLESS STATED OTHERWISE
	sort(v.begin(), v.end());
	int minDist = INT_MAX;
	for (int i = 1; i < v.size(); i++) {
		if (abs(v[i] - v[i - 1]) < minDist) {
			minDist = abs(v[i] - v[i - 1]);
		}
	}
	return minDist;
}

// Question 2
vector<int> q2(multimap<char, int> m, char line) {
	vector<int> allTimes;
	for (multimap<char, int>::iterator i = m.begin(); i != m.end(); i++) {
		if (i->first == line) {
			allTimes.push_back(i->second);
		}
	}
	return allTimes;
}

// Question 3a
vector<pair<double, double>> q3a(vector<double> men, vector<double> women) { // O(n^2)
	vector<pair<double, double>> matches;
	for (int i = 0; i < men.size(); i++) {
		int minMan = 0;
		int minWoman = 0;
		for (int j = 1; j < men.size(); j++) {
			if (men[j] < men[minMan]) {
				minMan = j;
			}
		}
		for (int j = 1; j < women.size(); j++) {
			if (women[j] < women[minWoman]) {
				minWoman = j;
			}
		}
		pair<double, double> temp(men[minMan], women[minWoman]);
		men[minMan] = DBL_MAX;
		women[minWoman] = DBL_MAX;
		matches.push_back(temp);
	}
	return matches;
}

// Question 3b
// Runtime of the above algorithm = O(n^2)

// Question 3c
vector<pair<double, double>> q3c(vector<double> men, vector<double> women) {
	sort(men.begin(), men.end());
	sort(women.begin(), women.end());
	vector<pair<double, double>> matches2;
	pair<double, double> couple;
	for (int i = 0; i < men.size(); i++) {
		couple.first = men[i];
		couple.second = women[i];
		matches2.push_back(couple);
	}
	return matches2;
}

// Question 3d
// The runtime of the above solution is O(n log(n))

// Question 4a
// The Big-O Runtime of running just the median-of-three partionining portion is O(1) Constant.

// Question 4b
// The Big-O Runtime of the Quicksort function if the pivot was the second lowest number in the set is O(n^2). (worst case)

// Question 5a - Takes in a vector of Elephant pointers
class Elephant {
private:
	int size;
public:
	bool operator<(const Elephant& rhs) {
		return size < rhs.size;
	}
};

void q5a(vector<Elephant*>& v) {
	for (int i = 1; i < v.size(); i++) {
		Elephant* temp = v[i];
		int j = i;
		for (j = i; j > 0 && *(temp) < *(v[j - 1]); j--) {
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

// Question 5b - Takes in a vector of Elephants
void q5b(vector<Elephant>& v) {
	vector<Elephant*> vep;
	for (int i = 0; i < v.size(); i++) {
		vep.push_back(&v[i]);
	}

	// Ranged for loop
	for (Elephant& e : v) {
		vep.push_back(&e);
	}

	q5a(vep);
	vector<Elephant> temp;
	for (Elephant* ptr : vep) {
		temp.push_back(*ptr);
	}
	v = temp;
}

template<class T>
class Queue {
private:
	list<T> data;
public:
	void push(T newItem) { data.push_back(newItem); }
	T pop();
	T& top() { return *data.begin(); }
	T top() const { return *data.begin(); }
	bool isEmpty() { return data.begin() == data.end(); }
	void clear() { data.clear(); }
};

template<class T>
T Queue::pop() {
	T retval = top();
	data.pop_front();
	return retval;
}

int main() {

}

/*
In-fix:
5 + 4 * (3 + 2^3) / 2

Post-fix:
54323^+*2/+
(2^3) = 8
3 + 8 = 11
11 * 4 = 44
44 / 2 = 22
5 + 22 = 27
Final Answer = 27

Queue - FIFO (First In First Out)
Functions:
				  Vector	List
push (enqueue)	O(1)/O(n)	O(1)
pop  (dequeue)     O(n)		O(1)
top				   O(1)		O(1)
isEmpty			   O(1)		O(1)
clear			   O(1)		O(n)

Circular Buffer
1 | 2 | 3 | 4 | 5 | 6
s				e

1 | 2 | 3 | 4 | 5 | 6
    s               e
	
1 | 2 | 3 | 4 | 5 | 6
e   s

s = start index
e = end index
if you keep iterating the end, it wraps around to the beginning

*/