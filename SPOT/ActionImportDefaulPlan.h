#pragma once
#include "ActionImport.h"
#include "Registrar.h"
class ActionImportDefaulPlan :
    public ActionImport
{

	bool isCourseCode(const string& input);
	bool isYear(const string& input);
	bool isSemster(const string& input);
	SEMESTER getSemesterFromString(const string& input);
	
public:
	ActionImportDefaulPlan(Registrar*);
	bool virtual Execute();
	virtual string getFilePath(Student* signedStudent);
	virtual ~ActionImportDefaulPlan();
};

