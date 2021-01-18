#include<iostream>
#include <fstream>
#include<string>
#include "Courses/Course.h"
using namespace std;


class BasicError
{
private:
	string error_msg;
	int errorType;
	string severity;
	Course* invalidCourse;
	SEMESTER invalidSem;
	int invalidYear;


public:
	BasicError();
	BasicError(int new_errorType);
	BasicError(int new_errorType, Course* new_invalidCourse);
	BasicError(int new_errorType, SEMESTER new_invalidSem, int new_invalidYear);
	
	string set_severity();

	void set_error_msg();
	void set_error_msg_1();
	void set_error_msg_2();
	void set_error_msg_3();
	void set_error_msg_4();
	void set_error_msg_5();

	string get_error_msg();
	int getType();
	string getSeverity();
	Course* getCourse();
};