#pragma once
#include"Actions/Action.h"
#include "ActionChangeMenuItemTo.h"
class ActionCheckErrors : public Action
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionCheckErrors(Registrar*);
	bool virtual Execute();
	virtual ~ActionCheckErrors();

};
