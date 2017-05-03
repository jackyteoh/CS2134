// 04.06.2017 Notes - Binary Search Trees & Red-Black Trees
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

// Question 3a - Recursive
int Q3a(char* arr, char c) {
	if (*arr == '\0') {
		return 0;
	}
	if (c != *arr) {
		return 1 + Q3a(arr + 1, c);
	}
	else
		return Q3a(arr + 1, c);
}

// Question 3b - Runtime of recursive
// O(N) you check each character in the array once

// Question 5a
// push in a vector can be O(N) compared to a list which is O(1)

// Question 5b - Push & Pop
template<class T>
void push(T item) {
	data.push_back(item);
}

template<class T>
void pop() {
	data.pop_back();
}








template<class T>
class AVL;

template<class T>
class AVLNode {
	AVLNode<T>* parent, *left, *right;
	T data;
public:
	friend class AVL<T>;
	AVLNode(const T& newData = T(), AVLNode<T>* newParent = nullptr, AVLNode<T>* newLeft = nullptr, AVLNode<T>* newRight = nullptr)
		: data(newData), parent(newParent), left(newLeft), right(newRight) {}
	void calcHeight() {
		int leftHeight = -1;
		int rightHeight = -1;
		if (left != nullptr) {
			leftHeight = left->height + 1;
		}
		if (right != nullptr) {
			rightHeight = right->height + 1;
		}
		height = max(leftHeight, rightHeight) + 1;
	}
	void printInOrder() const {
		if (left != nullptr) {
			left->printInOrder();
		}
		cout << data << endl;
		if (right != nullptr) {
			right->printInOrder();
		}
	}
	int size() const {
		int leftSize = 0;
		int rightSize = 0;
		if (left != nullptr) {
			leftSize = left->size();
		}
		if (right != nullptr) {
			rightSize = right->size();
		}
		return 1 + leftSize + rightSize;
	}
	//int height() const {
	//	int leftHeight = -1;
	//	int rightHeight = -1;
	//	if (left != nullptr) {
	//		leftHeight = left->height();
	//	}
	//	if (right != nullptr) {
	//		rightHeight = right->height();
	//	}
	//	return 1 + max(leftHeight, rightHeight);
	//}
	int depth() const {
		int parentDepth = -1;
		if (parent != nullptr) {
			parentDepth = parent->depth();
		}
		return 1 + parentDepth;
	}
};


template<class T>
class AVL {
	AVLNode<T>* root;
	int size;
	AVLNode<T>* recursiveCopy(AVLNode<T>* toCopy);
	void singleCCR(AVLNode<T>*& point);
	void singleCR(AVLNode<T>*& point);
	void doubleCR(AVLNode<T>*& point);
	void doubleCCR(AVLNode<T>*& point);
	int heightDiff(AVLNode<T>* point);
	void doRotation(AVLNode<T>* point);
public:
	AVL() :size(0) { root = nullptr; }

	// Memory is created on the heap, so you need the Big 3!
	virtual ~AVL() { // Virtual allows for inheritance. ALWAYS. HAVE. VIRTUAL. BEFORE. EVERY. DESTRUCTOR.
		clear();
	}
	AVL& operator=(const BST<T>& rhs);
	AVL(const BST<T>& rhs) : root(nullptr) { *this = rhs; }

	void printInOrder() const { root->printInOrder(); }

	void insert(const T&);
	void remove(const T& toRemove) {
		BSTNode<T>* item = find(toRemove);
		if (item != nullptr) {
			remove(item);
		}
	}
	void remove(BSTNode<T>*);
	BSTNode<T>* find(const T& toFind) const;
	bool isInTree(const T& toFind) { return find(toFind) != nullptr; }
	bool isEmpty() const { return root == nullptr; }
	int getSize() const { return size; }
	void clear() { while (!isEmpty()) { remove(root); } }
};

template<class T>
BSTNode<T>* BST<T>::recursiveCopy(BSTNode<T>* toCopy) {
	if (toCopy == nullptr) {
		return nullptr;
	}
	BSTNode<T>* temp = new BSTNode<T>(toCopy->data, nullptr, recursiveCopy(toCopy->left), recursiveCopy(toCopy->right));
	if (temp->left != nullptr) {
		temp->left->parent = temp;
	}
	if (temp->right != nullptr) {
		temp->right->parent = temp;
	}
	return temp;
}

template<class T>
BST<T>& BST<T>::operator=(const BST<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	clear();
	root = recursiveCopy(rhs.root);
	size = rhs.size;
	return *this;
}

