#include <iostream>
#include <vector>
#include <string>

class Course {
public:
	void addCourse(std::string course);
	void enrollStudentInCourse(std::string student, std::string course);
	void cancelCourse(std::string course);
private:
	std::string course
};
