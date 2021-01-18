#pragma once
#include "Actions/Action.h"
#include <vector>
using namespace std;

/*
	This clas is supposed to to iterate over vector of actions to excute them 
	as they preliminary to the prgrogam. as to make the work for registrar easier just 
	it will create object for that class.
*/
class ActionImportRules :
    public Action
{
	vector<Action*>* actions= new vector<Action*>;

public:

	ActionImportRules(Registrar*);
	bool virtual Execute();
	virtual ~ActionImportRules();
};

