#include "ActionImportCourseCatalog.h"
#include <fstream>
#include "Rules.h"
#include <string>
#include "DEFs.h"
#include <list>
#include  "Registrar.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "StringUtils.h"
using namespace std;

ActionImportCourseCatalog::ActionImportCourseCatalog(Registrar* pReg):ActionImport(pReg)
{
	//getFilePath() should return the base url --> Files//
	
	file.open(this->getFilePath()+"Courses-Catalog.txt");
}

bool ActionImportCourseCatalog::Execute()
{
	//Just to make sure that we are at the begining of the file
	beginTheFile();


	//Looping over the lines
	const int size = 300;
	char line[size];
	char* context = nullptr;
	CourseInfo* ci=nullptr;
	while (file.getline(line, size))
	{
		CourseInfo* tempCourseInfo= getCourseInfoFromLine(line, context);
		pReg->getRules().insertCourseInfoIntoCourseCatalog(tempCourseInfo);
	}
	
	return true;
}
CourseInfo* ActionImportCourseCatalog::getCourseInfoFromLine(char line[], char* context)
{
	//I can't access them from clas giving error 'this' can't be used in ...
	const int STEP_COURSE_CODE	= 0;
	const int STEP_TITLE		= 1;
	const int STEP_CREDITS		= 2;
	const int STEP_COREQ_PREREG	= 3;
	const int STEP_PREREQ		= 4;
	CourseInfo* tempCI=new CourseInfo;

	int currentStep = STEP_COURSE_CODE;
	char* pch = strtok_s(line, ",", &context);
	while (pch != NULL)
	{
		switch (currentStep)
		{
		case STEP_COURSE_CODE:
			tempCI->Code = pch;
			currentStep++;
			break;
		
		case STEP_TITLE:
			tempCI->Title = pch;
			currentStep++;
			break;
		
		case STEP_CREDITS:
			tempCI->Credits = stoi(pch);
			currentStep++;
			break;
		
		case STEP_COREQ_PREREG:
		{
			//this dummy var is used later, as I take only substring, as the string is -->Prereq: PHYS 101 And MATH 101. So I take what is after : and space
			string tempString = pch;
			int startIndex = 6;
			//6 --> indicates for "CoReq:" I just escape them. and 7 Means "PreReq"
			if (tempString.substr(0, 2) != "Co")
				startIndex = 7;
			vector<Course_Code> Req = StringUtils::getVectorFromStringSeperatedByTrim(tempString.substr(startIndex), "And");
			//then this means we are in CoReq if it's 6
			if(startIndex==6)
				tempCI->CoReqList = Req;
			else
				tempCI->PreReqList = Req;

			break;
		}
		default:
			break;
		}
		pch = strtok_s(NULL, ",", &context);
	}
	return tempCI;
}




ActionImportCourseCatalog::~ActionImportCourseCatalog()
{
}
