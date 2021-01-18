#include "ActionChangeMenuItemTo.h"
#include "Registrar.h"
#include "Actions/Action.h"
#include "GUI/GUI.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"

ActionChangeMenuItemTo::ActionChangeMenuItemTo(Registrar* pReg, GUI::MENU_ITEM mnItem) : Action(pReg)
{
    selectedMenuItem = mnItem;
    filePath = pReg->getGUI()->getFilePathForMenuItemAt(mnItem);
}
bool ActionChangeMenuItemTo::Execute()
{
    //Drawing an outer red rectangle
    pReg->getGUI()->getWindow()->SetPen(RED);
    pReg->getGUI()->getWindow()->SetBrush(RED);
    pReg->getGUI()->getWindow()->DrawRectangle(selectedMenuItem * MenuItemWidth, 0, selectedMenuItem * MenuItemWidth + MenuItemWidth, MenuBarHeight);
    int widthOfRedLine = 3;
    pReg->getGUI()->getWindow()->DrawImage(filePath, selectedMenuItem * MenuItemWidth+ widthOfRedLine, widthOfRedLine, MenuItemWidth - 2* widthOfRedLine, MenuBarHeight-2* widthOfRedLine);

    return true;
}

bool ActionChangeMenuItemTo::reverseExcute()
{
    pReg->getGUI()->getWindow()->DrawImage(filePath, selectedMenuItem * MenuItemWidth , 0, MenuItemWidth , MenuBarHeight);
    return true;
}
