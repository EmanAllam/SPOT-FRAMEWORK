#include "Course.h"
#include "../GUI/GUI.h"
#include <iostream>
#include<string>
#include <list>
#include "../StudyPlan/StudyPlan.h"
using namespace std;



Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
	Done = false;
	Points = 0;
}

void Course::setPreReq(list<Course_Code> pr)
{
	this->PreReq = pr;
}

void Course::setCoReq(list<Course_Code> cr)
{
	this->CoReq = cr;
}

void Course::setType(string type)
{
	this->type = type;
}

void Course::setPoints(string letter, StudyPlan* plan)
{
	int courseCredits=getCredits();
	bool isCourseDone=getDone();

	if (isCourseDone == false) //if not done do not reflect on the gpa (just user puts expected letter)
	{
		if (letter == "A")
			Points = 4.0 * courseCredits;
		else if (letter == "A-")
			Points = 3.7 * courseCredits;
		else if (letter == "B+")
			Points = 3.3 * courseCredits;
		else if (letter == "B")
			Points = 3.0 * courseCredits;
		else if (letter == "B-")
			Points = 2.7 * courseCredits;
		else if (letter == "C+")
			Points = 2.3 * courseCredits;
		else if (letter == "C")
			Points = 2.0 * courseCredits;
		else if (letter == "C-")
			Points = 1.7 * courseCredits;
		else if (letter == "F")
			Points = 0;
		else // pass/fail or drop
			Points = 0;
	}
	else if (isCourseDone == true) //the course is done then reflect the change of the grade on gpa
	{
		double gpa = plan->getGpa();
		int doneCredits = plan->getDoneCredits();

		if (letter == "A")
			gpa = (gpa * doneCredits + 4.0 * courseCredits - Points) / doneCredits;
		else if (letter == "A-")
			gpa = (gpa * doneCredits + 3.7 * courseCredits - Points) / doneCredits;
		else if (letter == "B+")
			gpa = (gpa * doneCredits + 3.3 * courseCredits - Points) / doneCredits;
		else if (letter == "B")
			gpa = (gpa * doneCredits + 3.0 * courseCredits - Points) / doneCredits;
		else if (letter == "B-")
			gpa = (gpa * doneCredits + 2.7 * courseCredits - Points) / doneCredits;
		else if (letter == "C+")
			gpa = (gpa * doneCredits + 2.3 * courseCredits - Points) / doneCredits;
		else if (letter == "C")
			gpa = (gpa * doneCredits + 2.0 * courseCredits - Points) / doneCredits;
		else if (letter == "C-")
			gpa = (gpa * doneCredits + 1.7 * courseCredits - Points) / doneCredits;
		else if (letter == "F")
			gpa = (gpa * doneCredits + 0 * courseCredits - Points) / doneCredits;
		else // pass/fail or drop
			gpa = (gpa * doneCredits + 0 * courseCredits - Points) / doneCredits;

		plan->setGpa(gpa); //set the new  gpa
	}
}

void Course::setDone(StudyPlan* plan, int choice)

{
	int oldDoneCredits = plan->getDoneCredits();
	int newDoneCredits;
	double gpa = plan->getGpa(); 

	//reflect on the GPA the effect of adding or removing DONE credits 
	
	if (Done == false ) //the course is not done yet 
	{
		if (choice != 2 && choice != 3) //will be marked as done
		{
			newDoneCredits = oldDoneCredits + getCredits();
			Done = true;
			gpa = (gpa * oldDoneCredits + Points) / newDoneCredits;
			plan->setDoneCredits(newDoneCredits);
			plan->setGpa(gpa);
		}
	}
	else if (Done == true) //the course WAS marked as done already then unmarked
	{
		if (choice == 2 || choice == 3) //will be marked as undone
		{
			newDoneCredits = oldDoneCredits - getCredits();
			Done = false;
			gpa = (gpa * oldDoneCredits - Points) / newDoneCredits;
			plan->setDoneCredits(newDoneCredits);
			plan->setGpa(gpa);
		}
	}
	return;
}



bool Course::getDone()
{
	return Done;
}

double Course::getPoints()
{
	return Points;
}

string Course::getType() const
{
	return type;
}

//

Course::~Course()
{
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}


string Course::getPreReqAsString() const //it return all prerequisits as string.
{
	string tempString = "";
	if (PreReq.size() == 0)
		return "None";
	else 
	{

		std::list<Course_Code>::const_iterator it;
		for (it = PreReq.begin(); it != PreReq.end(); ++it)
		{
			tempString = tempString + ", ";
			tempString = tempString + (*it);
		}
	}
	tempString = tempString + ".";
	return tempString.substr(1);
	
}

string Course::getCoReqAsString() const//it return all corequisits as string.
{
	string tempString = "";
	if (CoReq.size() == 0)
		return "None";
	else
	{

		std::list<Course_Code>::const_iterator it;
		for (it = CoReq.begin(); it != CoReq.end(); ++it)
		{
			tempString = tempString + ", ";
			tempString = tempString + (*it);
		}
	}
	tempString = tempString + ".";
	return tempString.substr(1);
}

list<Course_Code> Course::getPreReq() const
{
	return PreReq;
}

list<Course_Code> Course::getCoReq() const
{
	return CoReq;
}

void Course::addPreReq(string preReq)
{
	this->PreReq.push_back(preReq);
}


void Course::addCoReq(string CoReq)
{
	this->CoReq.push_back(CoReq);
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

bool Course::operator=(const Course& anotherCourse)
{
	if (this->getCode() == anotherCourse.getCode())
		return true;
	return false;
}
