#pragma once

struct graphicsInfo
{
	//coords of left corner of rectangular area where this obj should be drawn
	int x, y;
};

/*
	Makes it faster to check for user clicks.
	and even the memery used after using it is not too big. less than 1 Mega.
*/
struct graphicsInfoComprehensive
{
	graphicsInfo topLeft;
	graphicsInfo bottomRight;
};

class Drawable_Parent
{
protected:
	//Info required for drawing
	graphicsInfoComprehensive GfxInfoComp;

public:
	Drawable_Parent();
	void setGfxInfoComp(graphicsInfoComprehensive);
	graphicsInfoComprehensive getGfxInfoComp() const;
	void virtual DrawMe() const;
	virtual ~Drawable_Parent();
	
};

