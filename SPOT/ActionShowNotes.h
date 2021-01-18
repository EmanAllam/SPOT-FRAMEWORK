#include"Actions/Action.h"
#include "ActionChangeMenuItemTo.h"

class ActionShowNotes : public Action
{
	ActionChangeMenuItemTo* actionChangeMenuItemTo;

public:
	ActionShowNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionShowNotes();
};