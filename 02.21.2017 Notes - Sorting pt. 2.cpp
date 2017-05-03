// 02.21.2017 Notes - Sorting pt.2
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <ctime>
#include <cmath>

using namespace std;

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

template<class T>
void printVec(vector<T>& v) {
	cout << "Vector: ";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "Sorted : ";
	merge(v);
	for (int j = 0; j < v.size(); j++) {
		cout << v[j];
	}
}

template <class T>
// O(n) - for loop 
// Big Theta (2n) - all while loops total up to n, + for loop = 2n
// while loops basically go over entire vector
void merge(vector<T>& v, int leftPos, int leftEnd, int rightEnd, vector<T>& temp) { 
	int rightPos = leftEnd + 1;
	int originalLeftPos = leftPos;
	int tempPos = leftPos;
	while (leftPos <= leftEnd && rightPos <= rightEnd) {
		if (v[leftPos] < v[rightPos]) {
			temp[tempPos++] = v[leftPos++];
		}
		else {
			temp[tempPos++] = v[rightPos++];
		}
	}
	while (leftPos <= leftEnd) {
		temp[tempPos++] = v[leftPos++];
	}
	while (rightPos <= rightEnd) {
		temp[tempPos++] = v[rightPos++];
	}
	for (int i = originalLeftPos; i <= rightEnd; i++) { // Copying from temp back into v
		v[i] = temp[i];
	}
}

// | 2 | 3 | 7 | 9 || 1 | 4 | 6 | 8 |

// | 0 | 0 | 0 | 0 || 0 | 0 | 0 | 0 |
// tempPos


template <class T>
// O(n log n)
// Downside : Takes an additional amount of memory for copying 
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

class Timer {
private:
	double start;
public:
	Timer() { start = clock(); }
	double elapsed() { return (clock() - start) / CLOCKS_PER_SEC; }
	void reset() { start = clock(); }
};

template <class T>
void insertionSort(vector<T>& v, int start, int end) {
	for (int i = start + 1; i < end; i++) { // Starts out with i = 1; til v.size(). <- O(n)
		T temp = v[i];					 // make a copy of v[i], "hole" inside the array. Copies items that are greater than our value in the array
		int j = i;
		for (j = i; j > 0 && v[j - 1] > temp; j--) {
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

template <class T>
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
	vector<int> temp;
	srand(time(NULL));
	int startSize = 100000;
	Timer t;
	double elapsed;
	for (int i = startSize; i < startSize * 10; i+= startSize){
		for (int j = 0; j < startSize; j++) {
			temp.push_back(rand() % 100);
		}
		t.reset();
		mergeSort(temp);
		elapsed = t.elapsed();
		cout << "Size = " << temp.size() << "\t time to Sort = " << elapsed << endl;
	}
}

/*
Worst Case scenario of quick sort = n^2
n = 1,000,000
O(n^2) = 
Big Theta (n(n-1)/2) = 500,000,000,000 (500 billion loops)

Quicksort Alone = 20,000,000 loops (2n)
Insertion Sort on 100,000 x 10 Array
4,500,000 loops
20,000,000 + 4,500,000 loops = 24,500,000 Loops compared to 500,000,000,000 loops
*/