template<class T>
void BST<T>::insert(const T& toInsert) {
	size++;
	if (root == nullptr) {
		root = new BSTNode<T>(toInsert);
	}
	else {
		BSTNode<T>* temp = root;
		BSTNode<T>* prev = temp;
		while (temp != nullptr) {
			prev = temp;
			if (toInsert < temp->data) {
				temp = temp->left;
			}
			if (toInsert >= temp->data) {
				temp = temp->right;
			}
		}
		// Now temp points to nullptr and prev points to the node we want to insert onto (where we're inserting the child)
		if (toInsert < prev->data) { // Insert to the left of Prev
			prev->left = new BSTNode<T>(toInsert, prev);
		}
		if (toInsert >= prev->data) { // Insert onto the right of Prev
			prev->right = new BSTNode<T>(toInsert, prev);
		}

		while (prev != nullptr) {
			prev->calcHeight();
			if (heightDiff(prev) > 1) {
				doRotation(prev);
			}
		}
	}
}

template<class T>
BSTNode<T>* BST<T>::find(const T& toFind) const {
	BSTNode<T>* temp = root;
	while (temp != nullptr && temp->data != toFind) {
		if (toFind < temp->data) {
			temp = temp->left;
		}
		if (toFind >= temp->data) {
			temp = temp->right;
		}
	}
	return temp;
}

template<class T>
void BST<T>::remove(BSTNode<T>* toRemove) {
	if (root == nullptr) {
		return; // Remove from an empty tree ????? Can't do that.
	}
	if (toRemove->left == nullptr && toRemove->right == nullptr) { // leaf node case
		if (toRemove->parent == nullptr) { // no parent
			root = nullptr;
		}
		else if (toRemove = toRemove->parent->left) { // left child!
			toRemove->parent->left = nullptr;
		}
		else {										// Right child
			toRemove->parent->right = nullptr;
		}
		delete toRemove;
		size--;
	}
	else if (toRemove->right == nullptr) { // Has one child (left)
		if (toRemove->parent == nullptr) {
			root = toRemove->left;
		}
		else if (toRemove == toRemove->parent->left) { // We're the left child of our parent
			toRemove->parent->left = toRemove->left;
		}
		else {
			toRemove->parent->right = toRemove->left;
		}
		delete toRemove;
		size--;
	}
	else if (toRemove->left == nullptr) { // Has one child (right), almost same solution as left child only
		if (toRemove->parent == nullptr) {
			root = toRemove->right;
		}
		else if (toRemove == toRemove->parent->left) { // We're the left child of our parent
			toRemove->parent->left = toRemove->right;
		}
		else {
			toRemove->parent->right = toRemove->right;
		}
		delete toRemove;
		size--;
	}
	else { // Has two children ! Full node !
		BSTNode<T>* temp = toRemove->right;
		while (temp->left != nullptr) {
			temp = temp->left;
		}
		toRemove->data = temp->data;
		remove(temp);
	}
}

template<class T>
void AVL<T>::doubleCCR(AVLNode<T>*& point) {
	singleCR(point->right);
	singleCCR(point);
}

template<class T>
void AVL<T>::doubleCR(AVLNode<T>*& point) {
	singleCCR(point->left);
	singleCR(point);
}

template<class T>
void AVL<T>::singleCR(AVLNode<T>*& point) {
	AVLNode<T>* grandparent = point;
	AVLNode<T>* parent = point->left;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->left = parent->right;
	parent->right = grandparent;
	if (grandparent->left != nullptr) { // If we now have a left child, update its parent position
		grandparent->left->parent = grandparent;
	}
	if (parent->parent == nullptr) { // If we were the root, update the root
		root = parent;
	}
	else if (parent->parent->left == grandparent) {
		parent->parent->left = parent;
	}
	else {
		parent->parent->right = parent;
	}
	grandparent->calcHeight();
	parent->calcHeight();
}

template<class T>
int AVL<T>::heightDiff(AVLNode<T>* point) {
	int leftHeight = -1;
	int rightHeight = -1;
	if (point->left != nullptr) {
		leftHeight = point->left->height;
	}
	if (point->right != nullptr) {
		rightHeight = point->right->height;
	}
	return (abs(leftHeight - rightHeight));
}

template<class T>
void AVL<T>::doRotation(AVLNode<T>* point) {
	int leftChild = -1;
	int rightChild = -1;
	if (point->left != nullptr) {
		leftChild = point->left->height;
	}
	if (point->right != nullptr) {
		rightChild = point->right->calcHeight;
	}
	if (leftChild > rightChild) { // CR but is it single or double?
		int leftGC = -1;
		int rightGC = -1;
		if (point->left->left != nullptr) {
			leftGC = point->left->left->height();
		}
		if (point->left->right != nullptr) {
			rightGC = point->left->right->height();
		}
		if (leftGC > rightGC) { // Single rotation
			singleCR(point);
		}
		else { 
			doubleCR(point);
		}
	}
	else {
		int leftGC = -1;
		int rightGC = -1;
		if (point->right->left != nullptr) {
			leftGC = point->right->left->height();
		}
		if (point->right->right != nullptr) {
			rightGC = point->right->right->height();
		}
		if (leftGC > rightGC) { // double rotation

		}
	}
}

