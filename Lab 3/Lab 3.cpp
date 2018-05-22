#include <iostream>
#include <vector>
using namespace std;

// Task 1
class Sandwich { //Makes a class for Sandwich
private:
	int const bread; // sets variables for contents of sandwich with their types
	int cheese; // All are in private because contents should not be able to be changed
	double mayonaise;
	int tomato;
	double mustard;
// Task 2
public: // in public is the amount of ingredients that the customer wants in their sandwich
	Sandwich(int myCheese = 2, double myMayonaise = 1.0, int myTomato = 1, double myMustard = 1.0) : bread(2), cheese(myCheese),
		mayonaise(myMayonaise), tomato(myTomato), mustard(myMustard) {}; /* setting variables to a certain value*/
	int getCheese() const { // returns each variable with certain value when function is called
		return cheese;
	}
	int getTomatoes() const {
		return tomato;
	}
	double getMustard() const {
		return mustard;
	}
	double getMayonaise() const {
		return mayonaise;
	}
	void setCheese(int myCheese) { //creates function for set___ to return set values
		cheese = myCheese;
	}
	void setMayonaise(double myMayonaise) {
		mayonaise = myMayonaise;
	}
	void setTomato(int myTomato) {
		tomato = myTomato;
	}
	void setMustard(double myMustard) {
		mustard = myMustard;
	}
	void display() { //prints the ingredient with its corresponding amount
		cout << "Bread :" << bread << endl;
		cout << "Cheese: " << cheese << endl;
		cout << "Mayonaise: " << mayonaise << endl;
		cout << "Tomato: " << tomato << endl;
		cout << "Mustard: " << mustard << endl;
	}
};
class SandwichTruck { //class for the sandwich truck
private:
	vector<Sandwich> Sandwiches; 
public:
	void displaySandwiches() { //for every sandwich in the sandwich truck, function displays it
		for (int i = 0; i < Sandwiches.size(); i++) {
			Sandwiches[i].display();
		}
	}
	void addSandwiches(Sandwich singleSandwich) { // this function adds sandwiches to the vector so that it is able to be called
		Sandwiches.push_back(singleSandwich);
	}
};

int main() {
	SandwichTruck SandwichDelivery; // calls the sandwich truck class
	Sandwich sandwich1;
	Sandwich sandwich2;
	SandwichDelivery.addSandwiches(sandwich1); //adds sandwich 1
	SandwichDelivery.addSandwiches(sandwich2); // and sandwich 2 to the truck
	SandwichDelivery.displaySandwiches(); // then displays the sandwich with their ingredients
	system("pause");
};
