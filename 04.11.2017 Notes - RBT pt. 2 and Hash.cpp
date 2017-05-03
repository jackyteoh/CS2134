// 04.11.2017 Notes - Red-Black Trees pt. 2 and Hash Tables
// Thursday, 04.13.2017 EXAM 4 - Linked Lists, Trees, Binary Search Trees
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

int hash(int x, int limit) {
	return x % limit;
}

int main() {

}

/*

		20B						20B																		20B
		/ \						/\																		/\
	  10B  30B				  5B  30B																   5R 30B
      /				====>    / \			=====> if you insert another on the left side of 20		   /\
     5R					    2R  10R																	 2B	 10B
	 /																								  \
    2R																								   NR

NULL IS A BLACK NODE
2'S UNCLE IS BLACK (10's right is null)
Left-Left = Single rotation
left = clockwise rotation
5 becomes new root
2 and 10 become children

If the parent was a red node and the sibling is a black node
you can recolor the parent to black, and recolor the sibling to red
keeps the number of black nodes on the subtree the same
Problem is when the parent is already black, you have to make the parent double black, but you can't (?)
You have to push the black up the tree. IF the parent is double black, you make the parent's parent black and the parent to red
and the sibling to red (?)

Red-Black Tree Demo - First Link - Great tool for visualization


Hash Functions + Tables
Hashfunction is a function that takes in some object and produces for that object a unique number that's always consistent
If you give input x and call the hashfunction, will give you a hash for y. No matter how many times you call the 
hashfunction with x, you will always get y back.
If you pass in a string, you will get in a 32 bit integer for that string, hashed.
y = hash(x); will always equal the hash of x, will always be the same y.

array of size 10
insert(25) => hash(25, 10);
inserts 25 at index 5
inserting = constant time.
Hash = constant time access to data structure
insert(33) => hash(33, 10); => 33 at index 3
insert(15) => hash(15, 10); => also yields 5, 25 is already at index 5. HASH COLLISION

Primary Indexing:
If hash(n) is occupied: store at hash(n) + 1. If hash(n) + 1 is occupied, store at hash(n) + 2, and so on.
Relying on the fact that the array has empty spaces. 
Hashtable needs to have empty spaces (at least 20% empty).
We create an accessory array for booleans and call it deleted. If we were to delete one element in the array, 
we wouldn't actually delete it, but mark it as deleted in the boolean. Therefore we can still search
for an element that tried to get stored in that spot but had to be stored in hash(n) + 1 or further on.
result: Primary Clustering

Secondary Indexing:
h, h + 1, h + 4, h + 9, h + 16, ... etc. (squared)
result: Secondary Clustering (doesn't solve the issue)

Solution: Separate Chain Hashing
 0  1  2   3  4  5  6  7  8  9
|  |  |  |  |  |  |  |  |  |  |
           v    v   v
		   33   25  46
		        v
				15
You have to keep track of how many items are on each chain.
Once you cross 5 chains, you have to change the size of the vector, take everything out of the vector and rehash it all
O(n) runtime.
Resize = new limit. size 10 -> size 11
hash(int x, 11);
 0  1  2  3  4  5  6  7  8  9  10
|  |  |  |  |  |  |  |  |  |  |  |
 v     v  v  v
33    46 25  15

Now doesn't have max separate chain hashing.

vector<list<T>> data;
*/