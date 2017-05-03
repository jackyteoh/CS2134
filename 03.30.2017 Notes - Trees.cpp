// 03.30.2017 Notes - Trees
// 04.13.2017 Thursday, Exam 4 - 
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
class BTreeNode {
private:
	BTreeNode<T>* parent;
	BTreeNode<T>* left;
	BTreeNode<T>* right;
	T data;
public:

};

/*
Queue
A
A BC
BC D
CD EF
DEF GH
EFGH IJ
FGHIJ
*/

// Code for Level Order Traversal
Treenode<T>::LevelOrder() {
	Queue<Treenode<T>*> q;
	q.push(root);
	while (!(q.isEmpty())) {
		cout << q.top().data;
		if (q.top().left) {
			q.push(q.top().left);
		}
		if (q.top().right) {
			q.push(q.top().right);
		}
		q.pop();
	}
}

Treenode<T>::inOrder() {
	if (left) {
		left->inOrder();
	}
	cout << data;
	if (right) {
		right->inOrder();
	}
}

Treenode<T>::preOrder() {
	cout << data;
	if (left) {
		left->preOrder();
	}
	if (right) {
		right->preOrder();
	}
}

Treenode<T>::postOrder() {
	if (left) {
		left->postOrder();
	}
	if (right) {
		right->postOrder();
	}	
	cout << data;
}

int main() {

}

/*
Directory Tree:
C:\
Program Files
	- Microsoft Office
Users
	- Bob
		- Documents
		- Videos
			- Legal
			- Illegal
		- Music
Windows
	- Temp
	- System

Trees:
A hierarchial data structure where every node has one and only one parent, except for the root node. (Highest node)
Definitions:
	Branch - A segment of the larger tree
	Root - The only node on the tree with no parent (Highest node(?))
	Size - Count of number of nodes on the tree. Size of tree == Size of root node.
		   Size of a node is 1 greater than the sum of the size of all its children (children + node)
	Height - Distance between the root node and its FARTHEST child (can count number of links between the nodes)
			 Height of a single node = 0 
	Depth - Number of links from the node to the root
	Leaf - A node with no children
	Full Node - A node with the maximum number of children
	Sibling - Nodes share the parent
	Uncle - Parent's sibling
	Cousins - Parent's sibling's children
	Descendant - Anyone below you
	Ancestor - Anyone above you

		.
	/	|	   \
  com  net       edu
  / \   |        /  \
google verizon  nyu  adelphi
  |              |
 www		engineering

	B
  /  \
 A    C
/ \  /  \
D E  F   G
B = A + C

Tree B is the same as Tree A. The trees lend themselves through recursion(?) 
Likewise Trees B = A = C = D = E = F = G

Parent Multi=child (PMC) - Vector
Parent
Data
Vector of children

Parent-Child-Sibling (PCS) - List
Parent
Data
Child
Sibling
Constant time to access the child, linear time to access the siblings(?)

There are two mechanisms to search a tree:
1) Depth-First Search (DFS) - Go down to the lowest level (of each child of the root), and work our way back up to the root
   and down each child, Usually the left most child first (Pre order traversal)
2) Breadth-First Search (BFS) - Go down to the first (left) child, and then check the siblings and then check the child of 
   the first child, and check siblings of that child, etc.
Each method still checks every single node, but there's just a different order to process each node.

Binary Trees - A tree with at most, TWO children. 
Parent
Data
Node* Left
Node* Right

		A
	   / \
	  B   C
	 /   /  \
    D   E    F
   /\  / \   
  G  H I  J 

ALL DEPTH FIRST SEARCHES:
Pre order traversal: A B D G H C E I J F (TLR) (This then Left then Right)
In order traversal: G D H B A I E J C F (LTR) (Left then This then Right)
Post order traversal: G H D B I J E F C A (LRT) (Left then Right then This)
Level Order Traversal: A B C D E F G H I J

Expression Tree:
3 * (4 + 5)
	 *
	/ \
   3   +
      / \
	 4   5
In Order Traversal: 3 * (4 + 5)

Binary Search Tree
A Binary tree where all the left children have a value less than the node, and all right children have values >= than the node.
		10
	    / \
	   5   20
	   \   /
	    7  15

*/