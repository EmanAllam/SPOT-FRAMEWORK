#pragma once
#include "Actions/Action.h"
#include "Courses/Course.h"
#include "ActionChangeMenuItemTo.h"
#include "ActionMenuBar.h"

class ActionDragAndDropCrs :
    public ActionMenuBar
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionDragAndDropCrs(Registrar*);
	bool virtual Execute();
	virtual ~ActionDragAndDropCrs();
	void showInfo(Course*);
};

