#pragma once
#include"Actions/Action.h"
#include "ActionChangeMenuItemTo.h"
class ActionValidityReport : public Action
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionValidityReport(Registrar*);
	bool virtual Execute();
	virtual ~ActionValidityReport();

};
