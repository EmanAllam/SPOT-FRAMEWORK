#pragma once
#include "..\Drawable_Parent.h"
class Registrar; //forward class declaration

//Base class for all possible actions (abstract class)
class Action
{
protected:
	Registrar* pReg;

public:
	Action(Registrar* p) { pReg = p; }
	
	//Execute action (code depends on action type)
	bool virtual Execute() = 0; //pure virtual
	//this function maker the prober calculations to check if user clicked on one of icon on menu bar to cancel the action.
	virtual ~Action() {}
};

