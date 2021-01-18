#pragma once
#include "..\Drawable_Parent.h"
class GUI;


//constants related to objects to be drawn
enum
{
	CRS_WIDTH = 70,		//width of course rectangle to be drawn on screen
	CRS_HEIGHT = 30,	//Height of course rectangle to be drawn on screen
	//PLAN_YEAR_WIDTH = CRS_WIDTH * 4,	//width of plan year rectangle to be drawn on screen
	//PLAN_YEAR_HEIGHT	//Height of play year rectangle to be drawn on screen
};

//Used for drawing and displaying the academic years.
static const int 
				  WIDTH_YEAR_WORD = 80,
				  WIDTH_SEMESTER_WORD = 60,
				  VERTICAL_SPACE_BETWEEN_YEARS = 5,
				  VERTICAL_SPACE_BETWEEN_SEMESTER_ = 3,
				  HORIZENTAL_SPACE_BETWEEN_COURSES_ = 5;
//const int VERTICAL_SPACE_BETWEEN_ONE_LIST_ITEMS = 0;

//Base class for all drawable classes
class Drawable
	:public Drawable_Parent
{
protected:
	//Info required for drawing
	graphicsInfo GfxInfo;
	//graphicsInfoComprehensive GfxInfoComp;

	bool Selected;	//is this obj selected (to highlight when drawing)

	

public:
	Drawable();
	void setGfxInfo(graphicsInfo);
	graphicsInfo getGfxInfo() const;
	void setGfxInfoComp(graphicsInfoComprehensive);
	graphicsInfoComprehensive getGfxInfoComp() const;
	void setSelected(bool );
	bool isSelected() const;
	void virtual DrawMe(GUI*) const = 0;
	virtual ~Drawable();
};

