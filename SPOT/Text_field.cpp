#include "Text_field.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include <string>
using namespace std;
#include <iostream>
#include "ViewField.h"
TextField::TextField(window* pWind, int Top_left_x, int Top_left_y, color BACKGROUND_COLOR): ViewField(pWind)
{
	GfxInfoComp.topLeft.x = Top_left_x;
	GfxInfoComp.topLeft.y = Top_left_y;
	GfxInfoComp.bottomRight.x = Top_left_x + TEXT_FIELD_WIDTH;
	GfxInfoComp.bottomRight.y = Top_left_y + TEXT_FIELD_HEIGHT;

	this->pWind = pWind;
	this->BACKGROUND_COLOR = BACKGROUND_COLOR;
	height = TEXT_FIELD_HEIGHT;
	width = TEXT_FIELD_WIDTH;
}

void TextField::setHint(string hint)
{
	this->hint = hint;
}

void TextField::DrawMe()
{
	ClearArea();
	if (current_state == CLICKED)
		DrawTextFieldClicked();
	else
		DrawTextFieldNotClicked();

}

void TextField::DrawTextFieldClicked()
{
	pWind->SetBrush(ZewailCityBackground);
	pWind->SetPen(ZewailCityBackground);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x+10, GfxInfoComp.topLeft.y+10, GfxInfoComp.bottomRight.x-10, GfxInfoComp.bottomRight.y-10);
	//basically what will be drawn next is similar to drwing while not clicked
	DrawTextFieldNotClicked();
	
}

void TextField::DrawTextFieldNotClicked()
{
	pWind->DrawRectangle(GfxInfoComp.topLeft.x + MARGIN_VALUE, GfxInfoComp.topLeft.y + MARGIN_VALUE, GfxInfoComp.bottomRight.x - MARGIN_VALUE, GfxInfoComp.bottomRight.y -MARGIN_VALUE);
	printWordUserTpyed();

}
void TextField::printWordUserTpyed()const
{
	pWind->SetPen(TEXT_FIELD_COLOR_NOT_CLCKED);
	pWind->SetBrush(TEXT_FIELD_COLOR_NOT_CLCKED);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x + MARGIN_VALUE, GfxInfoComp.topLeft.y + MARGIN_VALUE, GfxInfoComp.bottomRight.x - MARGIN_VALUE, GfxInfoComp.bottomRight.y - MARGIN_VALUE);


	pWind->SetPen(BLACK);
	pWind->SetFont(TEXT_FONT_SIZE, BOLD, BY_NAME, "Arial");
	if (words.size() == 0)
	{
		//it will print the hint.
		pWind->DrawString(GfxInfoComp.topLeft.x + 2 * MARGIN_VALUE, GfxInfoComp.topLeft.y + 2 * MARGIN_VALUE, hint);
	}
	else 
	{
		pWind->DrawString(GfxInfoComp.topLeft.x + 2 * MARGIN_VALUE, GfxInfoComp.topLeft.y + 2 * MARGIN_VALUE, words);
	}
	
}



void TextField::DrawMeAnimatedEntering(TextField aryTextFields[], int size)
{
	int nextWidth = 10;
	while (nextWidth <= TEXT_FIELD_WIDTH)
	{
		ClearArea();
		for (int i = 0; i < size; i++)
		{
		
			aryTextFields[i].DrawTextFieldWithWidth(nextWidth);
			
		}

		nextWidth += 10;
		Sleep(10);

	}
	for (int i = 0; i < size; i++)
	{

		aryTextFields[i].DrawMe();
	}

}


void TextField::DrawTextFieldWithWidth(int width) const
{
	pWind->SetBrush(TEXT_FIELD_COLOR_NOT_CLCKED);
	pWind->SetPen(TEXT_FIELD_COLOR_NOT_CLCKED);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x , GfxInfoComp.topLeft.y , GfxInfoComp.topLeft.x + +width, GfxInfoComp.bottomRight.y);
	
}

void TextField::DrawError()
{
	pWind->SetBrush(RED);
	pWind->SetPen(RED);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x + 10, GfxInfoComp.topLeft.y + 10, GfxInfoComp.bottomRight.x - 10, GfxInfoComp.bottomRight.y - 10);
}



void TextField::setPressed(bool state)
{
	current_state = state ? CLICKED : NOT_CLICKED;
	DrawMe();
}

void TextField::switchState()
{
	if (current_state == CLICKED)
		setPressed(false);
	else
		setPressed(true);
	storeStringIfClicked();
}

bool TextField::isPressed()
{
	return current_state == CLICKED;
}

void TextField::ClearArea()
{
	pWind->SetPen(BACKGROUND_COLOR);
	pWind->SetBrush(BACKGROUND_COLOR);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x, GfxInfoComp.topLeft.y, GfxInfoComp.bottomRight.x, GfxInfoComp.bottomRight.y);
}

void TextField::getNextTopLeftHorizental(int& newX)const
{
	newX =GfxInfoComp.bottomRight.x+ 20;
}

bool TextField::isXYinMe(int x, int y)
{
	if (x >= GfxInfoComp.topLeft.x && x <= GfxInfoComp.bottomRight.x
		&& y >= GfxInfoComp.topLeft.y && y <= GfxInfoComp.bottomRight.y)
	{
		return true;
	}
	return false;
}

string TextField::getHint()
{
	return hint;
}

void TextField::storeStringIfClicked()
{

	if (current_state == CLICKED)
	{
		char Key;
		bool shouldContinue = true;;
		while (shouldContinue)
		{
			pWind->WaitKeyPress(Key);

			switch (Key)
			{
			case 27: //ESCAPE key is pressed
				switchState();
				return;

			case 13:		//ENTER key is pressed
				switchState();
				return;

			case 8:		//BackSpace is pressed
				if (words.size() > 0)
					words.resize(words.size() - 1);
				break;

			default:
				words += Key;
			};

			printWordUserTpyed();
		}
	}
}

string TextField::getFinalStringUserTyped()
{
	if (words.size() == 0)
		return "";
	return words;
}

void TextField::setWords(string words)
{
	this->words = words;
	DrawMe();
}


