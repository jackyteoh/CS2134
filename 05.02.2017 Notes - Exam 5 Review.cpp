// 05.02.2017 Notes - Exam 5 Review
// EXAM 5 NEXT THURSDAY, 05.04.2017 - GRAPHS, PRIORITY QUEUES, HASH TABLES
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

int main() {

}

/*
Priority Queue in a vector
0 index not used
parent = index/2
child = index*2 OR index*2 + 1
in tree Left to right has to be filled, is always a full tree

Primary and Secondary Indexing is going to be on the test
Adding something onto a hash table that's partially full
WILL BE ON THE TEST

How dense should a graph be before we use an adjacency matrix
Adjacency list is pretty light
Once you're over 50% v^2 as edges, 5 vertices and you have > 12 edges, use matrix

Primary/Secondary Indexing
Hash Table
hash function = n % 10
22, 24, 35, 13, 92
 0  1  2  3  4  5  6  7  8  9 
|  |  |22|13|24|35|92|  |  |  |
Since 92 % 10 is 2, but there's arleady 22 at 2, you go to the next index and see if that's empty
Keep going until you find an empty index in order to place 92. (index 6)
Primary indexing (h, h + 1, h + 2, h + 3, h + 4, h + 5, etc.)
Secondary indexing (h, h + 1, h + 4, h + 9, h + 16, etc.)
When you delete from a hash table, there is a secondary array of bools called deleted
when you "remove" something from the hash table, you change the bool to deleted
in this case if you would hash 92, you check index 2 and see its deleted, you check the next ones
if you check and its not deleted and at index 2 its not 92, it'll just stop checking the hash table

Separate Chain Hashing
hash function = n % 10 (n % size)
22, 24, 35, 13, 92
0  1  2  3  4  5  6  7  8  9
|  |  |  |  |  |  |  |  |  |  |
       22 13 24 35
	   92
When your chain gets too long (around 5) resize your table/map (double it) and therefore doubles your 
size, changes your hash function. (n % 2*size) Therefore rehashing changes your entire table/map


*/