#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Timeslot //Timeslot for the sections
{
public:
	Timeslot(string d, int t) : time(t), date(d) // constructor
	{}
	string const getDate()
	{
		return date;
	}
	int const getTime()
	{
		return time;
	}
	void setTime(int t)
	{
		time = t;
	}
	void display()//Prints a 24 hour clock in terms of 12 hours
	{
		cout << date << " ";
		if (time > 12) //If the hour is over 12
		{
			cout << (time - 12) << " PM"; // Changes 24 to 12 and makes it PM
		}
		else if (time == 12)
		{
			cout << time << " PM"; //IF 12 then make PM and dont subtract 12
		}
		else
		{
			cout << time << " AM";//Otherwise it is the same number and is AM
		}
		cout << endl;
	}
private:
	int time;
	string date;
};

class Student {
private:
	string StudentName;
	vector <int> Grades( , -1);
public:
	// addGrade
	// addSection ?
	void display() {
		for (, , i++) {

		}
	}
};

class Section {
private:
	string SectionName;
	vector <Student*> Student;
public:
	// addStudent
	// addLabWorker ??
	void display() {

	}

};

class LabWorker {
private:
	string LabWorkerName;
	vector <Section*> 
public:
	// addGrade
	// addSection
};


int main() {

	// lab workers
	LabWorker moe("Moe");
	LabWorker jane("Jane");

	// sections and setup and testing
	Section secA2("A2", "Tuesday", 16);
	//secA2.loadStudentsFromFile( "A2.txt" );
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");

	cout << "\ntest A2\n";    // here the modeler-programmer checks that load worked
	secA2.display();          // YOU'll DO THIS LATER AS: cout << secA2 << endl;
	moe.addSection(secA2);
	moe.displayGrades();       // here the modeler-programmer checks that adding the Section worked

	Section secB3("B3", "Thursday", 11);
	//secB3.loadStudentsFromFile( "B3.txt" );
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");

	cout << "\ntest B3\n";    // here the modeler-programmer checks that load worked
	secB3.display();          // YOU'll DO THIS LATER AS: cout << secB3 << endl;
	jane.addSection(secB3);
	jane.displayGrades();      // here the modeler-programmer checks that adding Instructor worked


							   // setup is complete, now a real world scenario can be written in the code
							   // [NOTE: the modeler-programmer is only modeling joe's actions for the rest of the program]

							   // week one activities  
	cout << "\nModeling week: 1\n";
	moe.addGrade("John", 7, 1);
	moe.addGrade("Paul", 9, 1);
	moe.addGrade("George", 7, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << "End of week one\n";
	moe.displayGrades();

	// week two activities
	cout << "\nModeling week: 2\n";
	moe.addGrade("John", 5, 2);
	moe.addGrade("Paul", 10, 2);
	moe.addGrade("Ringo", 0, 2);
	cout << "End of week two\n";
	moe.displayGrades();

	//test that reset works  // NOTE: can we check that the heap data was dealt with?
	cout << "\ntesting reset()\n";
	secA2.reset();
	secA2.display();
	moe.displayGrades();

} // main