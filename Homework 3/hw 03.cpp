/*
Jacky Teoh - jt2908
CS2134 - Data Structures & Algorithms : Homework 3
03.27.2017
hw 03.cpp
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Flight {
public:
	int flightNumber;
	string flightDeparture;
	string flightArrival;
	int flightTime;
	Flight(int n, string d, string a, int t) : flightNumber(n), flightDeparture(d), flightArrival(a), flightTime(t) {}
	friend ostream& operator<<(ostream& os, const Flight& rhs) {
		os << rhs.flightNumber << " " << rhs.flightDeparture << " " << rhs.flightArrival << " " << rhs.flightTime;
		return os;
	}
};

class equalByDeparture {
public:
	bool operator()(const Flight& lhs, const string& rhs) {
		return lhs.flightDeparture == rhs;
	}
};

class equalByDestination {
public:
	bool operator()(const Flight& lhs, const string& rhs) {
		return lhs.flightArrival == rhs;
	}
};

template<class F, class S, class T>
vector<F> returnSatisfy(vector<F>& v, S comparator, T fixed) {
	vector<F> retval;
	for (int i = 0; i < v.size(); i++) {
		if (comparator(v[i], fixed) == true) {
			retval.push_back(v[i]);
		}
	}
	return retval;
}

template<class F>
void outdegree(vector<F>& flights) {
	vector<F> maxOut = returnSatisfy(flights, equalByDeparture(), flights[0].flightDeparture);
	for (int i = 1; i < flights.size(); i++) {
		vector<F> check = returnSatisfy(flights, equalByDeparture(), flights[i].flightDeparture);
		if (maxOut.size() <= check.size()) {
			maxOut = check;
		}
	}
	cout << "The city with the most departures is: " << maxOut[0].flightDeparture << ", and has an outdegree of: " << maxOut.size() << endl;
	cout << "The flights that are leaving " << maxOut[0].flightDeparture << " are: " << endl;
	for (int j = 0; j < maxOut.size(); j++) {
		cout << maxOut[j] << endl;
	}
}

int main() {
	vector<Flight> flights;

	ifstream ifs("HW3Data.txt");
	if (ifs) {
		cout << "This file has successfully opened!" << endl;
	}
	else {
		cout << "There was an error opening this file, please try again." << endl;
	}

	int number;
	string depart;
	string arrive;
	int time;

	while (ifs >> number >> depart >> arrive >> time) {
		flights.push_back(Flight(number, depart, arrive, time));
	}

	//vector<Flight> returned = returnSatisfy(flights, equalByDestination(), "KJFK");
	//for (int i = 0; i < returned.size(); i++) {
	//	cout << returned[i] << endl;
	//}

	outdegree(flights);

	system("pause");
}