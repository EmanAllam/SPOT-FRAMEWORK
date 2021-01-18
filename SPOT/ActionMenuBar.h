#pragma once
#include "Actions\Action.h"
#include "Registrar.h"
#include "GUI/GUI.h"
class ActionMenuBar :
    public Action
{
protected:
    int widthOfBlackLine = 3;
    graphicsInfoComprehensive iconBoundaries;
    ActionMenuBar(Registrar* pReg, GUI::MENU_ITEM);
    bool isClose(int x, int y);

};

