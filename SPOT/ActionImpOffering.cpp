#include "ActionImpOffering.h"
#include <fstream>
#include "Registrar.h"
#include <iostream>
ActionImpOffering::ActionImpOffering(Registrar* p) :Action(p)
{}


bool ActionImpOffering::Execute()
{
	Rules newRules;
	ifstream infile("Files\\Offerings.txt");
	string dummy;
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];

	if (!infile)
	{
		cout << "File open failure";
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			infile.getline(line, size);
			//get year title.
			pch = strtok_s(line, ",", &context);
			newRules.OffringsList[i].Year = pch;
			//use dummy variable to skip semester name.
			dummy = pch;
			pch = strtok_s(NULL, ",", &context);
			//saving the courses
			while (pch != NULL)
			{
				newRules.OffringsList[i].Offerings[j].push_back(pch);
				pch = strtok_s(NULL, ",", &context);
			}
		}
	}
	infile.close();
	pReg->setOfferingRules(newRules);
	return true;
}

ActionImpOffering::~ActionImpOffering()
{

}