#pragma once
#include "Actions/Action.h"
#include "ActionChangeMenuItemTo.h"
#include "ActionMenuBar.h"

class ActionChangeByCode :
    public ActionMenuBar
{
    ActionChangeMenuItemTo* actionChangeMenuItemTo;
    bool isWrong = false;
public:
    ActionChangeByCode(Registrar*);
    bool DeleteAndAdd(string desiredCrs, ActionData actData, SEMESTER sem, int  year);
    bool virtual Execute();
    virtual ~ActionChangeByCode();

};
