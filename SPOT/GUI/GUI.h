#pragma once
#include <string>
using namespace std;

#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "map"
class Course;
class AcademicYear;
//user interface class
static const int	WindWidth = 1300, WindHeight = 680/*+250*/,	//Window width and height
wx = 15, wy = 15,		//Window starting coordinates
StatusBarHeight = 60,	//Status Bar Height
MenuBarHeight = 50,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
MenuItemWidth = 40;		//Width of each item in the menu

class GUI
{

public:
	//static const string filePathForCloseIcon;
	static enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
						//TODO: Add more items names here



			//Delete course


		ITM_ADD,
		ITM_CHANGE_CRS_BY_CODE,
		ITM_DELETE,			//Add a new course
		ITM_REORDER,
		ITM_ADD_NOTES,  //Add written notes
		ITM_SHOW_NOTES, //Show written notes
		ITM_SETTINGS,
		ITM_COURSE_STATUS,
		ITM_ADD_GRADE,
		ITM_SHOW_GRADE,
		ITM_SUPPORT_MINOR,
		ITM_CNT		    //no. of menu items ==> This should be the last line in this enum


	};

	static enum STATE_DRAG_CRS
	{
		OK, //Means the place is right
		WRONG //meas the place is wrong may between exactly two sems;
	};
private:
	//Some constants for GUI
	



	//color DrawColor = BLACK;		//Drawing color
	color FillColor = YELLOW;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLUE;			//Messages color
	color BkGrndColor = LIGHTGRAY;	//Background color
	color StatusBarColor = DARKGRAY;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";
	color textColor = color(66,52,17);
	const color ZewailCityBackground = color(1, 168, 187);
	//To make it easit to change the picture in menu bar.
	std::map<MENU_ITEM, string>* filePathsForMenuItem = new ::map<MENU_ITEM, string>;


	window* pWind;
public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	void DrawCourse(const Course*);
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;

	//input functions
	ActionData GUI::GetUserAction(string msg) const;
	//This function will not print any msgs, just wait till the user clicks.
	ActionData GUI::GetUserAction() const;
	ActionData GUI::GetCoordAndSenseDelete() const;
	string GetSrting() const;
	int getWindHeight()const;
	int getWindWidth()const;
	int getStatusBarHeight()const;
	void changeMenuItemTo(MENU_ITEM, string filePath);
	string getFilePathForMenuItemAt(MENU_ITEM mi);
	window* getWindow();
	void RedrawTempCrs(const Course*, STATE_DRAG_CRS);
	bool isPointInMenuBarRange(int x, int y);
	void DrawOnlyTwoCourses(const Course* crs1, const Course* crs2);
	~GUI();
};

//filePathForCloseIcon = "GUI\\Images\\Menu\\Cancel.jpg";

