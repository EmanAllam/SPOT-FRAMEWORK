#include<iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "BasicError.h"
#include "Courses/Course.h"
using namespace std;


BasicError::BasicError() 
{

}


BasicError::BasicError(int new_errorType)
{
	errorType = new_errorType;
	severity = set_severity();
	set_error_msg();
}

BasicError::BasicError(int new_errorType, Course* new_invalidCourse)
{
	errorType = new_errorType;
	invalidCourse = new_invalidCourse;
	severity = set_severity();
	set_error_msg();
}
BasicError::BasicError(int new_errorType, SEMESTER new_invalidSem, int new_invalidYear)
{
	errorType = new_errorType;
	invalidSem = new_invalidSem;
	invalidYear = new_invalidYear;
	severity = set_severity();
	set_error_msg();
}

string BasicError::set_severity()
{
	if (errorType == 1 || errorType == 3 || errorType == 4)
	{
		return "Critical issue";
	}
	else 
	{
		return "Moderate issue";
	}
}

void BasicError::set_error_msg()
{
	if (errorType == 1)
	{
		set_error_msg_1();
	}
	else if (errorType == 2)
	{
		set_error_msg_2();
	}
	else if (errorType == 3)
	{
		set_error_msg_3();
	}
	else if (errorType == 4)
	{
		set_error_msg_4();
	}
	else if (errorType == 5)
	{
		set_error_msg_5();
	}
}

void BasicError::set_error_msg_1() 
{	
	ostringstream stream;
	stream << "Invalid Study Plan: Course " << invalidCourse->getCode() << " has unmet dependencies. (" << severity << ")" ;
	error_msg = stream.str();
}

void BasicError::set_error_msg_2()
{
	ostringstream stream;
	stream << "Invalid Study Plan: Semster " << invalidSem << " Year "<< invalidYear << "(" << severity << ")";
	error_msg = stream.str();
}

void BasicError::set_error_msg_3()
{
	ostringstream stream;
	stream << "Invalid Study Plan: the Program requirements are not fullfilled by the current study plan. (" << severity << ")";
	error_msg = stream.str();
}

void BasicError::set_error_msg_4()
{
	ostringstream stream;
	stream << "Invalid Study Plan: the Concentration requirements are not fullfilled by the current study plan. (" << severity << ")";
	error_msg = stream.str();
}

void BasicError::set_error_msg_5()
{
	ostringstream stream;
	stream << "Invalid Study Plan: Course " << invalidCourse->getCode() << " has offering time issue. (" << severity << ")";
	error_msg = stream.str();
}

string BasicError::get_error_msg()
{
	return error_msg;
}

int BasicError::getType()
{
	return errorType;
}

string BasicError::getSeverity()
{
	return severity;
}

Course* BasicError::getCourse() {
	return invalidCourse;
}