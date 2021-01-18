#pragma once
#include "../SPOT/Actions/Action.h"
#include "Registrar.h"


class ActionSupportMinor :
    public Action
{
public:
	ActionSupportMinor(Registrar*);
	bool virtual Execute();
	virtual ~ActionSupportMinor();
};

