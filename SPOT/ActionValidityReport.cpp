#include"Actions/Action.h"
#include "ActionValidityReport.h"
#include"Registrar.h"
#include<iostream>
#include <fstream>
#include<string>
#include <thread>
#include <chrono>
//#include "ActionChangeMenuItemTo.h"
#include "ErrorList.h"

using namespace std;
using std::this_thread::sleep_for;


ActionValidityReport::ActionValidityReport(Registrar* p) :Action(p)
{
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_VALIDITY_REPORT);

}

bool ActionValidityReport::Execute()
{
	actionChangeMenuItemTo->Execute();
	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("A report with all issues has been saved in the txt file.");
	StudyPlan* pS = pReg->getStudyPlay();
	ErrorList* errorList = pS->getErrors();
	pS->displayWarning(errorList);
	pS->saveTxtFile();
	sleep_for(2s);

	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;

}

ActionValidityReport::~ActionValidityReport()
{

}
