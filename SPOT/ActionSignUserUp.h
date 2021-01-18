#pragma once
#include "Actions/Action.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include <string>
#include "Text_field.h"
#include "ListImagesFields.h"
#include "ButtonField.h"
using namespace std;
class ActionSignUserUp :
    public Action
{

	window* pWind;
	const int WINDOW_HEIGHT =340;
	const int WINDOW_WIDTH = 650;
	//top left point
	const int X_S = 307;
	const int Y_S = 170;
	const int MARGIN_VALUE = 15;
	const int TEXT_FIELD_WIDTH = 250;
	const int TEXT_FIELD_HEIGHT = 60;
	color BkGrndColor = LIGHTGRAY;	
	color TEXT_FIELD_COLOR_NOT_CLCKED = DARKGRAY;
	const int TEXT__FONT_SIZE = 17;

	
	TextField* firstName_textField =nullptr;
	TextField* lastName_textField = nullptr;
	ListImagesFields* majorsListField = nullptr;
	ButtonField* DoneButton=nullptr;

	MAJORS lastMajrSelected;
public:
	ActionSignUserUp(Registrar* p);
	//Execute action (code depends on action type)
	bool Execute(); //pure virtual
	void ClearDrawingArea() const;
	//this function will perform the proper calculations to calculate the top left point of the next text field at the same horizental line.
	void UpdateInterface()const ;
	//it wall call all textfield specified in that class and draw them
	void DrawAllTextFields() const;
	//it will call drawAnimated from one of textfield and give other as arry as argument to it to be well animated
	void DrawAnimatedTextField(string hint, int x_s, int x_y)const;
	//it will check if the position where use clicked in a text field or not.
	TextField* getTextFieldClicked(int x, int y) const;
	//uses the DrawString func with proper argument
	void DrawSelectMajorString()const;
	//used to draw essential "Select major" sentenct
	void DrawString(string text, int x, int y) const;
	//it will call listImagedFiled with proper file pathe to draw all of them.
	void DrawMajors ()const;
	//simply it will draw all button in that screen 
	void DrawButton()const;
	//this functions should do all necessary actions when user clicks on Donw. the bool return indicates wether the registrar should update the interface or not.
	bool  DoneClicked()const;
	virtual ~ActionSignUserUp();

};

