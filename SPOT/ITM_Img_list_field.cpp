#include "ITM_Img_list_field.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"
#include "DEFs.h"
#include <iostream>
using namespace std;
ITM_Img_list_field::ITM_Img_list_field(window* pWind, string filePath, MAJORS major_flag, int topLeftX, int topLeftY):ViewField(pWind)
{

	setWidtheHeightDefualt();
	this->imgFilePath = filePath;
	GfxInfoComp.topLeft.x = topLeftX;
	GfxInfoComp.topLeft.y = topLeftY;
	GfxInfoComp.bottomRight.x = topLeftX+ width;
	GfxInfoComp.bottomRight.y = topLeftY+ height;
	this->imgFilePath = filePath;
	this->major_flag = major_flag;
}

ITM_Img_list_field::ITM_Img_list_field(window* pWind, string filePath, MAJORS major_flag):ViewField(pWind)
{
	setWidtheHeightDefualt();
	this->imgFilePath = filePath;
	this->imgFilePath = filePath;
	this->major_flag = major_flag;

}
void ITM_Img_list_field::setWidtheHeightDefualt()
{
	setWidtheHeight(70, 50);
}
void ITM_Img_list_field::setWidtheHeight(int w, int h)
{
	setWidth(w);
	setHeight(h);
}
void ITM_Img_list_field::setWidth(int width)
{
	this->width = width;
}

void ITM_Img_list_field::setHeight(int height)
{
	this->height = height;
}

void ITM_Img_list_field::DrawMe() const
{
	if (current_state == CLICKED)
		DrawMeClicked();
	else
		DrawMeNotClicked();
	

}

void ITM_Img_list_field::DrawMeClicked() const
{
	pWind->SetBrush(GREEN);
	pWind->SetPen(GREEN);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x+10 , GfxInfoComp.topLeft.y+10 , GfxInfoComp.bottomRight.x +5, GfxInfoComp.bottomRight.y+5);
	DrawMeNotClicked();
}

void ITM_Img_list_field::DrawMeNotClicked() const
{
	pWind->DrawImage(imgFilePath, GfxInfoComp.topLeft.x + MARGIN_VALUE, GfxInfoComp.topLeft.y + MARGIN_VALUE, width - MARGIN_VALUE, height - MARGIN_VALUE);

}
MAJORS ITM_Img_list_field::getMajorFlag() const
{
	return major_flag;
}
void ITM_Img_list_field::setTopLeft(graphicsInfoComprehensive gfc)
{
	this->GfxInfoComp = gfc;

}
void ITM_Img_list_field::setTopLeft(int topLeftX, int topLeftY)
{
	GfxInfoComp.topLeft.x = topLeftX;
	GfxInfoComp.topLeft.y = topLeftY;
	GfxInfoComp.bottomRight.x = topLeftX + width;
	GfxInfoComp.bottomRight.y = topLeftY + height;
}
void ITM_Img_list_field::setTopLeftAtHorizentalLine(ITM_Img_list_field* lastImage)
{
	setTopLeft(lastImage->getGfxInfoComp().topLeft.x + lastImage->getWidth() + MARGIN_VALUE, lastImage->getGfxInfoComp().topLeft.y);
}
int ITM_Img_list_field::getWidth()
{
	return width;
}
int ITM_Img_list_field::getHeight()
{
	return height;
}
bool ITM_Img_list_field::isXYinMe(int x, int y)
{
	if (x >= GfxInfoComp.topLeft.x &&
		x <= GfxInfoComp.bottomRight.x
		&& y >= GfxInfoComp.topLeft.y
		&& y <= GfxInfoComp.bottomRight.y)
	{
		return true;
	}
	return false;
}

void ITM_Img_list_field::setSelected(bool sel)
{
	clearArea();
	current_state = sel ? CLICKED : NOT_CLICKED;
	DrawMe();
}

void ITM_Img_list_field::clearArea()
{
	pWind->SetPen(LIGHTGRAY);
	pWind->SetBrush(LIGHTGRAY);
	pWind->DrawRectangle(GfxInfoComp.topLeft.x + 10, GfxInfoComp.topLeft.y + 10, GfxInfoComp.bottomRight.x + 5, GfxInfoComp.bottomRight.y + 5);
}

bool ITM_Img_list_field::isSelected() const
{
	return current_state == CLICKED;
}
