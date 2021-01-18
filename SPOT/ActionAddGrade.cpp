#include "ActionAddGrade.h"

ActionAddGrade::ActionAddGrade(Registrar* p) :Action(p)
{
}

bool ActionAddGrade::Execute()
{
	GUI* pGui = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	ActionData actData = pGui->GetUserAction("Select a course to add its grade Letter");
	graphicsInfo ginfo{ actData.x,actData.y };
	try
	{
		Course* course = pS->getCourseAtGraphicsInfo(ginfo);
		pGui->PrintMsg("Enter the grade Letter  (e.g.: A-) ");
		course->setPoints(pGui->GetSrting(), pS);
	}
	catch (char* error)
	{
		Execute();
	}
	return true;
}

ActionAddGrade::~ActionAddGrade()
{

}