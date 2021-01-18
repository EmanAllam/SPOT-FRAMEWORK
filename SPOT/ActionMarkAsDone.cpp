#include "ActionMarkAsDone.h"
#include <iostream>
using namespace std;

ActionMarkAsDone::ActionMarkAsDone(Registrar* p) :Action(p)
{
}

bool ActionMarkAsDone::Execute()
{
	GUI* pGui = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	ActionData actData = pGui->GetUserAction("Select a course mark/unmark as done");
	graphicsInfo ginfo{ actData.x,actData.y };
	try
	{
		Course* course = pS->getCourseAtGraphicsInfo(ginfo);
		int choice = 0;
		while (choice <1 || choice >6)
		{
			pGui->PrintMsg("Select course status: 1.Done 2.In Progress 3.Pending 4.Replaced 5.Exempted 6.Credit Transferred");
			choice = stoi(pGui->GetSrting());
		}
		course->setDone(pS,choice);
		cout << pS->getDoneCredits() << endl;
		cout << pS->getGpa()<<endl;
	}
	catch (char* error)
	{
		Execute();
	}
	return true;
}

ActionMarkAsDone::~ActionMarkAsDone()
{

}