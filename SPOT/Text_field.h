#pragma once
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include <string>
#include "ViewField.h"
using namespace std;

class TextField
	:public ViewField
{



	const int TEXT_FIELD_WIDTH = 250;
	const int TEXT_FIELD_HEIGHT = 65;
	color TEXT_FIELD_COLOR_CLCKED = LIGHTGRAY;	//Background color
	color TEXT_FIELD_COLOR_NOT_CLCKED = DARKGRAY;//statusbar color
	color TEXT_COLOR = BLACK;
	//this is meant to be the color the main window as while animating and sliding right, it can delete and redraw upon it.

	const int TEXT_FONT_SIZE = 17;
	
	

	string hint;
	string words;

	void DrawTextField();
	void DrawTextFieldClicked();
	void DrawTextFieldNotClicked();
	
public:
	TextField(window* pWind, int Top_left_x, int Top_left_y, color);
	//inherited function, that draws the object, essentially it checks first if it's clicked or not, and rediret it to the prober funtion 
	void DrawMe();
	//for text Field hint is important to enable the user to know what he should write here as an example
	void setHint(string hint);
	//just print what user typed if user types null, it will print hint, if no hint exist. it will print nothin.
	void printWordUserTpyed()const;
	//it's used essentialy for animation. as to have the feeling the goes to left
	void DrawTextFieldWithWidth(int width)const;
	//inherited funtion. that should make use notice he sholuld write it.
	void DrawError();
	//to animate bunch of textFields at the same time. as if I was to make individually. each one will start after the last but here they wory on the same thread
	void DrawMeAnimatedEntering(TextField aryTextFields [], int size);
	void setPressed(bool);
	//if it clicked, i make uncliked, and vice versa
	void switchState();
	bool isPressed();
	//clear what was drawn with the specified backgournd color
	void ClearArea();
	//used to knwo the next x for the next elment at the same horizenal line, taking in considration the maring value
	void getNextTopLeftHorizental(int& newX)const;
	//just checks if user click on it.
	bool isXYinMe(int x, int y);
	string getHint();
	//just check if the user clicked on text field and starts get what use types from keyboard.
	void storeStringIfClicked();
	//return what use typed
	string getFinalStringUserTyped();
	void setWords(string words);


};

