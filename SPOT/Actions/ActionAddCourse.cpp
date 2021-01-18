#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "..\DEFs.h"
#include <iostream>
#include "..\ActionChangeMenuItemTo.h"
#include "..\ActionMenuBar.h"


ActionAddCourse::ActionAddCourse(Registrar* p) :ActionMenuBar(p, GUI::ITM_ADD)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD, "GUI\\Images\\Menu\\Add_borderd.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD);



}

bool ActionAddCourse::Execute()
{
	actionChangeMenuItemTo->Execute();
	GUI* pGUI = pReg->getGUI();
	bool flag = false;
	Course* pC=nullptr;
	Course_Code Code;
	string title;
	int credits;
	string type;
	list<Course_Code> coReq;
	list<Course_Code> preReq;

	pGUI->PrintMsg("Enter course code to be added (eg: CIE 202)"); 
	Code = pGUI->GetSrting();
	//while loop to check if code is found (correct)
	while (flag == false)
	{
		//loops over the catalouge to check if the code is correct
		for (auto it = pReg->getRules().CourseCatalog->begin(); it != pReg->getRules().CourseCatalog->end(); it++)
		{
			if (Code == it->Code) //get its info
			{
				title = it->Title;
				credits = it->Credits;
				type = pReg->findTypeOfCourse(Code);
				pC = new Course(Code, title, credits);
				pC->setType(type);
				for (auto j = it->CoReqList.begin(); j != it->CoReqList.end(); j++)
					pC->addCoReq(*j);
				for (auto j = it->PreReqList.begin(); j != it->PreReqList.end(); j++)
					pC->addPreReq(*j);
				flag = true;
				break;
			}
		}
		//if the code is wrong then ask the user to reEnter
		if (flag == false)
		{
			pGUI->PrintMsg("Please Re Enter The course code CORRECT"); //re read code
			Code = pGUI->GetSrting();
		}
	}
	
	//choose the semester to add course
	ActionData actData = pGUI->GetUserAction("Select a semester to add coures to");


	//Checking if user want to deselect Add Action.
	if (isClose(actData.x, actData.y))
	{
		actionChangeMenuItemTo->reverseExcute();
		delete actionChangeMenuItemTo;
		return false;
	}

	int x, y;
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		StudyPlan* pS = pReg->getStudyPlay();
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		graphicsInfo gInfo{ x, y };
		graphicsInfo g2info{ x + CRS_WIDTH,y + CRS_HEIGHT };
		graphicsInfoComprehensive gcomprehensive{ gInfo,g2info };
		pC->setGfxInfo(gInfo);
		pC->setGfxInfoComp(gcomprehensive);
		//constants needed for detecting which semester
		int sH = pGUI->getStatusBarHeight();
		int wH = pGUI->getWindHeight();
		int d = VERTICAL_SPACE_BETWEEN_YEARS;
		int semH = CRS_HEIGHT + 2 * VERTICAL_SPACE_BETWEEN_SEMESTER_;
		int yH = 3 * semH;
		SEMESTER sem;
		for (int i = 0; i <= 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (y <= wH - sH - (d + yH) * i - d - semH * j && y > wH - sH - (d + yH) * i - d - semH * (j + 1))
				{
					sem = static_cast<SEMESTER>(j);
					pS->AddCourse(pC, i + 1, sem);
					pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
					break;
				}
			}
		}

	}
	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;
}

bool ActionAddCourse::Execute(Course* crs, SEMESTER& sem, int year)
{
	StudyPlan* pS = pReg->getStudyPlay();
	pS->AddCourse(crs, year, sem);
	return false;
}





ActionAddCourse::~ActionAddCourse()
{
}
