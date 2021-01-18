#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>
#include <iostream>
#include <map>
#include "..\ViewField.h"
#include <conio.h>
using namespace std;
GUI::GUI()
{
	changeMenuItemTo(ITM_ADD, "GUI\\Images\\Menu\\Add.jpeg");
	changeMenuItemTo(ITM_DELETE, "GUI\\Images\\Menu\\Delete.jpeg");
	changeMenuItemTo(ITM_ADD_NOTES, "GUI\\Images\\Menu\\Add_note.jpeg");
	changeMenuItemTo(ITM_SHOW_NOTES, "GUI\\Images\\Menu\\Show_notes.jpeg");
	changeMenuItemTo(ITM_CHANGE_CRS_BY_CODE, "GUI\\Images\\Menu\\Update.jpeg");
	changeMenuItemTo(ITM_REORDER, "GUI\\Images\\Menu\\Reorder.jpg");
	changeMenuItemTo(ITM_SETTINGS, "GUI\\Images\\Menu\\Settings.jpeg");



	changeMenuItemTo(ITM_COURSE_STATUS, "GUI\\Images\\Menu\\gpa.jpg");
	changeMenuItemTo(ITM_ADD_GRADE, "GUI\\Images\\Menu\\gpa1.jpg");
	changeMenuItemTo(ITM_SHOW_GRADE, "GUI\\Images\\Menu\\gpa2.jpg");
	changeMenuItemTo(ITM_SUPPORT_MINOR, "GUI\\Images\\Menu\\gpa3.jpg");


	pWind = new window(WindWidth, WindHeight, wx, wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	//pWind->SetBrush(BkGrndColor);
	//pWind->SetPen(BkGrndColor);
	//pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
	pWind->DrawImage(BACKGROUN_PATH_FILE, 0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);
	int widthOfBlackLine = 3;
	for (int i = 0; i < ITM_CNT; i++)
	{
		pWind->SetPen(BkGrndColor, widthOfBlackLine);
		//Draw a line before each icon
		pWind->DrawLine(i * MenuItemWidth, 0, i * MenuItemWidth, MenuBarHeight);
		pWind->DrawImage(filePathsForMenuItem->at(static_cast<MENU_ITEM>(i)), i * MenuItemWidth + widthOfBlackLine, 0, MenuItemWidth - widthOfBlackLine, MenuBarHeight);
		//pWind->DrawLine(i * MenuItemWidth, 0, i * MenuItemWidth , MenuBarHeight);

	}
	//Draw a line after last course.
	pWind->DrawLine((ITM_CNT - 1) * MenuItemWidth + MenuItemWidth + widthOfBlackLine, 0, (ITM_CNT - 1) * MenuItemWidth + MenuItemWidth + widthOfBlackLine, MenuBarHeight);

}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{

	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	//if condition to choose color of the course according to its type
	color DrawColor;
	if (pCrs->getType() == "UnivCompulsory")
		DrawColor = BLUE;
	else if (pCrs->getType() == "UnivElective")
		DrawColor = PINK;
	else if (pCrs->getType() == "TrackCompulsory")
		DrawColor = DARKRED;
	else if (pCrs->getType() == "MajorCompulsory")
		DrawColor = BLACK;
	else if (pCrs->getType() == "MajorElective")
		DrawColor = SNOW;
	else if (pCrs->getType() == "Minor")
		DrawColor = DIMGREY;
	else DrawColor = GREEN;


	if (pCrs->isSelected())
		pWind->SetPen(RED, 2);
	else
		pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(ZewailCityBackground);
	graphicsInfo gInfo = pCrs->getGfxInfoComp().topLeft;
	//elective courses are rounded
	if (pCrs->getType() == "UnivElective" || pCrs->getType() == "MajorElective")
		pWind->DrawEllipse(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	else
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);


	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(BLACK);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
	pWind->DrawLine(0, 0, 500, 500);
}

void GUI::DrawAcademicYear(const AcademicYear* pY)
{
	pWind->SetPen(BLACKONWHITE);
	pWind->DrawRectangle(pY->getGfxInfoComp().topLeft.x, pY->getGfxInfoComp().topLeft.y, pY->getGfxInfoComp().bottomRight.x, pY->getGfxInfoComp().bottomRight.y, FRAME);
	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(pY->getGfxInfoComp().topLeft.x + 10, (pY->getGfxInfoComp().topLeft.y + pY->getGfxInfoComp().bottomRight.y + 15) / 2, "Year " + to_string(pY->getYear()));
	pWind->SetPen(BLACK);

	//Line after word year
	pWind->DrawLine(WIDTH_YEAR_WORD, pY->getGfxInfoComp().topLeft.y, WIDTH_YEAR_WORD, pY->getGfxInfoComp().bottomRight.y);
	//line after year+ semester
	pWind->DrawLine(WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD, pY->getGfxInfoComp().topLeft.y, WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD, pY->getGfxInfoComp().bottomRight.y);

	//draw vertical row between semesters.
	int lastY = pY->getGfxInfoComp().bottomRight.y - CRS_HEIGHT - VERTICAL_SPACE_BETWEEN_YEARS - VERTICAL_SPACE_BETWEEN_SEMESTER_ / 2;
	for (int i = FALL; i < SEM_CNT; i++)
	{

		pWind->DrawLine(WIDTH_YEAR_WORD, lastY, pY->getGfxInfoComp().bottomRight.x, lastY);
		pWind->SetPen(BLACK);
		pWind->SetFont(15, ITALICIZED, BY_NAME, "Arial");
		pWind->DrawString(WIDTH_YEAR_WORD + 2, lastY + 5, i == 0 ? "Fall" : (i == 1 ? "Spring" : "Summer"));
		lastY = lastY - CRS_HEIGHT - VERTICAL_SPACE_BETWEEN_YEARS - VERTICAL_SPACE_BETWEEN_SEMESTER_ / 2;
	}


}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{

				case ITM_ADD: return ActionData{ ADD_CRS,x,y };	//Add course
				case ITM_CHANGE_CRS_BY_CODE: return ActionData{ CHANGE_BY_CODE ,x,y };
				case ITM_DELETE: return ActionData{ DEL_CRS,x,y };		//Delete course
				case ITM_REORDER: return ActionData{ REORDER ,x,y };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES ,x,y };
				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES,x,y };
				case ITM_SETTINGS: return ActionData{ SETTINGS,x,y };
				case ITM_COURSE_STATUS: return ActionData{ COURSE_STATUS,x,y };
				case ITM_ADD_GRADE: return ActionData{ ADD_GRADE,x,y };
				case ITM_SHOW_GRADE: return ActionData{ SHOW_GRADE,x,y };
				case ITM_SUPPORT_MINOR: return ActionData{ SUPPORT_MINOR,x,y };
					

				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}
