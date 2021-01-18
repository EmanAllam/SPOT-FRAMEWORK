#include "ActionDragAndDropCrs.h"
#include "Actions/Action.h"
#include "ActionDeleteCourse.h"
#include "Actions/ActionAddCourse.h"
#include "ActionChangeMenuItemTo.h"
#include "Registrar.h"
#include <iostream>
#include "GUI/GUI.h"
using namespace std;
ActionDragAndDropCrs::ActionDragAndDropCrs(Registrar* pReg): ActionMenuBar(pReg, GUI::ITM_DELETE)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_REORDER, "GUI\\Images\\Menu\\Reorder_bordered.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_REORDER);

}


bool ActionDragAndDropCrs::Execute()
{
	actionChangeMenuItemTo->Execute();
	//pReg->UpdateInterface();
	pReg->getGUI()->PrintMsg("Please drag and drop any course.");
	//Flushing 
	pReg->getGUI()->getWindow()->FlushMouseQueue();
	pReg->getGUI()->getWindow()->FlushKeyQueue();
	pReg->getGUI()->getWindow()->SetBuffering(true);
	bool bDragging = false;
	//dummy
	int iX = 0, iY = 0;

	int iXOld = 0;
	int iYOld = 0;
	char cKeyData;

	//is to be setLater
	int newX,newY ,ORIGINALX, ORIGINALY;
	Course* selectedCrs=new Course("", "", 0);
	Course* tempCrs = new Course("","",0);
	bool isChanged = false;

	while (pReg->getGUI()->getWindow()->GetKeyPress(cKeyData) != ESCAPE)
	{

		
		if (bDragging == false) {
			//it takes iX and iY by reference
			if (pReg->getGUI()->getWindow()->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) {
				if (pReg->getGUI()->isPointInMenuBarRange(iX, iY))
				{
					//Then user wants to end that action (Assumption)
					actionChangeMenuItemTo->reverseExcute();
					delete actionChangeMenuItemTo;
					return true;

				}
				try 
				{
					selectedCrs = pReg->getStudyPlay()->getCourseAtGraphicsInfo(graphicsInfo{ iX,iY });
					tempCrs = new Course(selectedCrs->getCode(), selectedCrs->getTitle(), selectedCrs->getCredits());
					tempCrs->setGfxInfoComp(selectedCrs->getGfxInfoComp());
					ORIGINALX = selectedCrs->getGfxInfoComp().topLeft.x;
					ORIGINALY = selectedCrs->getGfxInfoComp().topLeft.y;
					newX = ORIGINALX;;
					newY = ORIGINALY;
					selectedCrs->setSelected(true);
					bDragging = true;
					iXOld = iX;
					iYOld = iY;

				}
				catch (const char* msg)
				{

					pReg->getGUI()->PrintMsg("Please drag and drop any course.");
				}
			}
		}
		//User now is  moving the course.
		else if(bDragging == true)
		{
			if (pReg->getGUI()->getWindow()->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP)
			{
				//User stopped moving the course.
				SEMESTER sem = FALL;
				int year = -1;
				try


				{
					pReg->getStudyPlay()->getSemAndYearForPoint(iX, iY, sem, year);
					tempCrs->setCoReq(selectedCrs->getCoReq());		
					tempCrs->setPreReq(selectedCrs->getPreReq());		
					//delete by point
					ActionDeleteCourse* actionDltCrs = new ActionDeleteCourse(pReg);
					actionDltCrs->Execute(graphicsInfo{ selectedCrs->getGfxInfoComp().topLeft.x,selectedCrs->getGfxInfoComp().topLeft.y });
					
					//add new one
					ActionAddCourse* actionAddCrs = new ActionAddCourse(pReg);
					selectedCrs->setGfxInfoComp(tempCrs->getGfxInfoComp());
					actionAddCrs->Execute(tempCrs, sem, year);
					pReg->getStudyPlay()->calculateGraphicsInfoForEachItem(pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight());
					pReg->UpdateInterface();
					bDragging = false;
					
					return Execute();
					
				}
				catch (const char* msg)
				{
					newX = ORIGINALX;
					newY = ORIGINALY;
				}
			}
			else {
				//still moving
				isChanged = false;
				if (iX != iXOld) {
					newX = newX + (iX - iXOld);
					iXOld = iX;
					isChanged = true;

				}
				if (iY != iYOld) {
					newY = newY + (iY - iYOld);
					iYOld = iY;
					isChanged = true;


				}
			}
		}
		if (bDragging && isChanged)
		{
		
			tempCrs->setGfxInfoComp({ newX, newY, newX + CRS_WIDTH, newY + CRS_HEIGHT });
			pReg->UpdateInterface();
			pReg->getGUI()->RedrawTempCrs(tempCrs, GUI::OK);
		
			pReg->getGUI()->getWindow()->UpdateBuffer();
			//showInfo();
		}
	}
	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;
}

ActionDragAndDropCrs::~ActionDragAndDropCrs()
{

}

void ActionDragAndDropCrs::showInfo(Course* crsClicked)
{
	crsClicked->setSelected(true);
	//the show the the course RED
	pReg->UpdateInterface();
	pReg->getGUI()->PrintMsg("Title: " + crsClicked->getTitle()
		+ ", Credits: " + to_string(crsClicked->getCredits())
		+ ", Pre requisits: " + crsClicked->getPreReqAsString()
		+ ", Core requisits: " + crsClicked->getCoReqAsString()
		+ " .Please click anywhere to deselect."
	);
}
