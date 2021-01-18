#pragma once
#include "../SPOT/Actions/Action.h"
#include "Registrar.h"

class ActionMarkAsDone :
    public Action
{
public:
	ActionMarkAsDone(Registrar*);
	bool virtual Execute();
	virtual ~ActionMarkAsDone();
};

