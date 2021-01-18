#include "Drawable_Parent.h"

Drawable_Parent::Drawable_Parent()
{
}

void Drawable_Parent::setGfxInfoComp(const graphicsInfoComprehensive g)
{
	GfxInfoComp = g;
}

graphicsInfoComprehensive Drawable_Parent::getGfxInfoComp() const
{
	return GfxInfoComp;
}

void Drawable_Parent::DrawMe() const
{
}

Drawable_Parent::~Drawable_Parent()
{
}
