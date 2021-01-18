#include "ActionDisplayStudentLevel.h"


ActionDisplayStudentLevel::ActionDisplayStudentLevel(Registrar* p) :Action(p)
{
}

bool ActionDisplayStudentLevel::Execute()
{
	GUI* pGui = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	pGui->PrintMsg(pS->getStudentLevel());
	return true;
}

ActionDisplayStudentLevel::~ActionDisplayStudentLevel()
{

}