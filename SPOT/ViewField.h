#pragma once
#include "Drawable_Parent.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"


static string BACKGROUN_PATH_FILE = "GUI\\Images\\\Background.jpg";



//This class is made specifically for all view fields ex: TextField, ListField. it has some common attributes shared between them.
class ViewField :
    public Drawable_Parent
{

protected:

	//is used in many cases to have proper space between object on screen.
    const int MARGIN_VALUE = 15;
	//should be specified by caller, as to make while not clicked; show a color similar to what was origianll
    color BACKGROUND_COLOR;
	//color used by university
	const color ZewailCityBackground = color(1, 168, 187);

	int width;
	int height;
	//to state wether if that object has been clicked on or not
	enum STATE
	{
		CLICKED,
		NOT_CLICKED
	};

	STATE current_state;
	window* pWind;
	ViewField(window* pWind);
	//could be used in some cases as a hint to user that he should enter text in text Field for example.
	virtual void DrawError();
	//draws the object, while it's not cliked
	void DrawMeClicked()const;
	//draws the object while it's clicked.
	void DrawMeNotClicked()const;
	bool isXYinMe(int x, int y); 
public:
	virtual int getWidth();
	virtual int getHeight();

};

