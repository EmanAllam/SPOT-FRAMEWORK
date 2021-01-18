#pragma once
#include "Action.h"
#include "..\ActionChangeMenuItemTo.h"
#include "..\ActionMenuBar.h"
//Class responsible for adding course action
class ActionAddCourse :
	public ActionMenuBar
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionAddCourse(Registrar*);
	bool virtual Execute();
	bool Execute(Course* crs, SEMESTER& sem, int year);
	virtual ~ActionAddCourse();
};

