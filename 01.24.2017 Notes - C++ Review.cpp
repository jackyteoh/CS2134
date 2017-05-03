// 01.24.2017 Notes - C++ Review
#include <iostream>

using namespace std;

/*
Pointers
Big 3
Arrays
File I/O
*/

int main() {
	int x = 100;
	int* y = &x;
	*y = 200;

	cout << x << endl; // Prints 200
}

/*
Pointers
Three possible errors with pointers:

1) Dereferencing null (DEREF NULL), program crashes. Illegal to access 0x00000.
int* x = nullptr;
cout << *x;

2) Double Delete, also crashes program.
delete x;
delete x; <-- Can't delete the same memory space again if it's already been deleted.
int* x = new int;
int* y = x; <-- points to what x is pointing to, the new int.
delete x; <-- deletes the new int that x is pointing to
delete y; <-- Only creating one new item on the heap, x = new int, so you only need to delete once.
Therefore you can't delete y because it has already been deleted.

3) Memory Leak / Garbage on the heap.
Memory leak = memory left on the heap that you can no longer access.
int* x = new int; // garbage on the heap
x = new int;
delete x; <-- the first new int is still there that we can't access. Therefore memory leak.
Memory leaks don't happen instantaneously, happens over time, then crashes.
*/