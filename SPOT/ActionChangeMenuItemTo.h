#pragma once
#include "Actions/Action.h"
#include "GUI/GUI.h"
#include<string>
using namespace std;
class ActionChangeMenuItemTo :
    public Action

{
    //this will save last saved file path, to go back the use wants.
    GUI::MENU_ITEM selectedMenuItem;
    string filePath;


public:
    ActionChangeMenuItemTo(Registrar*, GUI::MENU_ITEM);
    bool virtual Execute();
    bool reverseExcute();
};

