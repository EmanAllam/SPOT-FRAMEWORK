#include "ActionImportRules.h"
#include "ActionImportCourseCatalog.h"
ActionImportRules::ActionImportRules(Registrar* pReg):Action(pReg)
{
	actions->push_back(new ActionImportCourseCatalog(pReg));
}

bool ActionImportRules::Execute()
{
	for (auto action = actions->begin(); action != actions->end(); ++action)
	{
		(**action).Execute();
	}
	return true;
}

ActionImportRules::~ActionImportRules()
{
	for (auto action = actions->begin(); action != actions->end(); ++actions)
	{
		delete *action;
	}

}
