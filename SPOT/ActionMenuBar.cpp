#include "ActionMenuBar.h"
#include "GUI/GUI.h"
ActionMenuBar::ActionMenuBar(Registrar* pReg, GUI::MENU_ITEM mn):Action(pReg)
{
    iconBoundaries.topLeft.x = mn * MenuItemWidth + widthOfBlackLine;
    iconBoundaries.topLeft.y = 0;
    iconBoundaries.bottomRight.x = mn * MenuItemWidth + widthOfBlackLine + MenuItemWidth;
    iconBoundaries.bottomRight.y = CRS_HEIGHT;
}

bool ActionMenuBar::isClose(int x, int y)
{
    if (x >= iconBoundaries.topLeft.x && x <= iconBoundaries.bottomRight.x
        && y >= iconBoundaries.topLeft.y && y <= iconBoundaries.bottomRight.y)
    {
        return true;
    }
    return false;
}
