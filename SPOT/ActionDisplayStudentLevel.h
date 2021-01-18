#pragma once
#include "../SPOT/Actions/Action.h"
#include "Registrar.h"


class ActionDisplayStudentLevel :
    public Action
{
public:
	ActionDisplayStudentLevel(Registrar*);
	bool virtual Execute();
	virtual ~ActionDisplayStudentLevel();
};

