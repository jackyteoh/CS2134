// 04.27.2017 Notes - Graphs pt. 3
// Exam 5 05.04.2017 - Graphs, Priority Queues, Hash Tables
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <functional>

using namespace std;

struct Edge { //an edge is made up of a destination and a cost
	int dest;
	int cost;
};

class Graph {
	map<string, int> vertexNames;
	vector<list<Edge>> edges; // Each Edge in the list has a destination and a cost
	int getVertexIndexByName(string name) const {
		map<string, int>::const_iterator i = vertexNames.find(name);
		if (i == vertexNames.end()) // If the place doesn't exist, return -1
			return -1;
		return i->second; // Else, return the value (cost) to get to that destination
	}
	string getVertexNameByIndex(int index) const {
		for (pair<string, int> vertex : vertexNames)
			if (index == vertex.second)
				return vertex.first;
		return "";
	}

public:
	void addVertex(string newName);
	void addEdge(string source, string dest, int cost);
	void addBidirectionalEdge(string source, string dest, int cost) {
		addEdge(source, dest, cost);
		addEdge(dest, source, cost);
	}
	int countVertices()const { return vertexNames.size(); }
	int countEdges()const;
	void printGraph() const;
	map<string, int> dijkstra(string source);
};

bool operator<(const Edge& lhs, const Edge& rhs) { //has to be overloaded so priority_queue can sort
	return lhs.cost < rhs.cost;
}

bool operator>(const Edge& lhs, const Edge& rhs) { //has to be overloaded to priority_queue can sort
	return lhs.cost > rhs.cost;
}

map<string, int> Graph::dijkstra(string source) {
	map<string, int> result;
	int sourceIndex = getVertexIndexByName(source);
	if (sourceIndex == -1)
		return result;
	for (pair<string, int> p : vertexNames)
		result[p.first] = INT_MAX; //initialize all distances to infinity
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	result[source] = 0;
	Edge temp;
	temp.dest = sourceIndex;
	temp.cost = 0;
	pq.push(temp);
	while (!pq.empty()) {
		int topVertex = pq.top().dest;
		int topCost = pq.top().cost;
		if (topCost == result[getVertexNameByIndex(topVertex)]) {
			for (Edge e : edges[topVertex]) {
				string destName = getVertexNameByIndex(e.dest);
				int destIndex = e.dest;
				int totalCost = topCost + e.cost;
				if (result[destName] > totalCost) { //we found a better route!
					result[destName] = totalCost;
					temp.dest = destIndex;
					temp.cost = totalCost;
					pq.push(temp);
				}
			}
		}
		pq.pop();
	}
	return result;
}
void Graph::addEdge(string source, string dest, int cost) {
	int sourceIndex = getVertexIndexByName(source);
	int destIndex = getVertexIndexByName(dest);
	if (sourceIndex == -1 || destIndex == -1) //if one index doesn't exist!
		return;
	for (Edge& e : edges[sourceIndex])
		if (e.dest == destIndex) {
			e.cost = cost; //edge already exists, update the cost and leave
			return;
		}
	Edge temp;
	temp.dest = destIndex;
	temp.cost = cost;
	edges[sourceIndex].push_back(temp);
}
void Graph::printGraph() const {
	for (pair<string, int> vertex : vertexNames) {
		cout << vertex.first << ": ";
		int vertexIndex = vertex.second;
		for (Edge e : edges[vertexIndex])
			cout << "(" << getVertexNameByIndex(e.dest) << "," << e.cost << "),";
		cout << endl;
	}
}

int Graph::countEdges()const {
	int count = 0;
	for (int i = 0; i < edges.size(); i++)
		count += edges[i].size();
	return count;
}

void Graph::addVertex(string newName) {
	if (getVertexIndexByName(newName) != -1) //This vertex already exists
		return;
	int vertexNumber = countVertices();
	vertexNames[newName] = vertexNumber;
	edges.resize(vertexNumber + 1);
}


int main() {
	Graph g;
	g.addVertex("NY");
	g.addVertex("MIA");
	g.addVertex("CHI");
	g.addVertex("SEA");
	g.addVertex("SFO");
	g.addVertex("LAX");
	g.addVertex("DFW");
	g.addBidirectionalEdge("NY", "CHI", 50);
	g.addBidirectionalEdge("NY", "MIA", 300);
	g.addBidirectionalEdge("NY", "DFW", 50);
	g.addBidirectionalEdge("CHI", "SEA", 100);
	g.addBidirectionalEdge("SEA", "SFO", 25);
	g.addBidirectionalEdge("SFO", "LAX", 25);
	g.addBidirectionalEdge("SFO", "DFW", 100);
	g.addBidirectionalEdge("LAX", "MIA", 100);
	g.printGraph();
	cout << "*******************Dijkstra****************************" << endl;
	map<string, int> m = g.dijkstra("NY");
	for (pair<string, int> p : m) {
		cout << "NY to " << p.first << "=" << p.second << endl;
	}
}

/*
index 0 has a connection to 4 that costs 100
0 -> 4 | 100
1
2
3
4
5
6
7 -> dest | cost

*/