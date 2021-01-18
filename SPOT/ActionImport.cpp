#include "ActionImport.h"
#include  "Registrar.h"

ActionImport::ActionImport(Registrar* pReg) :Action(pReg)
{
}

bool ActionImport::Execute()
{
	return false;
}

ActionImport::~ActionImport()
{
	file.close();
}

string ActionImport::getFilePath()
{
	return "Files\\";
}

void ActionImport::beginTheFile()
{
	file.clear();
	file.seekg(0);
	//pReg->getRules();
}
