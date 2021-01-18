
#pragma once
#include "Actions//Action.h"
#include "Rules.h"
#include "DEFs.h"
#include <vector>
#include "Student.h"
class ActionImpReq :
	public Action
{
public:
	ActionImpReq(Registrar*);
	bool virtual Execute();
	virtual ~ActionImpReq();
	void functionImpReq(string);
	void codesToVector(ifstream&, vector<Course_Code>&);
};
