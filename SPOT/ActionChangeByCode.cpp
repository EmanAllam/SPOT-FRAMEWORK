#include "ActionChangeByCode.h"
#include "Registrar.h"
#include "Rules.h"
#include "GUI/GUI.h"
#include <string>
#include "Courses/Course.h"
#include "ActionDeleteCourse.h"
#include "Actions/ActionAddCourse.h"
#include "ActionMenuBar.h"

using namespace std;
ActionChangeByCode::ActionChangeByCode(Registrar* pReg) :ActionMenuBar(pReg, GUI::ITM_CHANGE_CRS_BY_CODE)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_CHANGE_CRS_BY_CODE, "GUI\\Images\\Menu\\Update_borderd.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_CHANGE_CRS_BY_CODE);

}

bool ActionChangeByCode::DeleteAndAdd(string desiredCrs, ActionData actData, SEMESTER sem, int  year)
{
	try
	{
		CourseInfo* desireCrsInfoClicked = pReg->getRules().getCourseInfoAtCode(desiredCrs);
		Course* desiredCourse = new Course(desireCrsInfoClicked->Code, desireCrsInfoClicked->Title, desireCrsInfoClicked->Credits);
		desireCrsInfoClicked->CoReqList = desireCrsInfoClicked->CoReqList;
		desireCrsInfoClicked->PreReqList = desireCrsInfoClicked->PreReqList;
		//Then the course name user typed was right
		ActionDeleteCourse* actionDltCrs = new ActionDeleteCourse(pReg);
		//this will delete course selected
		actionDltCrs->Execute(graphicsInfo{ actData.x, actData.y });

		//this will add the new Course
		ActionAddCourse* actionAddCrs = new ActionAddCourse(pReg);
		actionAddCrs->Execute(desiredCourse, sem, year);
		//showing the results
		pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
		pReg->UpdateInterface();

		//TODO::Ask about these errors.
		//delete desireCrsInfoClicked;
		//delete desiredCourse;
		//delete oldCrsClicked;
		return true;

	}
	catch (const char* msg)
	{
		return false;
		//The user wrote wrong course code
		throw "Wrong Course Code";
	}
}

bool ActionChangeByCode::Execute()
{
	//This varialbe is used if user wrote wrong name and I want to show differenct msg.
	actionChangeMenuItemTo->Execute();

	pReg->getGUI()->PrintMsg("Please Select any course to to updated");
	//Waiting for user to click anywhere whithout printing anythign new
	ActionData actData = pReg->getGUI()->GetUserAction();
	graphicsInfo tempGI;
	tempGI.x = actData.x;
	tempGI.y = actData.y;
	if (isClose(actData.x, actData.y))
	{
		actionChangeMenuItemTo->reverseExcute();
		return false;
	}

	try
	{
		SEMESTER sem;
		int  year, dummyOrder;
		Course* oldCrsClicked = pReg->getStudyPlay()->getCourseAtGraphicsInfo(tempGI, sem, year, dummyOrder);
		oldCrsClicked->setSelected(true);
		pReg->UpdateInterface();
		pReg->getGUI()->PrintMsg("Please write the desired course code correctly. Don't Forget CORRECTLY.");
		string desiredCrs = pReg->getGUI()->GetSrting();
		while (!DeleteAndAdd(desiredCrs, actData, sem, year))
		{
			pReg->getGUI()->PrintMsg("Please write the desired course code correctly. Don't Forget CORRECTLY.");
			desiredCrs = pReg->getGUI()->GetSrting();
		}


	}
	catch (const char* msg)
	{
		//Nothing happens if user clicks somewhere not containing course.
	}
	actionChangeMenuItemTo->reverseExcute();
	return false;
}

ActionChangeByCode::~ActionChangeByCode()
{
}