int main() {

}

/*
AVL Tree is constantly checking its height so that nothing is out of balance.
Binary Search Tree with the added property that for every node, the height of the left and right subtrees
can differ by no more than 1.
Height null = -1
	2 H = -1		2
	 \				 \
	  7 H = 0		  7
	                   \
					    9 H = 1, NOT AN AVL TREE. LEFT SUBTREE H = -1
Single Counter Clockwise Rotation
2				7
 \			   / \
  7    =>     2   9
   \ 
    9

1				2 H = -1		AVL TREE WORKS.
 \		  	   / \
  2    =>     1   3 H = 0
   \               \
    3               4 H = 1

	2						4
   / \					   / \
  1   4					  2   5
     / \		=>	     / \   \
	3   5				1   3	6
	     \
		  6
The Height at 6 is 2 whereas the Height of 1 is 0. Therefore, there is more than 1 between the heights, need to AVL.
When you make 4 the Root, 3 is on the left of 4 initially, but then 2 becomes the left of 4.
Since 2 < 3 and 4 > 3, it is okay to put 3 on the right of 2 since it is still less than 4.

Four possible situations for AVL:
1) 1			Single Counter-Clockwise Rotation		 2
  / \													/ \
 A	 2					==========>					   1   3
	/ \												  / \  / \
   B   3											 A  B C   D
	  / \
     C   D

2)		3		Single Clockwise Rotation				2
       / \											   / \
	  2   D											  1   3
	 / \			   ===========>					 / \  /\
	1   C											A   B C D
   / \
  A   B

3)	1		SCR			1		SCCR		2
   / \				   / \				   / \
  A	  3				  A   2				  1   3
	 / \				 / \			 / \ / \
	2   D				B   3			A  B C  D
   / \					   / \
  B   C					  C   D

Two stop problem, we need to temporarily make it easier for us to solve. DOUBLE CCR (Single + Single)
SCR = Single Clockwise Rotation
SCCR = Single Counter-Clockwise Rotation
	10			Step 1:		10				Step 2:			15
	  \			SCR			  \				SCCR		   /  \
	   20		=====>		   15			======>		 10    20
	   /						\
	  15						 20
		Balance it so we can use SCCR			Use SCCR

4)	3		DCR		2
   / \			   / \
  1   D			  1   3
 / \			 / \ / \
A   2			A  B C  D
   / \
  B   C

Double CR (Single CR + Single CR)
Single CCR (Left Child)
Single CR (Parent)

2 Left Insertions or 2 Right Insertions (Situations 1 and 2) = Single 
1 Left Insertion and 1 Right Insertion OR 1 Right Insertion and 1 Left Insertion (Situations 3 and 4) = Double

(RB Tree) = Red-Black Tree
Red-Black Trees: BINARY SEARCH TREES ONLY. LAWS CANNOT BE VIOLATED.
1) Every node has a color, red or black.
2) Root is always black.
3) If a node is red, its children must be black.
4) Every path from a node to a null must traverse the same number of black nodes!
^ Laws are useless in telling you how to implement a Red-Black tree
Red nodes cannot have red children. RED NODES CANNOT HAVE RED CHILDREN
Black nodes can have either black or red children.

How to Implement:
1) New nodes are always colored red.
	a) Parent is Black = done.
	b) Parent is red = problem.
		i) if Uncle is Black (null is black)
			I) If new node is outside - Single rotation (Grandparent)
			II) If new node is inside - Double rotation(Grandparent)
		ii) If uncle is red - AVOID/IMPOSSIBLE
2) As you go DOWN to find the insertion point, if you encounter a black parent with two red children, recolor
to red parent with two black children. If grandparent is red, rotate.

You can produce a RB Tree that is not balanced in AVL. But balanced in RB.
	B			R
   / \		   / \
  R   R		  B   B
However this can cause a problem if the parent of the Red is a Red, then you have to go through the implementation again
until it's completely correct.
GB = Grandparent Black
GR = Grandparent Red
PB = Parent Black
PR = Parent Red
UB = Uncle Black
UR = Uncle Red
NR = New Red
NB = New Black

		GB						PB
	   / \				       / \
	  PR   UB				  NR   GR
	 / \  / \		=>		 / \ / \
	NR  C d   e				a  b c  UB
	/ \						       / \
  a   b							  d   e


		GB						NB
	   /  \						/\
      PR   UB				  PR   GR
	 /  \  / \		=>		 / \  /  \
    a   NR d  e				a  b  c   UB
	   / \							  / \
	  b   c							 d   e

Red-Black Tree Visual
*/