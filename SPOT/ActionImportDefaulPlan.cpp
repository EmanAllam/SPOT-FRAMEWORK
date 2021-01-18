#include "ActionImportDefaulPlan.h"
#include "Actions\Action.h"
#include <iostream>
#include "StringUtils.h"

using namespace std;

ActionImportDefaulPlan::ActionImportDefaulPlan(Registrar* pReg1):ActionImport(pReg1)
{
	if (pReg->getSignedStudest()->isUserSigned())
	{
		file.open(getFilePath(pReg->getSignedStudest()));
	}
}

bool ActionImportDefaulPlan::isCourseCode(const string& input)
{
	if (!isYear(input) && !isSemster(input))
		return true;
	return false;

}

bool ActionImportDefaulPlan::isYear(const string& input)
{
	if (StringUtils::contains(input, "Year"))
		return true;
	return false;
}

bool ActionImportDefaulPlan::isSemster(const string& input)
{
	if (StringUtils::contains(input, "Fall"))
		return true;
	if (StringUtils::contains(input, "Spring"))
		return true;
	if (StringUtils::contains(input, "Summer"))
		return true;
	return false;
}

SEMESTER ActionImportDefaulPlan::getSemesterFromString(const string& input)
{
	if (input == "Fall")
		return FALL;
	if (input == "Spring")
		return SPRING;
	if (input == "Summer")
		return SUMMER;
	return SEM_CNT;
}

bool ActionImportDefaulPlan::Execute()
{
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	while (file.getline(line, size))
	{
		int lastSeenYear;
		SEMESTER lastSeenSemster;
		pch = strtok_s(line, ",", &context);
		while (pch != NULL)
		{
			if (isCourseCode(pch))
			{
				//TODO:: see if you need to check this course name exist.
				CourseInfo* tempCrsInfo = pReg->getRules().getCourseInfoAtCode(pch);
				Course* c = new Course(pch,tempCrsInfo->Title, tempCrsInfo->Credits);
				for (auto co = (*tempCrsInfo).CoReqList.begin(); co != (*tempCrsInfo).CoReqList.end(); ++co)
				{
					
					c->addCoReq(*co);
				}
				for (auto pe = (*tempCrsInfo).PreReqList.begin(); pe != (*tempCrsInfo).PreReqList.end(); ++pe)
				{
					
					c->addPreReq(*pe);
				}
				// type of the course
				Course_Code code = c->getCode();
				string type = pReg->findTypeOfCourse(code);;
				c->setType(type);
				//add course to the plan
				pReg->getStudyPlay()->AddCourse(c, lastSeenYear, lastSeenSemster);
				
			}
			else
			{
				if (isYear(pch))
				{
					//Review for understanding.
					lastSeenYear = pch[5] - '0';
				}
				else
				{
					string lastSeenSemestringString = pch;
					lastSeenSemster = getSemesterFromString(lastSeenSemestringString);

				}
			}

			pch = strtok_s(NULL, ",", &context);
		}
	}
	pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
	return true;
}

string ActionImportDefaulPlan::getFilePath(Student* signedStudent)
{
	//EX:: (Files//)+(CIE)+(-StudyPlan.txt) -> files//Cie-studyPlan.txt which is the right path.
	return ActionImport::getFilePath() + signedStudent->getMajorAsString() + "-StudyPlan.txt";
}

ActionImportDefaulPlan::~ActionImportDefaulPlan()
{
}
