// 02.16.2017 Notes - Sorting
// Exam 2 (Algorithm Analysis, Sorting) - February 28, 2017 (Tuesday) (?)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

// Selection Sort video on Youtube for visual aid ( https://www.youtube.com/watch?v=92BfuxHn2XE )
template <class T> 
// Average Case for Selection Sort - O(n^2)
// Best Case for Selection Sort - O(n^2) You still have to iterate twice
// Worst Case for Selection Sort - O(n^2)
void selectionSort(vector<T>& v) { // O(n^2)
	for (int i = 0; i < v.size(); i++) { // Starts at 0, goes to v.size()
		int min = i;					 // Sets min to the one being checked
		for (int j = i + 1; j < v.size(); j++) { // Iterates again over the vector, excluding the one being sorted (and already sorted)
			if (v[j] < v[min]) {		// If it's less, makes min = the lesser one
				min = j;
			}
		}
		T temp = v[min];				// Makes a T temp = to the v[min]
		v[i] = v[min];					// Sets the one to be sorted = to the min, therefore it's sorted
		v[min] = temp;					// switches the one that was in the initial position before with the currently sorted one
	}
}

// Insertion Sort Youtube Visualization Aid ( https://www.youtube.com/watch?v=8oJS1BMKE64 )
// Best Case - O(n) - Already sorted, only has to iterate and check once
// Average Case - O(n^2)
// Worst Case - O(n^2)
template <class T>
void insertionSort(vector<T>& v) {
	for (int i = 1; i < v.size(); i++) { // Starts out with i = 1; til v.size(). <- O(n)
		T temp = v[i];					 // make a copy of v[i], "hole" inside the array. Copies items that are greater than our value in the array
		int j = i;
		for (j = i; j > 0 && v[j - 1] > temp; j--) {
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

//   0   1   2   3   4   5   6   7   8
// | 7 | 3 | 5 | 9 | 2 | 1 | 6 | 4 | 8 |
//       i
//       j

// T temp = v[i] = v[1] = 3;
// v[j - 1] > temp && j > 0, v[j - 1] = v[1 - 1] = v[0] = 7. 7 > temp ? 7 > 3 ? YES.
// v[j] = v[j - 1]. v[1] = v[0]. v[1] = 7
// j decremented, v[j] = v[0] = temp = 3
// finishes loop, advances i

// | 3 | 7 | 5 | 9 | 2 | 1 | 6 | 4 | 8 |
//           i 
//           j

// T temp = v[i] = v[2] = 5
// v[j - 1] > temp && j > 0; v[j - 1] = v[2 - 1] = v[1] = 7. 7 > temp ? 7 > 5 ? YES.
// v[j] = v[j - 1]. v[2] = v[1]. v[1] = 5
// j decremented. v[j] = v[1] = temp = 5
// j = 1. Still bigger than 0. For loops again.
// However this time 5 > 3. Therefore breaks the loop.
// Finishes loop, advances i, repeats again.

// | 3 | 5 | 7 | 9 | 2 | 1 | 6 | 4 | 8 |
//               i
//               j                         
// Repeats for the entire thing until it's sorted.


// https://www.youtube.com/watch?v=n4sk-SzGvZA
// shellSort = divide and conquer algorithm
// Best Case - O(n log n)
// Average Case - approaches O(n^2) due to poor choice of gaps
// Worst Case - O(n^2)
template <class T>
void shellSort(vector<T>& v) {
	for (int gap = v.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < v.size(); i++) {
			T temp = v[i];
			int j = i;
			for (; j >= gap && temp < v[j - gap]; j -= gap) { // Optional initialization, j = i is the initialization
				v[j] = v[j - gap];
			}
			v[j] = temp;
		}
	}
}

//   0   1   2   3   4   5   6   7
// | 5 | 7 | 9 | 3 | 2 | 1 | 8 | 4 |
//				   |
// | 3 | 5 | 7 | 9 |      | 1 | 2 | 4 | 8 |
// O(n) needed to sort two sorted lists

template <class T>
void mergeSort(vector<T>& v, int start, int end, vector<T>& temp) {
	int mid = (start + end) / 2;
	if (end <= start) { // one element = already sorted, don't need to do anything
		return;
	}
	mergeSort(v, start, mid, temp);
	mergeSort(v, mid + 1, end, temp);
	merge(v, start, mid, end, temp);
}

template <class T>
void mergeSort(vector<T>& v) { // Acts as a driver, creates a temp vector & calls mergeSort function above
	vector<T> temp;
	temp.resize(v.size());
	mergeSort(v, 0, v.size() - 1, temp);
}

int main() {

}

/*
How to compare two strings:
Lexicographically - a generalization of the way the alphabetical order of words is based on the 
					alphabetical order of their component letters.

Using only less than operator
a < b  |  a < b
a > b  |  b < a               b is less than a = a is greater than b
a <= b |  !(b < a)            b is less than a is FALSE. that means that a has to be <= b
a >= b |  !(a < b)            a is less than b is FALSE. that means that b has to be <= a
a == b |  !(a < b || b < a)   if a < b or b < a is true, negates that. they are not equal. If either are false (a = b), then negates that, they are equal
		  !(b < a) && !(a < b)	
a != b |  a < b || b < a      if a < b OR b < a, they are not equal.

Big Theta = EXACT amount of time needed to run (n(n-1)/2)
Big O = Estimated amount of time needed to run (n^2) 

WORST CASE for insertion sort of 10 elements = 45 Loops
(n(n-1)/2) = (10(9)/2) = (90/2) = 45

Impossible to do O(n * log n) for any comparison based sorting
*/