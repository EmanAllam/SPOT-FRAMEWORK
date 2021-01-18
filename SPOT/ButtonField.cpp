#include "ButtonField.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include <iostream>
using namespace std;
ButtonField::ButtonField(window* pWind, int topLeftX, int topLeftY, int width, int height):ButtonField(pWind, topLeftX, topLeftY)
{
	this->width = width;
	this->height = height;
	GfxInfoComp.bottomRight.x = topLeftX + width;
	GfxInfoComp.bottomRight.y = topLeftX + height;
}

ButtonField::ButtonField(window* pWind, int topLeftX, int topLeftY):ViewField(pWind)
{
	width = 100;
	height = 50;
	GfxInfoComp.topLeft.x = topLeftX;
	GfxInfoComp.topLeft.y = topLeftY;
	GfxInfoComp.bottomRight.x = topLeftX + width;
	GfxInfoComp.bottomRight.y = topLeftY + height;
	colorSpecified = ZewailCityBackground;
}

void ButtonField::setColor(color c)
{
	this->colorSpecified = c;
}

void ButtonField::DrawMe()
{
	pWind->SetPen(colorSpecified);
	pWind->SetBrush(colorSpecified);
	pWind->DrawEllipse(GfxInfoComp.topLeft.x, GfxInfoComp.topLeft.y, GfxInfoComp.bottomRight.x, GfxInfoComp.bottomRight.y);
	pWind->SetPen(WHITEONBLACK);
	pWind->SetBrush(WHITEONBLACK);
	pWind->DrawString(GfxInfoComp.topLeft.x + 2*MARGIN_VALUE, GfxInfoComp.topLeft.y + MARGIN_VALUE, "Done");
}

bool ButtonField::isButtonClick(int x, int y)
{
	return isXYinMe(x,y);
}


