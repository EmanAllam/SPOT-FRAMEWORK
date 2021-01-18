#pragma once
#include "Actions/Action.h"
class EmptyAction
	:public Action
{
	/*
		This class is aimed to do nothing, just it will be returned when switching for ActData
		Ex: when DrawArea-> but no courses found at that place, an object of that class should be returned.
	*/

public:
	EmptyAction(Registrar*);
	bool virtual Execute();
	virtual ~EmptyAction();
};

