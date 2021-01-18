#include "ActionSignUserUp.h"
#include "Registrar.h"
#include "DEFs.h"
#include <iostream>
#include "Text_field.h"
using namespace std;
#include "ITM_Img_list_field.h"
#include "ViewField.h"
#include"DEFs.h"
#include "ListImagesFields.h"

ActionSignUserUp::ActionSignUserUp(Registrar*  pReg) : Action(pReg)
{
	pWind = new window(WINDOW_WIDTH, WINDOW_HEIGHT, X_S, Y_S);
	pWind->ChangeTitle("Zewailian settings");
	
	firstName_textField = new TextField(pWind, 0, 0, BkGrndColor);
	firstName_textField->setHint("First name...");

	int newX = 0;
	firstName_textField->getNextTopLeftHorizental(newX);
	lastName_textField = new TextField(pWind, newX, 0, BkGrndColor);

	lastName_textField->setHint("Last name...");

	majorsListField = new ListImagesFields(pWind, MARGIN_VALUE, (TEXT_FIELD_HEIGHT + firstName_textField->getHeight()));
	DoneButton = new ButtonField(pWind, WINDOW_WIDTH - 170, WINDOW_HEIGHT - 70);

	ClearDrawingArea();
	
}

bool ActionSignUserUp::Execute()
{
	
	
	//this indicated wehter the window should update interface or
	bool isInterfaceUpdate = false;

	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	UpdateInterface();
	//it user came just to edit.
	firstName_textField->setWords(pReg->getSignedStudest()->getFirstName());
	lastName_textField->setWords(pReg->getSignedStudest()->getLastName());
	lastMajrSelected = NOT_DEFINED;
	if (pReg->getSignedStudest()->isUserSigned())
	{
		majorsListField->setSelectedForMajor(pReg->getSignedStudest()->getMajor());
		lastMajrSelected = pReg->getSignedStudest()->getMajor();
	}
	while (true)
	{

		int x, y;
		pWind->GetMouseCoord(x,y);
		if (pWind->GetRed(x, y) == 0.8 && pWind->GetGreen(x, y) == 0.8 && pWind->GetBlue(x, y) == 0.8)
		{
			delete pWind;
			break;
		}
		else if (pWind->GetRed(x, y) == 1 && pWind->GetGreen(x, y) == 1 && pWind->GetBlue(x, y) == 1)
		{
			UpdateInterface();
		}
		int xc, yc;
		ctInput = pWind->GetMouseClick(xc, yc);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			try
			{
				TextField* textFieldClicked = getTextFieldClicked(xc, yc);
				textFieldClicked->switchState();
			}
			catch (const char* msg)
			{

				majorsListField->setSelectedForXY(xc, yc);
			}
			
		}
		if (DoneButton->isButtonClick(x, y) && ctInput == LEFT_CLICK)
		{
			try
			{
				isInterfaceUpdate = DoneClicked();
				delete pWind;
				break;
			}
			catch (const char* msg)
			{
			}
			
		}
	}
	
	return isInterfaceUpdate;
}

TextField* ActionSignUserUp::getTextFieldClicked(int x, int y) const
{
	if (firstName_textField->isXYinMe(x, y))
		return firstName_textField;
	else if (lastName_textField->isXYinMe(x, y))
		return lastName_textField;
	else
		throw "User didn't click here";
}


void ActionSignUserUp::ClearDrawingArea() const
{

	pWind->DrawImage(BACKGROUN_PATH_FILE, 0, 0);
}



void ActionSignUserUp::DrawString(string text, int x, int y)const
{
	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(x, y, text);


}





void ActionSignUserUp::DrawAllTextFields() const
{
	TextField tfs[2] = {*firstName_textField, *lastName_textField};
	firstName_textField->DrawMeAnimatedEntering(tfs, 2);
}

void ActionSignUserUp::UpdateInterface() const
{

	pWind->SetBuffering(true);
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);
	DrawAllTextFields();
	DrawSelectMajorString();
	DrawMajors();
	DrawButton();
	

}
void ActionSignUserUp::DrawButton()const
{
	DoneButton->DrawMe();
}

void ActionSignUserUp::DrawMajors()const
{
	ITM_Img_list_field* imgs[] = {
		new ITM_Img_list_field(pWind, "GUI\\Images\\\Majors\\Major_CIE.jpg",CIE),
		new ITM_Img_list_field(pWind, "GUI\\Images\\\Majors\\Major_NENE.jpg",NANE),
		new ITM_Img_list_field(pWind, "GUI\\Images\\\Majors\\Major_REE.jpg",REE),
		new ITM_Img_list_field(pWind, "GUI\\Images\\\Majors\\Major_ENV.jpg",ENV),
		new ITM_Img_list_field(pWind, "GUI\\Images\\\Majors\\Major_SPC.jpg",SPC),
	};
	majorsListField->addItmImagesAndClear(imgs, 5);
	majorsListField->DrawMe();

}

ActionSignUserUp::~ActionSignUserUp()
{
}

void ActionSignUserUp::DrawSelectMajorString() const
{
	DrawString("Select major: ", MARGIN_VALUE, TEXT_FIELD_HEIGHT + 2 * MARGIN_VALUE);
}

bool ActionSignUserUp::DoneClicked() const
{
	if (majorsListField->isSelected())
	{
		
		pReg->getSignedStudest()->setMajor(majorsListField->getFinalMajorSelected());

		if (firstName_textField->getFinalStringUserTyped().size() >= 0)
		{
			pReg->getSignedStudest()->setFirstName(firstName_textField->getFinalStringUserTyped());
		}
		if(lastName_textField->getFinalStringUserTyped().size() >=0)
			pReg->getSignedStudest()->setLastName(lastName_textField->getFinalStringUserTyped());
		pReg->getSignedStudest()->writeStdData();
		//then user chose another major
		if (lastMajrSelected != NOT_DEFINED && lastMajrSelected != majorsListField->getFinalMajorSelected())
		{
			pReg->loadNewDefaultPlan();
			return true;
		}
		else
			return false;
	}

	else
		throw "Major not selected";
}






