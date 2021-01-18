#include "ViewField.h"
#include "GUI/CMUgraphicsLib\CMUgraphics.h"

ViewField::ViewField(window* pWind)
{
	this->pWind = pWind;
	current_state = NOT_CLICKED;
}

void ViewField::DrawError()
{
}

void ViewField::DrawMeClicked()const
{
}

void ViewField::DrawMeNotClicked()const
{
}

bool ViewField::isXYinMe(int x, int y)
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

int ViewField::getWidth()
{
	return width;
}

int ViewField::getHeight()
{
	return height;
}
