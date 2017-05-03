// 04.04.2017 Notes - Binary Search Trees
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

template<class T>
class BST;

template<class T>
class BSTNode {
	BSTNode<T>* parent, *left, *right;
	T data;
public:
	friend class BST<T>;
	BSTNode(const T& newData = T(), BSTNode<T>* newParent = nullptr, BSTNode<T>* newLeft = nullptr, BSTNode<T>* newRight = nullptr)
		: data(newData), parent(newParent), left(newLeft), right(newRight) {}
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
	int height() const {
		int leftHeight = -1;
		int rightHeight = -1;
		if (left != nullptr) {
			leftHeight = left->height();
		}
		if (right != nullptr) {
			rightHeight = right->height();
		}
		return 1 + max(leftHeight, rightHeight);
	}
	int depth() const {
		int parentDepth = -1;
		if (parent != nullptr) {
			parentDepth = parent->depth();
		}
		return 1 + parentDepth;
	}

};

template<class T>
class BST {
	BSTNode<T>* root;
	int size;
	BSTNode<T>* recursiveCopy(BSTNode<T>* toCopy);
public:
	BST() :size(0) { root = nullptr; }

	// Memory is created on the heap, so you need the Big 3!
	virtual ~BST() { // Virtual allows for inheritance. ALWAYS. HAVE. VIRTUAL. BEFORE. EVERY. DESTRUCTOR.
		clear();
	}
	BST& operator=(const BST<T>& rhs);
	BST(const BST<T>& rhs) : root(nullptr) { *this = rhs; }

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
	if (toCopy == nullptr){
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
			prev->left = new BSTNode<T> (toInsert, prev);
		}
		if (toInsert >= prev->data) { // Insert onto the right of Prev
			prev->right = new BSTNode<T> (toInsert, prev);
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

int main() {

}

/*
35, 21, 96, 13, 44, 9, 14
Only one binary search tree you can create out of this group of numbers
Reacting with each insertion, check if greater/less than first num(root)
Runtimes: Same runtimes as a set !!!
Insertion of an element: O(log n)
Search for an element:   O(log n)
Removal of an element:   O(log n)
Binary Trees are sets

			35
		   /  \
		  21   96
		 /    /
		13   44
	   / \
	  9  14

		num
	   /   \
    < num    >= num

It's possible the runtimes can be different
2, 7, 9, 13, 54, 96, 99
2
 \
  7 
   \
    9
     \
      13
       \ 
       54
         \
          96
           \
            99
Pretty much a linked list.
Everything becomes O(n)

Remove function:
1) Remove a leaf
	10				10
   /  \            /  \
  5    15      nullptr  15
(remove 5)
	a) remove pointer from parent
	b) delete the node

2) Remove a node with 1 child
	5 (parent)			5 (parent)
	 \					 \
	  10 (remove)		  15 (child)
	    \
		 15 (child)
a) Change parent to point to child
b) delete the Node

3) Remove a node with 2 children (A full node in BST)
		10 (remove)			12
	   /  \				   / \
	  5    15             5   15
    /  \   / \           / \    \
   1   7  12   20       1   7    20
a) Promote the max of the left subtree or the min of the right subtree
b) Delete the one you promoted

AVL Trees:
Binary Search Tree with the added property that for every node, the height of the left and right subtrees
can differ by no more than 1.
Height null = -1
	2				2
H=-1 \				 \
	  7 H = 0		  7
	                   \
					    9 H = 1, NOT AN AVL TREE. LEFT SUBTREE H = -1
Single Counter Clockwise Rotation
2				7
 \			   / \
  7    =>     2   9
   \ 
    9
*/