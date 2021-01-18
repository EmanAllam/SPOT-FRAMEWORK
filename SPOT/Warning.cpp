#include "Warning.h"
#include "GUI/GUI.h"
#include <iostream>
#include <sstream>
#include <string>
#include "BasicError.h"


Warning::Warning()
{
	warningMsg = "";
}


string Warning::getContent() const
{
	return warningMsg;
}

void Warning::AddContent(string new_warningMsg)
{
	ostringstream stream;
	stream << warningMsg << new_warningMsg << "\n";
	warningMsg = stream.str();
}

void Warning::ClearWarnings()
{
	warningMsg = "";
}

void Warning :: saveTxtFile()
{
	std::fstream fs;
	fs.open("Files//Warning.txt", std::fstream::out);
	fs << warningMsg;
	fs.close();
}


void Warning::DrawMe(GUI* pG) const
{
	pG->DrawWarning(this);
}