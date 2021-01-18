#include "Student.h"
#include <iostream>
using namespace std;
#include <fstream>
#include<string>
Student::Student(string firstName, MAJORS selectedMajor)
{
	this->firstName = firstName;
	readStdData();
}

void Student::writeNewData()
{

}

Student::Student()
{
	selectedMajor = NOT_DEFINED;
	readStdData();
}

void Student::readStdData()
{
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	ifstream file;
	file.open("Files\\StudentProfile.txt");
	while (file.getline(line, size))
	{
		pch = strtok_s(line, ",", &context);
		bool nextIsFName = false;
		bool nextIsLName = false;
		bool nextIsMajor = false;
		while (pch != NULL)
		{
			if (string(pch) == "FirstName")
			{
				nextIsFName = true;
				nextIsMajor = false;
				nextIsLName = false;
				pch = strtok_s(NULL, ",", &context);

				continue;
			}
			else if (string(pch) == "LastName")
			{
				nextIsFName = false;
				nextIsLName = true;
				nextIsMajor = false;
				pch = strtok_s(NULL, ",", &context);

				continue;
			}
			if (string(pch) == "Major")
			{
				nextIsFName = false;
				nextIsLName = false;
				nextIsMajor = true;
				pch = strtok_s(NULL, ",", &context);

				continue;
			}
			
			else if (nextIsFName)
			{
				if (string(pch) != "NULL")
					setFirstName(string(pch));
				pch = strtok_s(NULL, ",", &context);
				continue;
			}
			else if (nextIsLName)
			{
				if (string(pch) != "NULL")
					setLastName(string(pch));
				pch = strtok_s(NULL, ",", &context);
				continue;
			}

			else if (nextIsMajor)
			{
				if(string(pch)!="NULL")
					setMajor(pch);
				pch = strtok_s(NULL, ",", &context);
				continue;
			}
			
			



		}
	}
	file.close();

}

void Student::writeStdData()
{
	ofstream file;
	//this will delete everyting
	file.open("Files\\StudentProfile.txt" ,std::ofstream::out | std::ofstream::trunc);
	file << "FirstName," << getFirstNameNull()<<endl;
	file << "LastName," << getLastNameNull()<<endl;
	file << "Major," << getMajorNull();

}

void Student::setFirstName(string name)
{
	this->firstName = name;
}

void Student::setFirstNameAndWrite(string name)
{
	setFirstName(name);
	writeStdData();
}

void Student::setLastName(string name)
{
	this->lastName = name;
}

void Student::setLastNameAndWrite(string name)
{
	setLastName(name);
	writeNewData();
}

void Student::setMajor(MAJORS selectedMajor)
{
	this->selectedMajor = selectedMajor;
}

void Student::setMajorAndWrite(MAJORS selectedMajor)
{
	this->selectedMajor = selectedMajor;
	writeStdData();
}
void Student::setMajor(char* major)
{
	setMajor(string(major));
	writeStdData();
}


void Student::setMajor(string  selectedMajor)
{
	if (selectedMajor == "CIE")
		setMajor(CIE);
	else if (selectedMajor == "ENV")
		setMajor(ENV);
	else if (selectedMajor == "NANE")
		setMajor(NANE);
	else if (selectedMajor == "REE")
		setMajor(REE);
	else if (selectedMajor == "SPC")
		setMajor(SPC);	
}

void Student::setId(int id)
{
	this->id = id;
}

string Student::getFirstName() const
{
	return firstName;
}

string Student::getFirstNameNull() const
{
	cout <<"ff"<< firstName<<endl;
	if(firstName.size() > 0)
		return getFirstName();
	return "NULL";
}
string Student::getLastName() const
{
	return lastName;
}

string Student::getLastNameNull() const
{
	if(lastName.size() > 0)
		return getLastName();
	return "NULL";
}

string Student::getMajorNull() const
{
	if(selectedMajor ==NOT_DEFINED)
		return "NULL";
	else 
	{
		return getMajorAsString();
	}
}



string Student::getName()
{
	return getFirstName()+" "+getLastName();
}

MAJORS Student::getMajor() const
{
	return selectedMajor;
}

string Student::getMajorAsString() const
{
	string filePath = "";
	switch (getMajor())
	{
	case FOUNDATION:
		return "FOUNDATION";
		break;
	case CIE:
		return filePath + "CIE";
		break;
	case ENV:
		return  filePath + "ENV";
		break;
	case NANE:
		return  filePath + "NAN";
		break;
	case REE:
		return  filePath + "REE";
		break;
	case SPC:
		return filePath + "SPC";
		break;
	default:
		return  "";
		break;
	}
}

int Student::getId() const
{
	return this->id;
}

bool Student::isUserSigned() const
{
	return selectedMajor != NOT_DEFINED;
}

bool Student::isEngeering()
{
	switch (selectedMajor)
	{
	case CIE:
		return true;
		//AHMED TODO: make sure of that major.
	case ENV:
		return true;
	case NANE:
		return true;
	case REE:
		return true;
	case SPC:
		return true;
	}
}
