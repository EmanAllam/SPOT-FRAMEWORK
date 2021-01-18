#include"Actions/Action.h"
#include "ActionAddNotes.h"
#include"Registrar.h"
#include<iostream>
#include <fstream>
#include<string>
#include "ActionChangeMenuItemTo.h"

using namespace std;
ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
	//actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD_NOTES, "GUI\\Images\\Menu\\Add_note_borderd.jpg");
	actionChangeMenuItemTo = new ActionChangeMenuItemTo(pReg, GUI::ITM_ADD_NOTES);

}

bool ActionAddNotes::Execute()
{
	actionChangeMenuItemTo->Execute();

	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("Add Notes to Current Study Plan: ");
	string Note = pGUI->GetSrting();
	ofstream myfile;
	myfile.open("Files\\Notes.txt");
	myfile << Note << endl;
	myfile.close();
	actionChangeMenuItemTo->reverseExcute();
	delete actionChangeMenuItemTo;
	return true;
}

ActionAddNotes::~ActionAddNotes()
{

}