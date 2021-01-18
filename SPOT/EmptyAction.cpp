#include "EmptyAction.h"

EmptyAction::EmptyAction(Registrar* pReg):Action(pReg)
{
}

bool EmptyAction::Execute()
{
    return false;
}

EmptyAction::~EmptyAction()
{
}
