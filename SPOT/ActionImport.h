#pragma once
#include "Actions/Action.h"
#include <string>
#include <fstream>
using namespace std;

class ActionImport :public Action
{
protected:
	ifstream file;
	string getFilePath();
	//This function should make sure that the file start from scratch
	void beginTheFile();

public:

	ActionImport(Registrar*);
	bool virtual Execute();
	virtual ~ActionImport();

};

