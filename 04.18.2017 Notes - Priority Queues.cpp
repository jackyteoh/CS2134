// 04.18.2017 Notes - Priority Queues
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

template<class T>
class PQueue {
	vector<T> data;
	void percolateUp(int pos); // pos = position
	void percolateDown(int pos);
public:
	PQueue() { data.push_back(T()); } // push garbage into position zero
	int size() const { return data.size() - 1; }
	bool isEmpty() const { return data.size() == 1; }
	void push(T newdata) {
		data.push_back(newdata);
		percolateUp(data.size() - 1);
	}
	T pop();
	T top() { return data[1]; }
	void clear() { data.resize(1); }

};

template<class T>
void PQueue<T>::percolateUp(int pos) {
	if (pos > 1) { // when pos is 1, we're the root and therefore finished
		if (data[pos] < data[pos / 2])){ // we're less than our parent, so we should swap.
			swap(data[pos], data[pos / 2]);
			percolateUp(pos / 2);
		}
	}
}

template<class T>
void PQueue<T>::percolateDown(int pos) {
	if (pos * 2 >= data.size()) { // no children, return.
		return;
	}
	else if (pos * 2 + 1 == data.size()) { // pos only has one child
		if (data[pos * 2] < data[pos]) {
			swap(data[pos], data[pos * 2]);
		}
	}
	else { // pos has two children
		if (data[pos] < data[pos * 2] && data[pos] < data[pos * 2 + 1]) { // Pos is the lesser value, leave it alone
			return;
		}
		else {
			if (data[pos * 2] < data[pos * 2 + 1]) { // find the lesser of the two children
				swap(data[pos], data[pos * 2]);
				percolateDown(pos * 2);
			}
			else {
				swap(data[pos], data[pos * 2 + 1]);
				percolateDown(pos * 2 + 1);
			}
		}
	}
}

/*
percolateDown possible situations:
1) When pos has no children = done. (pos * 2 >= size)
2) When pos has one child (pos * 2 + 1 == size) -> Check the child, swap as needed
3) When pos has two children
	if (data[pos] < min(data[pos*2], data[pos*2 + 1])), when pos is less than either of its children
	else, decide which to promote (the lower one), swap, and recurse
*/

template<class T>
T PQueue<T>::pop() {
	if (data.size() <= 1) { // Trying to pop from an empty queue
		return T();
	}
	T temp = top();
	data[1] = data[data.size() - 1];
	data.pop_back();
	percolateDown(1);
	return temp;
}

int main() {
	PQueue<int> pq;
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		pq.push(rand() % 100);
	}
	while (!pq.isEmpty()) {
		cout << pq.top() << endl;
	}
}

/*
FCFS = First come first serve
Priority Queue (Binary Heap) - A data structure which returns the lowest value the lowest value element 
first (highest priority element)
Store it as a tree with the root as the lowest element
When root gets deleted, promote the lowest child
Binary Heap - Lowest value = root of tree
When we add elements, we add on lowest level from left to right

N = newly added
		x
	   / \
	 >x   >x

		1
	   / \
      3   2
	 / \  / \
    9   5 7  14
   / \ 
  11N 13

  0   1   2   3   4   5   6   7	   8N   9N   10N 11N 
| X | 1 | 3 | 2 | 9 | 5 | 7 | 14 | 11 | 13 | 10 | 4 |

4 at 11 is smaller than its parent 5 at 5. swaps.

  0   1   2   3   4   5   6   7	   8N   9N   10N 11N
| X | 1 | 3 | 2 | 9 | 4 | 7 | 14 | 11 | 13 | 10 | 5 |

When you pop the root, promote the node that was most recently added. Then from there swap down the tree to
sort it and make it full and balanced again

Parent = Node / 2
Child = Node * 2 AND (Node * 2) + 1
14 (at position 7). 7/2 = 3 (Floored) 14's parent is 2 (at 3)
3 (at 2) children at node*2 and node*2 + 1 = 4 and 5 = 9 and 5 !
*/