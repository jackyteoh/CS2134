#include <vector>
#include <string>
#include <iostream>

class Registrar {
public:
	void addCourse(std::string course);
	void addStudent(std::string student);
	void enrollStudentInCourse(std::string student, std::string course);
	void cancelCourse(std::string course);
	void printReport();
	void purge();
private:

};