#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionShowGpa :
    public Action
{
public:
	ActionShowGpa(Registrar*);
	bool virtual Execute();
	virtual ~ActionShowGpa();
};

