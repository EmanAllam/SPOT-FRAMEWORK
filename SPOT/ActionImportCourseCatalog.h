#pragma once
#include "ActionImport.h"
#include "Rules.h"

class ActionImportCourseCatalog :
    public ActionImport
{

	/*
		These step variables, are used when iterrating over the each line to know exactly where the incoming input should go to, either is its name or credits ..etc.
	*/
	const int STEP_COURSE_CODE = 0;
	const int STEP_TITLE =1;
	const int STEP_CREDITS		=2;
	const int STEP_COREQ		=3;
	const int STEP_PREREQ		=4;


	//this function shall take one string line from many lines in Course-catalog.txt to parse to fill CourseInfo and return it back.
	CourseInfo* getCourseInfoFromLine(char line[], char* context);

public:
	ActionImportCourseCatalog(Registrar*);
	bool virtual Execute();
	~ActionImportCourseCatalog();

};

