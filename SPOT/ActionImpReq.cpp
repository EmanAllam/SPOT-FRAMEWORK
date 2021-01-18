#include "ActionImpReq.h"
#include <fstream>
#include "Registrar.h"
#include <iostream>
ActionImpReq::ActionImpReq(Registrar* p) :Action(p)
{
}

void ActionImpReq::codesToVector(ifstream& file, vector<Course_Code>& vector)
{
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];
	file.getline(line, size);
	pch = strtok_s(line, ",", &context);
	while (pch != NULL)
	{
		vector.push_back(pch);
		pch = strtok_s(NULL, ",", &context);
	}
}

void ActionImpReq::functionImpReq(string filename)
{
	Rules newRules;
	int temp[7];
	ifstream infile(filename);
	if (!infile)
	{
		cout << "Requirements file failure";
	}
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];

	//loop to get:  1.TotalCredits, 2.ReqUnivCreditsCompulsory & ReqUnivCreditsElective, 3.ReqTrackCredits, 4.ReqMajorCreditsCompulsory & ReqMajorCreditsElective, 5.ConcentrationsNumber.
	int c = 0; //counter on the words as i is a counter on lines
	for (int i = 0; i < 5; i++) 
	{
		temp[c] = 0;
		infile.getline(line, size);
		pch = strtok_s(line, ",", &context);
		while (pch != NULL)
		{
			temp[c] = stoi(pch);
			pch = strtok_s(NULL, ",", &context);
			c++;
		}
	}
	newRules.TotalCredits = temp[0];
	newRules.ReqUnivCreditsCompulsory = temp[1];
	newRules.ReqUnivCreditsElective = temp[2];
	newRules.ReqTrackCredits = temp[3];
	newRules.ReqMajorCreditsCompulsory = temp[4];
	newRules.ReqMajorCreditsElective = temp[5];
	newRules.ConcentrationsNumber = temp[6];

	//6.get ReqConcentrationCredits
	infile.getline(line, size);
	pch = strtok_s(line, ",", &context);
	if (newRules.ConcentrationsNumber != 0)
	{
		for (int i = 0; i < newRules.ConcentrationsNumber; i++) //get number of elec& compulsory credits of concentrations
		{
			temp[0] = 0;
			for (int j = 0; j < 2; j++) //2 iterations to get 1-compulsory, 2-elective and store their sum in temp[0]
			{
				temp[0] += stoi(pch); //temp used to store sum
				pch = strtok_s(NULL, ",", &context);
			}
			newRules.ReqConcentrationCredits.push_back(temp[0]);
		}
	}
	else
	{
		newRules.ReqConcentrationCredits.push_back(0);
	}

	//get 7.UnivCompulsory
	codesToVector(infile, newRules.UnivCompulsory);

	//get 8.UnivElective
	codesToVector(infile, newRules.UnivElective);

	//get 9.TrackCompulsory
	codesToVector(infile, newRules.TrackCompulsory);

	//10.get MajorCompulsory
	codesToVector(infile, newRules.MajorCompulsory);
	//11.get MajorElective
	codesToVector(infile, newRules.MajorElective);

	//12. ... get concentrations Compulsory and elective courses
	for (int i = 0; i < newRules.ConcentrationsNumber; i++)
	{
		codesToVector(infile, newRules.ConcentrationsCompulsory[i]);
		codesToVector(infile, newRules.ConcentrationsElective[i]);
	}

	infile.close();
	//pass the rules to the registrar
	pReg->setRules(newRules);
}

bool ActionImpReq::Execute()
{
	switch (pReg->getSignedStudest()->getMajor())
	{
	case CIE:
		functionImpReq("Files\\CIE-Requirements.txt");
		break;
	case ENV:
		functionImpReq("Files\\ENV-Requirements.txt");
		break;
	case NANE:
		functionImpReq("Files\\NANENG-Requirements.txt");
		break;
	case REE:
		functionImpReq("Files\\REE-Requirements.txt");
		break;
	case SPC:
		functionImpReq("Files\\SPC-Requirements.txt");
		break;
	case PEU:
		functionImpReq("Files\\PEU-Requirements.txt");
		break;
	default:
		break;
	};

	return true;
}

ActionImpReq::~ActionImpReq()
{

}