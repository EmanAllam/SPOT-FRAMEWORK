#pragma once
#include "Actions/Action.h"
#include "Courses/Course.h"
class ActionShowCourseInfo
	:public Action
{
	Course* crsClicked;

public:
	ActionShowCourseInfo(Registrar*,Course* crsClicked);
	bool virtual Execute();
	virtual ~ActionShowCourseInfo();
};

