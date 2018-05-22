/*
Jacky Teoh - jt2908
CS 2134 - Data Structures & Algorithms
Homework 4 - Hash Tables
04.25.2017 
hw 04.cpp
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

template<class K, class V, class HF, class NE>
class STLMap;
class HashFunction;
template<class V>
class notEquals;

class HashFunction {
public:
	int hash(int x, int limit) {
		return x % limit;
	}
};

template<class V> // check if values are equal
class notEquals {
public:
	bool operator()(const V& a, const V& b) {
		return a != b;
	}
};

template<class K, class V, class HF, class NE>
class STLMap {
private:
	class Node {
	public:
		V data;
		Node* next;
		K key;
		Node(K newKey, V newData) : key(newKey), data(newData) {}
	};
	vector<Node*> vals;
	HF hashFunction;
	NE notEquals;
public:
	STLMap() { vals.resize(10); hashFunction = HF(); notEquals = NE(); }
	V& operator[](K key) {
		int index = hashFunction.hash(key, vals.size());
		if (vals[index] == nullptr) {
			vals[index] = new Node(key, V());
		}
		else {
			Node* temp = vals[index];
			while (temp != nullptr && temp->key != key) {
				temp = temp->next;
			}
			if (temp == nullptr)
				insert(key, V());
			return temp->data;
		}
	}

	void insert(K key, V value) {
		int index = hashFunction.hash(key, vals.size());
		Node* newNode = new Node(key, value);
		if (vals[index] == nullptr) {
			vals[index] = newNode;
		}
		else if (notEquals(vals[index]->data, newNode->data)){
			Node* temp2 = vals[index];
			while (temp2 != nullptr && notEquals(temp2->data, newNode->data)) {
				temp2 = temp2->next;
			}
			Node* temp = vals[index];
			vals[index] = newNode;
			vals[index]->next = temp;
		}
		else { // When checked, the values were equal, don't insert.
			return;
		}
	}

	V remove(K key) {
		int index = hashFunction.hash(key, vals.size());
		if (vals[index] == nullptr) { // Trying to delete what's not there
			return -1;
		}
		else{
			if (vals[index]->key == key) {
				V returnVal = vals[index]->data;
				Node* temp = vals[index]->next;
				delete vals[index];
				vals[index] = temp;
			}
			else {
				while (vals[index] != nullptr && vals[index]->next->key != key) {
					vals[index] = vals[index]->next;
				}
				if (vals[index] == nullptr) { // trying to delete what's not there. key doesn't exist after checking
					return -1;
				}
				else {
					V retVal = vals[index]->next->data;
					Node* temp2 = vals[index]->next->next;
					delete vals[index]->next;
					vals[index]->next = temp2;
				}
			}
		}
		return retVal;
	}
};

int main() {
	HashFunction hf;
	notEquals<int> ne;
	STLMap<int, int, HashFunction, notEquals<int>> map;
	map.insert(5, 5);
	map.insert(13, 7);
	map.insert(20, 4);
	map.insert(23, 2);
	map.insert(25, 6);
	cout << map[5] << " and " << map[25] << " and " << map[13] << " and " << map[23] << " and " << map[20];
	system("pause");
}
