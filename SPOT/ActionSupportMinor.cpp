#include "ActionSupportMinor.h"


ActionSupportMinor::ActionSupportMinor(Registrar* p) :Action(p)
{
}

bool ActionSupportMinor::Execute()
{
	GUI* pGui = pReg->getGUI();
	bool flag = false;
	int choice = 0;
	Course_Code Code;
	while (choice != 4 && choice != 5) //if the choosen number is not 4 or 5 ask user again
	{
		pGui->PrintMsg("Would you take 4 or 5 Courses?");
		choice = stoi(pGui->GetSrting());
	}
	for (int i = 0; i < choice; i++)
	{
		pGui->PrintMsg("Enter The course code"); //read code
		Code = pGui->GetSrting();
		while (flag == false)
		{
			//loops over the catalouge to check if the code is correct
			for (auto it = pReg->getRules().CourseCatalog->begin(); it != pReg->getRules().CourseCatalog->end(); it++)
			{
				if (Code == it->Code) //add it to minor courses and its credits to total credits
				{
					flag = true;
					pReg->setMinorCourse(Code);
					pReg->addMinorCredits(pReg->getRules().getCourseInfoAtCode(Code)->Credits);
					break;
				}
			}
			//if the code is wrong then ask the user to reEnter
			if (flag == false)
			{
				pGui->PrintMsg("Please Re Enter The course code CORRECT"); //re read code
				Code = pGui->GetSrting();
			}
		}
		flag = false; //reset the flag to false after each right code
	}
	return true;
}

ActionSupportMinor::~ActionSupportMinor()
{

}