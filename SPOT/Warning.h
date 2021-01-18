#pragma once
#include <string>
#include <list>
using namespace std;
#include "DEFs.h"

#include "GUI/Drawable.h"


class Warning : public Drawable
{
	string warningMsg;		

public:
	Warning();
	string getContent() const;
	void AddContent(std::string);
	void ClearWarnings();
	void DrawMe(GUI*) const;
	void saveTxtFile();

};