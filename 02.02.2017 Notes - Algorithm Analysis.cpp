// 02.02.2017 Notes - Algorithm Analysis
// DSA First Test (02.14.2017 Tuesday)
// DSA Homework 1 due 02.08.2017 Wednesday
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cmath>

using namespace std;

void func(int n) {
	for (int i = 0; i < n; i++) {
		cout << i << endl;
	}
}

class Point {
public:
	Point(int newx, int newy) : x(newx), y(newy) {}
	int x;
	int y;
};

double distance(Point a, Point b) { // Big O of this function is constant
	return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
}

int closestToOrigin(vector<Point> v) { // Linear, O(n). Any line inside the for loop can be the controlling line of code (Cloc)
	Point origin(0, 0);
	double min = distance(origin, v[0]);
	int closest = 0;
	for (int i = 1; i < v.size(); i++) {
		double thisDist = distance(origin, v[i]); // Saving result of function because it may be used twice. More efficient
		if (thisDist < min) {
			closest = i;
			min = thisDist;
		}
	}
	return closest;
}

double closestPoints(vector<Point> v) { // Quadratic, O(n^2). Big Theta(n(n-1)/2). Two for loops. Second one is one less.
	double minDist = distance(v[0], v[1]);
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			double thisDist = distance(v[i], v[j]);
			if (thisDist < minDist) {
			minDist = thisDist;
			}
		}
	}
	return minDist;
}

int main() {
	int n = 100;
	for (int i = 0; i < n; i++) {
		cout << i << endl; // Controlling line of code
	}
	/* 
	Time needed to run is x.
	If input (n) changes to 101, it would take 1% more/longer. (0.01x longer)
	If n changes to 102 from 101, it would take 0.01x longer again. 
	If n changes to 200, it would take 2x.

	n   | Cloc (Controlling Line of Code)
	100 | 100 
	200 | 200 - 100 difference
	300 | 300 - 100 difference

	Time complexity for this task/code is O(n). [Linear]
	*/

	vector<int> v;

	int dups = 0;
	for (int i = 0; i < v.size(); i++) {			// ran "n" times
		for (int j = i + 1; j < v.size(); j++) {    // ran "(n - 1)/2" times; because we start at j = i + 1, one less element. On average, it runs half the array (thats why /2)
			if (v[i] == v[j]){					    // Controlling Line of Code
				dups++;								// (n(n-1))/2
			}
		}
	}
	cout << "There are " << dups << " duplicates in this vector." << endl;

	/*
	NON LINEAR (Quadratic)

	n   | CLOC
	2   | 1
	3   | 3     By adding one more element, added 2 more to cloc (by (n(n-1))/2)
	4   | 6
	5   | 10

	O(n^2) because n(n-1)/2 = 1/2(n^2) - 1/2(n). We care about the one that progresses most rapidly (n^2). Exclude coefficients + constants
	Big Theta(n(n-1)/2) -> EXACT time
	*/

	int x = 100;
	for (int i = 0; i < x; i++) {
		func(x);					// This is a quadratic, takes in x, does it x times. (x^2)
		func(i);					// This is STILL quadratic, takes in i, does it x times (x^2)
									// Big Theta(n(n-1)/2)
		func(5);					// O(n) the func will ONLY & ALWAYS print 5 times. Linear.
	}

}

/*
To get rid of duplicates inside a vector/list:
1) Compare first object/element (i) to every other element(j), advance i, check again.

Sort it by throwing it into a set and take it back out
You can't have duplicates in a set.

Minimize CPU usage - throw into set and take it out 
Minimize memory usage - Compare first object/element (i) to every other element(j), advance i, check again.

Easier to quantify memory - set + list with same data, double the memory (2x)
Harder to quantify CPU time

Concept:
Big O - used as a measurement of an underestimation of how long it will take for the process/task to be complete.
Generally dependent on the input size to the algorithm.
Models the delta between the input size of n and the input size of n+1
Models progression performance of the algorithm.

Big Theta is the exact amount of work we have to do.
Big Theta (n + 5)
O(n)

Big Theta(n^5 + n + 5)
O(n^5) -- increases the most rapidly, n is irrelevant after that.

In algorithm analysis, we usually only talk about huge numbers not small numbers

Constant algorithms will do better than anything else. O(1)
Finding the middle of the vector is constant, size/2 (Random Access)
O(log base 2 n) - Logarithmic - binary search
Finding the middle of a list, is linear. no random access. O(n)
O(n * log n)
O(n^2) quadratic
O(n^3) cubic
O(2^n) exponential

Constant < Logarithmic < Linear < O(n * log n) < Quadratic < Cubic < Exponential
Doubling money in the bank every year starting from $0 will take 20 years. (Exponential) 2^20 = >1,000,000

Never any constants inside a O(). Only one term (n) or n^something. 
*/