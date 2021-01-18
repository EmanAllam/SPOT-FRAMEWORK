#include"Actions/Action.h"
#include "ActionShowNotes.h"
#include"Registrar.h"
#include<iostream>
#include"GUI/GUI.h"
#include"DEFs.h"
#include <fstream>
#include<string>
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
ActionShowNotes::ActionShowNotes(Registrar* p) :Action(p)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_SHOW_NOTES, "GUI\\Images\\Menu\\ShowNotes_borded.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_SHOW_NOTES);

}
bool ActionShowNotes::Execute()
{
	actionChangeMenuItemTo->Execute();
	GUI* pGUI = pReg->getGUI();
	string LastNote;
	ifstream myfile("Files\\Notes.txt");
	getline(myfile, LastNote);
	pGUI->PrintMsg(LastNote);
	ActionData actData = pReg->getGUI()->GetUserAction();
	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;
}
ActionShowNotes::~ActionShowNotes()
{

}
