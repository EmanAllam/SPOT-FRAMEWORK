#pragma once
#include <string>
using namespace std;
#include "DEFs.h"

class Student
{
	string firstName;
	string lastName;
	MAJORS selectedMajor;
	int id;
	bool showDefaultPlan = true;
	//To be used in setting names, names must not contain numbers.
	
	void writeNewData();
	void setMajor(char* major);
	void setMajor(string major);
	void readStdData();
	//these two function will return String "NULL" in case user didn't type his name, used only in writing files.
	string getFirstNameNull()const;
	string getLastNameNull()const;
	string getMajorNull()const;
public:
	Student(string firstName, MAJORS selectedMajor=FOUNDATION);
	Student();

	void setFirstName(string name);
	void setLastName(string name);
	void setMajor(MAJORS);
	
	void setFirstNameAndWrite(string name);
	void setLastNameAndWrite(string name);
	void setMajorAndWrite(MAJORS);
	void setId(int id);

	string getFirstName()const;
	string getLastName()const;
	string getName();
	MAJORS getMajor() const;
	string getMajorAsString() const;
	int getId() const;
	bool isUserSigned()const;
	void writeStdData();
	//Default is foundation
	bool isEngeering();


};

