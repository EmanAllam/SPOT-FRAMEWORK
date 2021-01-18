#include "ActionShowGpa.h"

ActionShowGpa::ActionShowGpa(Registrar* p) :Action(p)
{
}

bool ActionShowGpa::Execute()
{
	GUI* pGUI = pReg->getGUI();
	string data="GPA: ";
	data += pReg->getStudyPlay()->getGpa();
	data += " Done Credits: ";
	data += pReg->getStudyPlay()->getDoneCredits();
	data += " Student Level: ";
	data += pReg->getStudyPlay()->getStudentLevel();
	pGUI->PrintMsg(data);
	ActionData actData = pReg->getGUI()->GetUserAction();
	return true;
}

ActionShowGpa::~ActionShowGpa()
{

}