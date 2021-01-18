#include"Actions/Action.h"
#include "ActionChangeMenuItemTo.h"
class ActionAddNotes : public Action
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionAddNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddNotes();

};