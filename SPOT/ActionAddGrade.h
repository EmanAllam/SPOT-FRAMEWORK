#pragma once
#include "../SPOT/Actions/Action.h"
#include "Registrar.h"

class ActionAddGrade :
    public Action
{
public:
	ActionAddGrade(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddGrade();
};

