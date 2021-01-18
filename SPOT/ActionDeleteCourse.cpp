#include "ActionDeleteCourse.h"
#include "ActionChangeMenuItemTo.h"
#include "GUI/GUI.h"
#include "ActionMenuBar.h"
#include "EmptyAction.h"
ActionDeleteCourse::ActionDeleteCourse(Registrar* p) :ActionMenuBar(p, GUI::ITM_DELETE)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_DELETE, "GUI\\Images\\Menu\\Delete_borderd.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_DELETE);

}

bool ActionDeleteCourse::Execute()
{
	
	actionChangeMenuItemTo->Execute();
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Select a course to be deleted");
	if (isClose(actData.x, actData.y))
	{
		actionChangeMenuItemTo->reverseExcute();
		delete actionChangeMenuItemTo;
		return false;
	}
	graphicsInfo ginfo{ actData.x,actData.y };
	SEMESTER deletedSemester;
	int deletedYear;
	int orderOfCourse;
	try
	{
		Course* toBeDeleted = pReg->getStudyPlay()->getCourseAtGraphicsInfo(ginfo, deletedSemester, deletedYear, orderOfCourse);
		//if the course is done, remove its effect from gpa before deleting it
		if (toBeDeleted->getDone() == true)
		{
			StudyPlan* pS = pReg->getStudyPlay();
			toBeDeleted->setDone(pS,2); //mark it as undone then remove its effect from gpa
		}
		//delete the course
		pReg->getStudyPlay()->DeleteCourse(toBeDeleted, deletedYear, deletedSemester, orderOfCourse);
		pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
		actionChangeMenuItemTo->reverseExcute();
		delete actionChangeMenuItemTo;
	}
	catch (char* msg)
	{
		EmptyAction* p = new EmptyAction(pReg);
		p->Execute();
		delete p;
		actionChangeMenuItemTo->reverseExcute();
		delete actionChangeMenuItemTo;
	}

	return true;
}


bool ActionDeleteCourse::Execute(graphicsInfo ginfo)
{
	ginfo.x += 5;
	ginfo.y += 5;
	GUI* pGUI = pReg->getGUI();
	SEMESTER deletedSemester;
	int deletedYear;
	int orderOfCourse;
	try
	{
		Course* toBeDeleted = pReg->getStudyPlay()->getCourseAtGraphicsInfo(ginfo, deletedSemester, deletedYear, orderOfCourse);
		pReg->getStudyPlay()->DeleteCourse(toBeDeleted, deletedYear, deletedSemester, orderOfCourse);
	}
	catch (const char* msg)
	{
	}
	return true;
}

bool ActionDeleteCourse::Execute(Course* crs)
{
	GUI* pGUI = pReg->getGUI();
	SEMESTER deletedSemester;
	int deletedYear;
	int orderOfCourse;
	try
	{
		//Course* toBeDeleted = pReg->getStudyPlay()->getCourseAtGraphicsInfo(ginfo, deletedSemester, deletedYear, orderOfCourse);
		//cout << toBeDeleted->getTitle()<<endl;
		//pReg->getStudyPlay()->DeleteCourse(toBeDeleted, deletedYear, deletedSemester, orderOfCourse);
		//cout << 4;
	}
	catch (const char* msg)
	{
	}
	return true;
}


ActionDeleteCourse::~ActionDeleteCourse()
{

}