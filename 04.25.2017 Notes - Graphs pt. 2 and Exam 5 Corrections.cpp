// 04.25.2017 Notes - Exam 4 Corrections & Graphs pt. 2
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

struct Node {
	int data;
	Node* right;
	Node* left;
};

// Question 1A
int count(Node* ptr) {
	Node* start = ptr;
	int count = 1;
	while (ptr->right != start) {
		count++;
		ptr = ptr->right;
	}
	return count;
}

// Question 1B
int count(Node* ptr) {
	int count = 1;
	Node* temp = ptr->left;
	while (temp != nullptr) {
		count++;
		temp = temp->left;
	}
	while (ptr->right != nullptr) {
		count++;
		ptr = ptr->right;
	}
	return count;
}

// Question 2
template<class T>
T findMedian(Node* given) { // assuming the given Node is the HEADER node.
	if (given->next == nullptr) {
		return 0;
	}
	if (given->next->next == nullptr) {
		return given->next->data;
	}
	Node* counter = given->next;
	int size = 0;
	for (counter; counter != nullptr; counter = counter->next) {
		size++;
	}
	counter = given->next;
	while ((size /= 2) != 0) {
		counter = counter->next;
	}
	return counter->data;
}

// Question 3a

// Question 5a
int nodeSum(Node* ptr) {
	if (ptr == nullptr) {
		return 0;
	}
	return ptr->data + nodeSum(ptr->left) + nodeSum(ptr->right);
}

// Question 5b
int findMax(Node* ptr) {
	while (ptr->right != nullptr) {
		ptr = ptr->right;
	}
	return ptr->data;
}

// Question 5c
int countPartial(Node* ptr) {
	if (ptr == nullptr) {
		return 0;
	}
	if ((ptr->left == nullptr && ptr->right != nullptr) || (ptr->left != nullptr && ptr->right == nullptr)) {
		return 1 + countPartial(ptr->left) + countPartial(ptr->right);
	}
	else {
		return countPartial(ptr->left) + countPartial(ptr->right);
	}
}

int main() {

}

/*
Unweighted Single Source Shortest Path Algorithm (?)
CAN'T HAVE NEGATIVE WEIGHTED EDGES
	    NY/0							SEA/145						MIA/150
	      |								/     \						/	   \
	   CHI/75					    MIA/150    MIA/300			SFO/170	   MIA/300
	  /     \				=>       /						=>    /
  MIA/150    SEA/145			  SFO/170					   LA/350
	/            
MIA/300         

		SFO/170							LA/195
		/	  \				=>			
	 LA/350	  LA/195

NY to
CHI 75
MIA 150
SEA 145
SFO 170
LA 195

Dijkstra's Algorithm - Weighted single source shortest path algorithm BREADTH FIRST SEARCH

*/