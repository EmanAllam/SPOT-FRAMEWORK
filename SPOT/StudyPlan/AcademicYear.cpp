#include "AcademicYear.h"
#include "../GUI/GUI.h"

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}

//deletes a course
bool AcademicYear::DeleteCourse(Course* pC, SEMESTER sem, int orderOfCourse)
{
	//TODO:
 //This function still needs many checks to be compelete
	YearCourses[sem].erase(find(YearCourses[sem].begin(), YearCourses[sem].end(), pC));
	TotalCredits -= pC->getCredits();
	delete pC;
	return true;
	//TODO: acording to course type incremenet corrsponding toatl hours for that year
}

int AcademicYear::sizeOfYearCourses()
{
	return YearCourses->size();
}


void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}
void AcademicYear::setYear(int year)
{
	this->year = year;
}

int AcademicYear::getYear() const
{
	return year;
}
list<Course*> AcademicYear::getYearCourses(int sem)const
{
	return YearCourses[sem];
}
