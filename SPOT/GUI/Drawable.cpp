#include "Drawable.h"



Drawable::Drawable()
{
	Selected = false;
}

Drawable::~Drawable()
{
}

void Drawable::setGfxInfo(graphicsInfo g)
{
	GfxInfo = g;
}

graphicsInfo Drawable::getGfxInfo() const
{
	return GfxInfo;
}

bool Drawable::isSelected() const
{
	return Selected;
}
void Drawable::setGfxInfoComp(graphicsInfoComprehensive g)
{

	GfxInfoComp = g;
}
graphicsInfoComprehensive Drawable::getGfxInfoComp() const
{
	//AHMED:: TODO:: check if it's assined or not.
	return GfxInfoComp;
}
void Drawable::setSelected(bool sel)
{
	Selected = sel;
}

