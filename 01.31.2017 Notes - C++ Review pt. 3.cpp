// 01.31.2017 Notes - C++ Review pt. 3 (STL)
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

template <class T, class S> // Doubly templated data structure
class Pair {
public:
	T first;
	S second;
};

int main() {
	Pair<string, int> p;
	p.first = "Daniel";
	p.second = 100;
	Pair<Pair<string, int>, Pair<char, float>> p2; // A pair of pairs
	p2.first.first = "John";

	int x = 100;
	int y = 10;
	int z = 5;
	cout << (x > 5) ? (x > y) ? x : ((y > z) ? y : z) : y;

	set<int> s;
	for (int i = 0; i < 100; i++) {
		s.insert(rand() % 1000);
	}
	for (int i : s) {
		cout << i;
	}

	map<string, int> m;
	m.insert(Pair<string, int>("John", 100));
	m.insert(Pair<string, int>("David", 90));
	m.insert(Pair<string, int>("Albert", 80));

	m["Daniel"] = 105; // Another way to insert keys and values.

	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++) {
		cout << i->first << " = " << i->second << endl;
	}

	cout << m["Daniel"] << endl; // Prints 105
	cout << m["Betty"]; // Prints out garbage
	cout << m.size(); // Prints out 5

	if (m.find("Betty") != m.end()) {
		cout << m["Betty"];
	}
}

/*
Vectors:
Can access any point inside the vector (Random Access & Random Access Iterators)
Can only insert/remove at the end of the vector

List:
Doesn't have random access, instead has Sequential access
Insertions/Removals at any point inside the list

cout << (x < y) ? x : y;
if (x < y){
	cout << x;
}
else{
	cout << y;
}

Sets:
Keeps your data in "sorted" order
Fast Insertions
Fast Searches
Random Insertion Points
Objects need to be able to be compared with less than operators (to sort)
Does not keep duplicates. You could insert 100 and possibly get back less than 100.

Multisets:
Same properties as a set, except it allows duplicates

Map:
Ties together a set and a pair
Pair's first is a "key"
Pair's second is a "value"
Maps stores the keys in sorted order.
*/