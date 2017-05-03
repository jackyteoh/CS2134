// 02.07.2017 Notes - Algorithm Analysis pt. 2
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

int mcss(vector<int> v) { // O(n^3) cubic (3 for loops) 
	int maxSum = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i; j < v.size(); j++) {
			int sum = 0;
			for (int k = i; k <= j; k++) { // Starts again from k, resums everything
				sum += v[k];
			}
			if (sum > maxSum) {
				maxSum = sum;
			}
		}
	}
	return maxSum;
}

int mcss2(vector<int> v) { // O(n^2) quadratic (2 for loops)
	int maxSum = 0;
	for (int i = 0; i < v.size(); i++) {
		int sum = 0;
		for (int j = i; i < v.size(); j++) { // Ending point = starting point
			sum += v[j];					 // Sums again ONLY when you advance the starting point(i)
			if (sum > maxSum) {
				maxSum = sum;
			}
		}
	}
	return maxSum;
}

int mcss3(vector<int> v) { // O(n) Linear (1 for loop)
	int maxSum = 0;
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
		if (sum > maxSum) {
			maxSum = sum;
		}
		else if (sum <= 0) {
			sum = 0;
		}
	}
	return maxSum;
}

void func(vector<int> v) { // O(n^2) Quadratic
	int total = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			if (i == j) { // Only runs n times, i == j for how many elements are in the vector (n)
				for (int k = 0; k < v.size(); k++) { // Only runs if outer for loops are equal, n times. n*n = n^2
					total += v[k];
				}
			}
		}
	}
}

int fib(int n) { // O(2^n) Exponential
	if (n < 2) {
		return 1;
	}
	return fib(n - 1) + fib(n - 2); // Doubling the amount of work you're doing, have to find the fib(1)... everytime
}

class Timer {
private:
	double start;
public:
	Timer() { start = clock(); }
	double elapsed() { return (clock() - start) / CLOCKS_PER_SEC; }
	void reset() { start = clock(); }
};


void func2(vector<int>& v) {
	double sum = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			sum += v[j];
		}
	}
}

int main() {
	// Fib
	double elapsed;
	double f;
	Timer t;
	for (int i = 5; i < 100; i++) {
		t.reset();
		f = fib(i);
		elapsed = t.elapsed();
		cout << "Fib(" << i << ")=" << f << ", which takes " << elapsed << " seconds." << endl;
	}

	// func2
	vector<int> x;
	double elapsed2;
	Timer m;
	int startSize = 2000;
	for (int i = startSize; i < 10000; i += startSize) {
		x.resize(i);
		m.reset();
		func2(x);
		elapsed = m.elapsed();
		cout << "X.size() = " << x.size() << ", function took " << elapsed << " seconds to run." << endl;
	}
	system("pause");
}

/*
Best - O(1) - constant (Find the middle of an array)
O(log n) - logarithmic (Binary search) (Halving/Doubling)
O(n) - linear
O(n log n) 
O(n^2) - Quadratic
O(n^3) - Cubic
Worst - O(2^n) - Exponential

Maximum Contiguous Subsequence Sum (MCSS Algorithm/Problem)
Given a set of numbers, determine the MCSS
{2, 3, -5, 8, 1}
Starting point and ending point only
Can't just add 2, 3, 8, 1; skips -5
Maximum = 9, can be {8,1} or {2,3,-5,8,1} 
Has to be in sequence

{3, 1, 5, 9, 2} = 20
{-3, 5, -2, 7, 6} = 16 {5, -2, 7, 6}
{-2, -4, -3, -1, -5} = 0 (You can choose to not sum any (the empty set, which is in every set)).

If you divide out the algorithm you get left with constants?
Empyrical way to prove runtime of algorithms.
*/