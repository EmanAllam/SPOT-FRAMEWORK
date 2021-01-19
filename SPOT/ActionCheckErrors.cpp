#include"Actions/Action.h"
#include "ActionCheckErrors.h"
#include"Registrar.h"
#include<iostream>
#include <fstream>
#include<string>
#include "ErrorList.h"

using namespace std;



ActionCheckErrors::ActionCheckErrors(Registrar* p) :Action(p)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_VALIDITY_REPORT);

}

bool ActionCheckErrors::Execute()
{
	//actionChangeMenuItemTo->Execute();
	//GUI* pGUI = pReg->getGUI();
	//pGUI->PrintMsg("A report with all issues has been saved in the txt file.");
	StudyPlan* pS = pReg->getStudyPlay();
	ErrorList* errorList = pS->getErrors();
	pS->displayWarning(errorList);
	//pS->saveTxtFile();
	//sleep_for(2s);

	//actionChangeMenuItemTo->reverseExcute();
	//delete actionChangeMenuItemTo;
	return true;

}

ActionCheckErrors::~ActionCheckErrors()
{

}
