#pragma once
#include "Actions//Action.h"
#include "Rules.h"
#include "DEFs.h"
#include <vector>
class ActionImpOffering :
	public Action
{
public:
	ActionImpOffering(Registrar*);
	bool virtual Execute();
	virtual ~ActionImpOffering();
};