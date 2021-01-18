#pragma once
#include<iostream>
#include <fstream>
#include<string>
#include "BasicError.h"
//#include "DEFs.h"
//#include "Registrar.h"

using namespace std;



class ErrorList {
private:
	int cnt = 0;
	BasicError* errors = new BasicError[10];

public:
	void addError(BasicError x) {
		errors[cnt] = x;
		cnt++;
	}

	int getCount() {
		return cnt;
	}

	BasicError* getErrorArray() {
		return errors;
	}

};

/*
ErrorList* getErrors()
{
	int cnt = 0;

	ErrorList* errorList = new ErrorList();

	// THIS SHOULD BE REPLACED WITH ACTUAL ERROR CHECKS
	Course* x = new Course("CIE 321", "qdwefrgtrhyt", 3);
	BasicError error_1 = BasicError(1, x);

	SEMESTER sem = SUMMER;
	BasicError error_2 = BasicError(2, sem, 3);

	BasicError error_3 = BasicError(3);

	BasicError error_4 = BasicError(4);

	Course* x2 = new Course("CIE 101", "pew", 5);
	BasicError error_5 = BasicError(5, x2);

	errorList->addError(error_1);
	errorList->addError(error_2);
	errorList->addError(error_3);
	errorList->addError(error_4);
	errorList->addError(error_5);


	
	//for (int i = 0; i < 5; i++) 
	//{
	//	BasicError new_error = BasicError(1, x);
	//	errorList->addError(new_error);
	//}
	

	//int arr1[5] = { 1,2,3,4,5 };
	//string arr2[5] = { "CIE 202", "Summer Year1","", "", "ENGR 210" };
	return errorList;
}

ErrorList* getErrors(Course* x)
{
	int cnt = 0;

	ErrorList* errorList = new ErrorList();

	// THIS SHOULD BE REPLACED WITH ACTUAL ERROR CHECKS
	//Course* x = new Course("CIE 321", "qdwefrgtrhyt", 3);
	BasicError error_1 = BasicError(1, x);

	SEMESTER sem = SUMMER;
	BasicError error_2 = BasicError(2, sem, 3);

	BasicError error_3 = BasicError(3);

	BasicError error_4 = BasicError(4);

	Course* x2 = new Course("CIE 101", "pew", 5);
	BasicError error_5 = BasicError(5, x2);

	errorList->addError(error_1);
	errorList->addError(error_2);
	errorList->addError(error_3);
	errorList->addError(error_4);
	errorList->addError(error_5);


	
	//for (int i = 0; i < 5; i++)
	//{
	//	BasicError new_error = BasicError(1, x);
	//	errorList->addError(new_error);
	//}
	

	//int arr1[5] = { 1,2,3,4,5 };
	//string arr2[5] = { "CIE 202", "Summer Year1","", "", "ENGR 210" };
	return errorList;
}


void displayWarning(ErrorList* errorList, StudyPlan* pS)
{	
	pS->ClearWarnings();
	int cnt = errorList->getCount();
	BasicError* errorArray = errorList->getErrorArray();
	for (int i = 0; i < cnt; i++)
	{	
		pS->AddWarning(errorArray[i].get_error_msg());
		cout << errorArray[i].get_error_msg() << endl;

		if (errorArray[i].getType() == 1)
		{
			errorArray[i].getCourse()->setColor(2);

		}

	}
}
*/