ActionData GUI::GetUserAction() const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	//PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}


		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course

				case ITM_DELETE: return ActionData{ DEL_CRS };		//delete
				case ITM_SETTINGS : return ActionData{ SETTINGS };

				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES };
				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}

ActionData GUI::GetCoordAndSenseDelete() const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;


	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course

				case ITM_DELETE: return ActionData{ DEL_CRS };		//delete
				case ITM_SETTINGS: return ActionData{ SETTINGS };

				case ITM_ADD_NOTES: return ActionData{ ADD_NOTES };
				case ITM_SHOW_NOTES: return ActionData{ SHOW_NOTES };
				default: return ActionData{ MENU_BAR };	   //A click on empty place in menu bar

				}
			}

			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
			}

			
		}
		
		

	}
}

string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar



	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








int GUI::getWindHeight() const
{
	return WindHeight;
}
int GUI::getWindWidth()const
{
	return WindWidth;
}
int GUI::getStatusBarHeight()const
{
	return StatusBarHeight;
}

void GUI::changeMenuItemTo(MENU_ITEM index, string filePath)
{

	if (filePathsForMenuItem->find(index) == filePathsForMenuItem->end()) {
		// not found
		filePathsForMenuItem->insert({ index, filePath });
	}
	else {
		// found
		filePathsForMenuItem->find(index)->second = filePath;
	}

	try
	{
		filePathsForMenuItem->find(index)->second = filePath;

	}
	catch (const char* msg)
	{
		filePathsForMenuItem->insert({ index, filePath });
	}
}

string GUI::getFilePathForMenuItemAt(MENU_ITEM mi)
{
	return filePathsForMenuItem->at(mi);
}

window* GUI::getWindow()
{
	return pWind;
}

void GUI::RedrawTempCrs(const Course* pCrs, STATE_DRAG_CRS sdc)
{
	pWind->SetPen(HiColor, 2);
	if(sdc ==OK)
		pWind->SetBrush(GREEN);
	else 
		pWind->SetBrush(RED);

	graphicsInfo gInfo = pCrs->getGfxInfoComp().topLeft;
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);

	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD, BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);

	ostringstream crd;
	crd << "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT / 2, crd.str());
}

bool GUI::isPointInMenuBarRange(int x, int y)
{
	if (x > 0 && x < WindWidth && y>0 && y < MenuBarHeight)
		return true;
	return false;
}

void GUI::DrawOnlyTwoCourses(const Course* crs1, const Course* crs2)
{
	DrawCourse(crs1);
	DrawCourse(crs2);
}

GUI::~GUI()
{
	delete pWind;
}
