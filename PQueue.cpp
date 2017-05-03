#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

template <class T>
class PQueue{
	vector<T> data;
	void percolateUp(int pos); //pos=position
	void percolateDown(int pos); //pos=position
public:
	PQueue(){ data.push_back(T()); } //push garbage into position zero
	int size()const{ return data.size() - 1; }
	bool isEmpty()const { return data.size() == 1; }
	T top(){ return data[1]; }
	void clear(){ data.resize(1); }
	void push(T newdata){
		data.push_back(newdata);
		percolateUp(data.size() - 1);
	}
	T pop();
};
template <class T>
void PQueue<T>::percolateDown(int pos){
	if (pos * 2 >= data.size()) //no children
		return;
	else if (pos * 2 + 1 == data.size()){ //pos has only one child
		if (data[pos * 2] < data[pos])
			swap(data[pos], data[pos * 2]);
	}
	else{ //two children
		if (data[pos] < data[pos * 2] && data[pos] < data[pos * 2 + 1]) //pos is the lesser value, leave it alone
			return;
		else{
			if (data[pos * 2] < data[pos * 2 + 1]){//find the lesser of the two children
				swap(data[pos], data[pos * 2]);
				percolateDown(pos * 2);
			}
			else{
				swap(data[pos], data[pos * 2 + 1]);
				percolateDown(pos * 2 + 1);
			}
		}
	}
}
template <class T>
void PQueue<T>::percolateUp(int pos){
	if (pos > 1){ //when pos is 1, we're the root and, therefore, finished
		if (data[pos] < data[pos / 2]){//we're less than our parent, so we should swap
			swap(data[pos], data[pos / 2]);
			percolateUp(pos / 2);
		}
	}
}

template <class T>
T PQueue<T>::pop(){
	if (data.size() <= 1) //pop from an empty queue???  nah fam.
		return T();
	T temp = top();
	data[1] = data[data.size() - 1];
	data.pop_back();
	percolateDown(1);
	return temp;
}


int main(){
	PQueue<int> pq;
	srand(time(NULL));
	for (int i = 0; i < 50; i++)
		pq.push(rand() % 100);

	while (!pq.isEmpty())
		cout << pq.pop() << endl;
}