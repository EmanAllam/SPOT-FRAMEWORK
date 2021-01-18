#include "ActionShowCourseInfo.h"
#include "Actions/Action.h"
#include "Registrar.h"
#include <thread>
ActionShowCourseInfo::ActionShowCourseInfo(Registrar* pReg, Course* crsClicked):Action(pReg)
{
	this->crsClicked = crsClicked;
}

bool ActionShowCourseInfo::Execute()
{
	crsClicked->setSelected(true);
	//the show the the course RED
	//pReg->UpdateInterface();
	pReg->getGUI()->DrawCourse(crsClicked);

	pReg->getGUI()->PrintMsg("Title: " + crsClicked->getTitle()
		+ ". Credits: " + to_string(crsClicked->getCredits())
		+". Pre requisits: "+ crsClicked->getPreReqAsString()
		+" Core requisits: "+ crsClicked->getCoReqAsString()
		+" .Please click anywhere to deselect."
	);
	//Waiting for user to click anywhere whithout printing anythign new

	
	ActionData actData = pReg->getGUI()->GetUserAction();
	crsClicked->setSelected(false);
	pReg->getGUI()->DrawCourse(crsClicked);

	//if the user clicked on another course
	graphicsInfo tempGI;
	tempGI.x = actData.x;
	tempGI.y = actData.y;
	try
	{
		Course* crsClicked = pReg->getStudyPlay()->getCourseAtGraphicsInfo(tempGI);
		//making sure that the course user clicked on later is not the same as what was already clicked on. it it is it will just deselect it.
		if (crsClicked == this->crsClicked)
			return false;
		//then course found if it doesn't throw an exception
		Action* RequiredAction = new ActionShowCourseInfo(pReg, crsClicked);
		RequiredAction->Execute();
		delete RequiredAction;
	}
	catch (const char* msg)
	{
		return false;
	}
	return false;
}

ActionShowCourseInfo::~ActionShowCourseInfo()
{
}
