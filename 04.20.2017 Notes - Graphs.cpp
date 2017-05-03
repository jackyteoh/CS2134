// 04.20.2017 Notes - Graphs
// Homework 4 posted due 04.25.2017
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <ctime>

using namespace std;

// Heap sort O(n log n)
// push keeps everything in sorted order, we don't need to keep it in sorted order
// maintains sorting throughout the iteration
// Uses twice the amount of memory, but does it in O(n log n)
for (T item : v) {
	h.push(item);
}

for (int i = 0; !(h.isEmpty()); i++) {
	v[i] = h.pop();
}

int main() {

}

/*
Graph

Directed Weighted Graph

MSP
|  \ 10
|   OSH
|	  \ 30
|	   APL
|	     \ 30
---------CHI

CHI -> APL = $30
APL -> OSH = $30
OSH -> MSP = $10
Not bidirectional
MSP -> CHI = $120
CHI -> MSP = $150
CHI -> OSH = $200

Graph - a data structure with vertices interconnected with edges.
Directed Graph - A graph where the edges can only be travelled in one direction
Weighted Graph - Each edge has a "cost"/weight associated with using that edge
Adjacency List - 
2---->1
|    /^
|  /  |
v/    |
3---->4

1 -> 3 -> nullptr
2 -> 1 -> nullptr
3 -> 2 -> 4 -> nullptr
4 -> 1 -> nullptr

Adjacency Matrix - 1 = there's a path, 0 = there's no path
   1   2   3   4
1  1   0   1   0
2  1   1   0   0 
3  0   1   1   1
4  1   0   0   1
Assume everything is reflexive (can get to themselves) since you're already there

Sparse Graph - 
o---o
|   |
o---o
Dense Graph - Number of edges approaches v^2, can never get to v^2, but can get to v^2 - v. This is known as a meshed graph
Meshed Graph - Every node is interconnected with every other node.
Dense Graph prefers an adjacency matrix
Sparse Graph prefers an adjacency list.
*/