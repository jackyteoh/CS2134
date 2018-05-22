/*
Jacky Teoh - jt2908
CS2134 - Data Structures & Algorithms : Homework 2 
03.02.2017
hw 02.cpp
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

class Timer {
private:
	double start;
public:
	Timer() { 
		start = clock(); 
	}
	double elapsed() { 
		return (clock() - start) / CLOCKS_PER_SEC; 
	}
	void reset() { 
		start = clock(); 
	}
};

bool is_prime1(int n) {
	if (n == 1 || n == 2) {
		return true;
	}
	for (int i = n / 2; i > 1; i--) {
		if (is_prime1(i) && n % i == 0) {
			return false;
		}
	}
	return true;
}

int count_primes1(int n) {
	int numberOfPrimes = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime1(i)) {
			numberOfPrimes++;
		}
	}
	return numberOfPrimes;
}

bool is_prime2(int n) {
	if (n == 1) {
		return true;
	}
	for (int i = n / 2; i > 1; i--) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int count_primes2(int n) {
	int numberOfPrimes = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime2(i)) {
			numberOfPrimes++;
		}
	}
	return numberOfPrimes;
}

bool is_prime3(int n) {
	if (n == 1) {
		return true;
	}
	for (int i = sqrt(n); i > 1; i--) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int count_primes3(int n) {
	int numberOfPrimes = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime3(i)) {
			numberOfPrimes++;
		}
	}
	return numberOfPrimes;
}

int main() {
	int option;
	int n;
	bool run = true;
	Timer t;
	while (run) {
		cout << "Which method(1, 2, 3 or 0 = Exit) : " << endl;
		cin >> option;
		if (!(option == 0 || option == 1 || option == 2 || option == 3)) {
			cout << "This is not one of the listed options. Please try again." << endl;
			break;
		}
		else if (option == 0) {
			cout << "Thank you." << endl;
			break;
		}

		cout << "Enter the value of n : " << endl;
		cin >> n;
		t.reset();

		if (option == 1) {
			cout << "There are " << count_primes1(n) << " prime numbers between 2 and " << n << endl;
			cout << "Approximately " << t.elapsed() << " seconds have elapsed." << endl;
		}
		else if (option == 2) {
			cout << "There are " << count_primes2(n) << " prime numbers between 2 and " << n << endl;
			cout << "Approximately " << t.elapsed() << " seconds have elapsed." << endl;
		}
		else if (option == 3) {
			cout << "There are " << count_primes3(n) << " prime numbers between 2 and " << n << endl;
			cout << "Approximately " << t.elapsed() << " seconds have elapsed." << endl;
		}
	}
	system("pause");
}

/*
Written Assignment:

1)
n       | is_prime1   |   is_prime2   | is_prime3 |
----------------------------------------------------
100			0.005			0.002		0.002
150			0.018			0.002		0.003
200			0.064			0.002		0.002
250			0.229			0.002		0.002
300			0.636			0.001		0.002
350			1.605			0.004		0.003
400			3.639			0.003		0.004
500			15.105			0.004		0.003
1,000						0.003		0.004
2,000						0.004		0.068
5,000						0.013		0.003
10,000						0.046		0.005
50,000						0.955		0.031
100,000						3.731		0.077
200,000						15.481		0.204
500,000									0.687
1,000,000								1.785
2,000,000								5.033
3,000,000								9.292
5,000,000								19.991

2)
is_prime2 would be O(n). Still has to check every number
is_prime3 would be O(log n) because you're square rooting it, thus getting rid of a lot of the numbers you have to check


3) Give the Big-Oh notation for the following functions:

log (n^5) = O(log (n)) ?

300 n^2 + 20 n + n^4 = O(n^4)

n * log (n+12) = O(n * log(n))

100n + 4n^2 + 12 log n = O(n^2)

log n + n/100 = O(n)

sqrt(6n) * (log n + 10) = O(n * log(n))

n + (n-1) + (n-2) + ... + 1 = O(n^2)


4) What is its running time using the Big-Oh notation, as a function of the
size n of the input, of the following codes:

a) for (i=0; i<n; i++)
for (j=0; j<n; ++j)
std::cout << "One more time!\n";

O(n^2)

b) for (i=0; i<n; i++)
for (j=0; j*j<n; ++j)
std::cout << "Processing " << i << " and " << j << "\n";

O(n * log(n))

c) while (n >= 1) {
std::cout << "Binary digit: " << n % 2 << "\n";
n /= 2;
}

O(log(n))

*/