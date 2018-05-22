#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
	Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
	int data;
	Node* link;
};

void listInsertHead(int entry, Node*& headPtr) {
	headPtr = new Node(entry, headPtr);
}

void spliceList(Node* before, Node* another) {
	Node* temp = before->link;
	before->link = another;
	while(another->link != nullptr) {
		another = another->link;
	}
	another->link = temp;
}

void displayList(Node* first) {
	Node* h = first;
	while (h != nullptr) {
		cout << h->data << ' ';
		h = h->link;
	} cout << endl;
}

Node* matchList(Node* firstList, Node* secondList) {
	Node* previous = secondList;
	int length = 1;

	Node* counter = secondList;
	while (counter->link != nullptr) {
		length++;
		counter = counter->link;
	}

	while (firstList != nullptr) {
		int matched = 0;
		Node* previous = firstList;
		Node* something = firstList;

		something = previous;
		while (secondList != nullptr) {
			if (something == nullptr) {
				return nullptr;
			}
			if (something->data == secondList->data) {
				matched++;
				secondList = secondList->link;
				something = something->link;

				if (matched == length) {
					return firstList;
				}
			}
			else {
				break;
			}
		}

		firstList = previous->link;
	}
	cout << "Failed to match" << endl;
	return nullptr;
}

int main() {
	cout << "Program 1:" << endl;

	Node L1d(1);
	Node L1c(9, &L1d);
	Node L1b(7, &L1c);
	Node L1a(5, &L1b);

	cout << "L1: ";
	displayList(&L1a);

	Node L2c(2);
	Node L2b(3, &L2c);
	Node L2a(6, &L2b);

	cout << "L2: ";
	displayList(&L2a);

	cout << "Target: ";
	displayList(&L1b);

	cout << "Splicing L2 at target in L1" << endl;
	cout << "L1: ";
	spliceList(&L1b, &L2a);
	displayList(&L1a);
	cout << "L2: ";
	displayList(&L2a);


	cout << endl << "Part two: " << endl;
	cout << "Target: ";
	Node L3i(6);
	Node L3h(5, &L3i);
	Node L3g(4, &L3h);
	Node L3f(2, &L3g);
	Node L3e(3, &L3f);
	Node L3d(2, &L3e);
	Node L3c(3, &L3d);
	Node L3b(2, &L3c);
	Node L3a(1, &L3b);
	displayList(&L3a);

	Node L4a(1);

	Node L5b(9);
	Node L5a(3, &L5b);

	Node L6b(3);
	Node L6a(2, &L6b);

	Node L7d(6);
	Node L7c(5, &L7d);
	Node L7b(4, &L7c);
	Node L7a(2, &L7b);

	Node L8d(4);
	Node L8c(2, &L8d);
	Node L8b(3, &L8c);
	Node L8a(2, &L8b);

	Node L9c(7);
	Node L9b(6, &L9c);
	Node L9a(5, &L9b);

	cout << endl << "Attempt Match: ";
	displayList(&L4a);
	displayList(matchList(&L3a, &L4a));
	cout << endl << "Attempt Match: ";
	displayList(&L5a);
	displayList(matchList(&L3a, &L5a));
	cout << endl << "Attempt Match: ";
	displayList(&L6a);
	displayList(matchList(&L3a, &L6a));
	cout << endl << "Attempt Match: ";
	displayList(&L7a);
	displayList(matchList(&L3a, &L7a));
	cout << endl << "Attempt Match: ";
	displayList(&L8a);
	displayList(matchList(&L3a, &L8a));
	cout << endl << "Attempt Match: ";
	displayList(&L9a);
	displayList(matchList(&L3a, &L9a));

	system("pause");
}