#pragma once
#include "Actions/Action.h"
#include "ActionShowCourseInfo.h"
#include <fstream>
#include "Registrar.h"
#include <iostream>
#include "Rules.h"
#include "DEFs.h"
#include <vector>
#include "ActionChangeMenuItemTo.h"
#include "ActionMenuBar.h"
class ActionDeleteCourse :
	public ActionMenuBar
{

	ActionChangeMenuItemTo* actionChangeMenuItemTo;
public:
	ActionDeleteCourse(Registrar*);
	bool virtual Execute();

	bool Execute(graphicsInfo ginfo);
	bool Execute(Course* crs);
	virtual ~ActionDeleteCourse();
};