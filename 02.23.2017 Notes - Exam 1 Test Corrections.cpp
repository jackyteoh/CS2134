// 02.23.2017 Notes - Exam 1 Test Corrections
// Exam 2 (Algorithm Analysis, Sorting) - February 28, 2017 (Tuesday)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <list>
#include <set>

using namespace std;

// Test Corrections
// Question 3 - Sum of Integers
int question3i(int num) { // Iterative
	int total = 0;
	while (num > 0) {
		total += num % 10;
		num /= 10;
	}
	return total;
}

int question3r(int num) { // Recursive
	if (num <= 0) {
		return 0;
	}
	return num % 10 + question3r(num / 10);
}

// Question 4 - C-string
vector<int> locate(char* toSearch, char search) { // OR vector<int> locate(char toSearch[], char search)
	vector<int> locations;
	for (int i = 0; toSearch[i] != '\0'; i++) {
		if (toSearch[i] == search) {
			locations.push_back(i);
		}
	}
	return locations;
}

map<int, double> getBusDistanceMap(int x) {

}

//Question 5 - Bus Stop
int closest(int busStop) {
	map<int, double> m = getBusDistanceMap(busStop);
	int minDist = m.begin()->second;
	int closestBus = m.begin()->first;
	for (map<int, double>::iterator i = m.begin(); i != m.end(); i++) {
		if (i->second < minDist) {
			minDist = i->second;
			closestBus = i->first;
		}
	}
	return closestBus;
}

int closest2(int busStop) { 
	map<int, double> m = getBusDistanceMap(busStop);
	int closestBus = m.begin()->first;
	for (map <int, double>::iterator i = m.begin(); i != m.end(); i++) {
		if (i->second < m[closestBus]) { // m[closestBus] takes log n, makes the original O(n) function a O(n log n) function
			closestBus = i->first;
		}
	}
	return closestBus;
}

class Person {
public:
	string name;
	int age;
	double salary;
};

class lessThanOnAge { // Functor used for sorting
public:
	bool operator()(const Person& a, const Person& b) { // Functor (function object)
		return a.age < b.age; 
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
void quickSort(vector<T>& v, int start, int end) {
	if ((start + 10) > end) {
		insertionSort(v, start, end);
		return;
	}

	int center = (start + end) / 2;
	if (v[center] < v[start]) { // begin median-of-three partitioning
		swap(v[center], v[start]);
	}
	if (v[end] < v[start]) {
		swap(v[end], v[start]);
	}
	if (v[end] < v[center]) {
		swap(v[end], v[center]);
	}

	T pivot = v[center];
	swap(v[center], v[end - 1]);
	int i = start;
	int j = end - 1;
	for (;;) { // only runs through once
		while (v[++i] < pivot) {

		}
		while (pivot < v[--j]) {

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

int main() {

}

/*
Can't compare people; can't say one is better than another
Need to compare them with some type of parameter (height, salary, etc)
Just use the objects for comparison (Functor)
*/