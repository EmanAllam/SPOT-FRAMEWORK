#include "StudyPlan.h"
#include <iostream>
#include <vector>
#include "..\Courses\Course.h"
#include "..\Rules.h"
#include <map>
#include "..\Rules.h"
#include "..\StringUtils.h"
using namespace std;


void StudyPlan::instantiatePlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan->push_back(new AcademicYear);

	// EMAN
	warningMessage = new Warning;
}


StudyPlan::StudyPlan()
{
	instantiatePlan();
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	(*plan)[year - 1]->AddCourse(pC, sem);
	
	return true;
}
bool StudyPlan::DeleteCourse(Course* pC, int year, SEMESTER sem, int orderOfCourse)
{
	(*plan)[year - 1]->DeleteCourse(pC, sem, orderOfCourse);
	return true;
}

void StudyPlan::DeleteAll()
{
	plan->clear();
	instantiatePlan();
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan->size(); i++)
		(*plan)[i]->DrawMe(pGUI);

	// EMAN
	graphicsInfo gInfo{ Year_xStart + YearWidth + Warning_xMargin, Year_yStart };
	warningMessage->setGfxInfo(gInfo);
	warningMessage->DrawMe(pGUI);

}

AcademicYear* StudyPlan::getAcadamicYearAt(int year)
{

	return (*plan)[year - 1];
}



//LastY is expected to be pReg->getGUI()->getWindHeight() - pReg->getGUI()->getStatusBarHeight()
void StudyPlan::calculateGraphicsInfoForEachItem(int lastYe)
{

	int lastY = lastYe;
	int sartingX = WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD;
	int lastTopLeft = lastY;
	int year = 1;
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		(*academicYear)->setYear(year++);
		lastY -= VERTICAL_SPACE_BETWEEN_YEARS;
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			sartingX = WIDTH_YEAR_WORD + WIDTH_SEMESTER_WORD+HORIZENTAL_SPACE_BETWEEN_COURSES_;
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			lastY -= VERTICAL_SPACE_BETWEEN_SEMESTER_;
			
			lastY -= CRS_HEIGHT;
			bool isFound = false;;
			std::list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				//cout << sartingX;
				Course* currentCourse = (*it);
				graphicsInfoComprehensive graphicInfoComp;
				graphicInfoComp.topLeft.x = sartingX;
				graphicInfoComp.topLeft.y = lastY;
				graphicInfoComp.bottomRight.x = sartingX + CRS_WIDTH;
				graphicInfoComp.bottomRight.y = lastY + CRS_HEIGHT;
				currentCourse->setGfxInfoComp(graphicInfoComp);
				sartingX += HORIZENTAL_SPACE_BETWEEN_COURSES_ + CRS_WIDTH;

				isFound = true;
			}
			//if(!isFound)
			//	lastY = lastY+CRS_HEIGHT-VERTICAL_SPACE_BETWEEN_SEMESTER_;
			lastY -= VERTICAL_SPACE_BETWEEN_SEMESTER_;

		}
		graphicsInfoComprehensive graphicInfoComp;
		graphicInfoComp.topLeft.x = 10;
		graphicInfoComp.topLeft.y = lastY ;
		graphicInfoComp.bottomRight.x = 1300 - 30;
		graphicInfoComp.bottomRight.y = lastTopLeft - VERTICAL_SPACE_BETWEEN_YEARS;
		(*academicYear)->setGfxInfoComp(graphicInfoComp);
		lastTopLeft = lastY;
	}
}



Course* StudyPlan::getCourseAtGraphicsInfo(graphicsInfo point)
{
	bool isFound = false;
	//Looping over acadamic years
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//checking first if it's in bounds of acadameic Year
		if (point.x >= (*academicYear)->getGfxInfoComp().topLeft.x && point.x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& point.y >= (*academicYear)->getGfxInfoComp().topLeft.y && point.y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in the boundary of that academic year
			//Looping over semesters.
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				//Checking if it's in that semester, if not it will skip that iteration.
				//1- checking first if the size >0 if not then no courses in in that sem
				if ((currentSemester).size() == 0)
					continue;
				//2- checking second for coordinates, if it reaches that point, then no way to give error for empty currenSemester
				if (!(point.y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y && point.y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y))
					continue;
				for (it = currentSemester.begin(); it != currentSemester.end(); it++)
				{
					Course* currentCourse = (*it);


					if (point.x >= currentCourse->getGfxInfoComp().topLeft.x && point.x < currentCourse->getGfxInfoComp().bottomRight.x
						&& point.y >= currentCourse->getGfxInfoComp().topLeft.y && point.y < currentCourse->getGfxInfoComp().bottomRight.y
						)
					{
						return currentCourse;
					}
				}
			}
		}
	}
	//if it reaches that point that mean he couldn't find that course, meanning that user clicked on somewhere not on course
	//then it will throw an error, meaning it must be handled from the place it will call it.
	throw "Course not found";
}

//over riding the function to use it in deleting courses
Course* StudyPlan::getCourseAtGraphicsInfo(graphicsInfo point, SEMESTER& deletedSemester, int& deletedYear,int& orderOfCourse)
{
	int count=-1;
	bool isFound = false;
	//Looping over acadamic years
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//checking first if it's in bounds of acadameic Year
		if (point.x >= (*academicYear)->getGfxInfoComp().topLeft.x && point.x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& point.y >= (*academicYear)->getGfxInfoComp().topLeft.y && point.y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in the boundary of that academic year
			//Looping over semesters.
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				//Checking if it's in that semester, if not it will skip that iteration.
				//1- checking first if the size >0 if not then no courses in in that sem
				if ((currentSemester).size() == 0)
					continue;
				//2- checking second for coordinates, if it reaches that point, then no way to give error for empty currenSemester
				if (!(point.y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y && point.y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y))
					continue;
				for (it = currentSemester.begin(); it != currentSemester.end(); it++)
				{
					Course* currentCourse = (*it);
					count++;
					if (point.x >= currentCourse->getGfxInfoComp().topLeft.x && point.x < currentCourse->getGfxInfoComp().bottomRight.x
						&& point.y >= currentCourse->getGfxInfoComp().topLeft.y && point.y < currentCourse->getGfxInfoComp().bottomRight.y
						)
					{
						deletedSemester = static_cast<SEMESTER>(sem);
						deletedYear = (*academicYear)->getYear();
						orderOfCourse = count;
						return currentCourse;
					}
				}
				count = -1;
			}
		}
	}
	//if it reaches that point that mean he couldn't find that course, meanning that user clicked on somewhere not on course
	//then it will throw an error, meaning it must be handled from the place it will call it.
	throw "Course not found";
}



void StudyPlan::getSemAndYearForPoint(int x, int y, SEMESTER& semester, int& year)
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//check if it's in this academic year.
		if (x >= (*academicYear)->getGfxInfoComp().topLeft.x && x < (*academicYear)->getGfxInfoComp().bottomRight.x
			&& y >= (*academicYear)->getGfxInfoComp().topLeft.y && y < (*academicYear)->getGfxInfoComp().bottomRight.y
			)
		{
			//it's in this academic year.
			year = (*academicYear)->getYear();
			//Looping over sems
			for (int sem = FALL; sem < SEM_CNT; sem++)
			{
				list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
				std::list<Course*>::iterator it;
				if ((currentSemester).size() == 0)
					continue;
				if ((y > (*currentSemester.begin())->getGfxInfoComp().topLeft.y- VERTICAL_SPACE_BETWEEN_SEMESTER_ && y < (*currentSemester.begin())->getGfxInfoComp().bottomRight.y +VERTICAL_SPACE_BETWEEN_SEMESTER_)
					&& x > WIDTH_SEMESTER_WORD+WIDTH_YEAR_WORD && x < 1300)
				{
					semester = static_cast<SEMESTER>(sem);
					return;
				}
			}


		}
	}
	throw "Not found";
}
map<Course_Code, PROBLEM_VALIDATION_TYPE>* StudyPlan::checkForProgramReq(Rules rules)
{
	map<Course_Code, PROBLEM_VALIDATION_TYPE>* invalidCourseas = new map<Course_Code, PROBLEM_VALIDATION_TYPE>;
	//To check for Compulsary and electives
	vector<Course_Code> UnivCompulsory = rules.UnivCompulsory;	//Univ Compulsory courses
	vector<Course_Code> UnivElective = rules.UnivElective;	//Univ Elective courses
	vector<Course*>UniElectivesTemp;

	vector<Course_Code> TrackCompulsory = rules.TrackCompulsory;//Track Compulsory courses
	vector<Course_Code> TrackElective = rules.TrackElective;	//Track Elective courses (added for future)
	vector<Course*>TrackElectivesTemp;


	vector<Course_Code> MajorCompulsory = rules.MajorCompulsory;//Major Compulsory courses
	vector<Course_Code> MajorElective = rules.MajorElective;	//Major Elective courses
	vector<Course*>MajElectivesTemp;
	cout << "AUniComp " << UnivCompulsory.size()<<endl;
	cout << "ATraComp " << TrackCompulsory.size()<<endl;
	cout << "AUMajComp " << MajorCompulsory.size()<<endl;
	cout << "track cours0e" << *(TrackCompulsory.begin()) << endl;
	cout << "track cours1e" << *(TrackCompulsory.begin() + 1) << endl;
	cout << "major cours0e" << *(MajorCompulsory.begin() ) << endl;
	cout << "major cours1e" << *(MajorCompulsory.begin() + 1) << endl;

	//Looping Over all courses, and classify them.
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			for (auto it = currentSemester.begin(); it != currentSemester.end(); ++it)
			{
				if (!isCourseInAnyCompulsory((*it), UnivCompulsory, TrackCompulsory, MajorCompulsory))
				{

					//If it's not compulsary, then it must be elective
					if (!isCourseInAnyElective((*it), UnivElective, UniElectivesTemp, TrackElective, TrackElectivesTemp, MajorElective, MajElectivesTemp))
					{
						cout <<"notfoundcode"<< (*it)->getCode()<<endl;
						invalidCourseas->insert({ (*it)->getCode(),COURSE_NOT_IN_ANY_CATEGORY });
					}
				}
			}
			
		}
	}
	if (UnivCompulsory.size() != 0)
	{
		for (int i = 0; i < UnivCompulsory.size(); i++)
		{
			invalidCourseas->insert({ UnivCompulsory.at(i),UNI_COMP_NOT_FOUND_ISSUE });
		}
	}
	
	if (TrackCompulsory.size() != 0)
	{
		for (int i = 0; i < TrackCompulsory.size(); i++)
		{
			invalidCourseas->insert({ TrackCompulsory.at(i),TRACK_COMP_NOT_FOUND_ISSUE });
		}
	}
	if (MajorCompulsory.size() != 0)
	{
		for (int i = 0; i < MajorCompulsory.size(); i++)
		{
			invalidCourseas->insert({ MajorCompulsory.at(i),MAJOR_COMP_NOT_FOUND_ISSUE });
		}
	}
	//TODO tomorrow, add all credits.to check for not size.
	if (getCreditsCountInVector(UniElectivesTemp) < rules.ReqUnivCreditsElective)
	{
		invalidCourseas->insert({ UNI_MIN_NOT_FOUND_COURSE_CODE,UNI_COMP_NOT_FOUND_ISSUE });
	}
	if (getCreditsCountInVector(TrackElectivesTemp) < rules.ReqTrackCreditsElective)
	{
		invalidCourseas->insert({ TRACK_MIN_NOT_FOUND_COURSE_CODE,TRACK_COMP_NOT_FOUND_ISSUE });
	}
	if (getCreditsCountInVector(MajElectivesTemp) < rules.ReqMajorCreditsElective)
	{
		invalidCourseas->insert({ MAJOR_MIN_NOT_FOUND_COURSE_CODE,MAJOR_COMP_NOT_FOUND_ISSUE });
	}
	
	return invalidCourseas;
}

bool StudyPlan::isCourseInAnyCompulsory(Course* crs, vector<Course_Code>& uni, vector<Course_Code>& track, vector<Course_Code>& maj)
{
	if (isCourseInVectorAndRemove(crs, uni) || isCourseInVectorAndRemove(crs, track) || isCourseInVectorAndRemove(crs, maj))
	{
		return true;
	}
	return false;
}
bool StudyPlan::isCourseInAnyElective(Course* crs, vector<Course_Code> uni, vector<Course*>& uniTemp,
	vector<Course_Code> track, vector<Course*>& trackTemp,
	vector<Course_Code> maj, vector<Course*>& majTemp)
{
	return (isCourseInVectorAndAddTo(crs, uni, uniTemp) || isCourseInVectorAndAddTo(crs, track, trackTemp) || isCourseInVectorAndAddTo(crs, maj, majTemp));
}



bool StudyPlan::isCourseInVectorAndRemove(Course* crs, vector<Course_Code>& vktr)
{
	for (int i = 0; i < vktr.size(); i++)
	{

		//cout << vktr.at(i);
		//cout << StringUtils::trimCourseCode(string(vktr.at(i)));
		if (crs->getCode() == StringUtils::trimCourseCode(string(vktr.at(i))))
		{
			vktr.erase(vktr.begin() + i);
			return true;
		}
	}
	return false;
}

bool StudyPlan::isCourseInVectorAndAddTo(Course* crs, vector<Course_Code> vktr, vector<Course*>& toBeAddedTo)
{
	
	for (int i = 0; i < vktr.size(); i++)
	{
		if (crs->getCode() == vktr.at(i))
		{
			toBeAddedTo.push_back(crs);
			return true;
		}
	}
	return false;
}

Course* StudyPlan::getCourseForCourseCode(Course_Code cc)
{
	Course* crs =nullptr;
	for (vector<AcademicYear*>::reverse_iterator academicYear = plan->rbegin(); academicYear != plan->rend(); ++academicYear)//Using rebegin and rend will reverser the iteration.
	{
		for (int sem = SUMMER; sem >= FALL; sem--)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem); //all courser in that semester.
			list<Course*>::iterator it;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				Course* currentCourse = (*it); //Course in that semester
				if (cc == currentCourse->getCode())
					return crs;
			}
		}
	}

	throw "Course not found";
}

int StudyPlan::getCreditsCountInVector(vector<Course*> crss)
{
	int totalCredits = 0;
	for (int i = 0; i < crss.size(); i++)
	{
		totalCredits = totalCredits + crss.at(i)->getCredits();
	}
	return totalCredits;
}


map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>*  StudyPlan::checkCoPreReqValidation()
{
	map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>* invalidCourses = new map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>; //This is what is going to be returned
	map<Course*, vector<Course_Code>*>* allPreReqForAllYears = new map<Course*, vector<Course_Code>*>;
	map<Course*, vector<Course_Code>*>* allCoReqForAllYears = new map<Course*, vector<Course_Code>*>;

	 //Looping over all academic years.
	for (vector<AcademicYear*>::reverse_iterator academicYear = plan->rbegin(); academicYear != plan->rend(); ++academicYear)//Using rebegin and rend will reverser the iteration.
	{
		for (int sem = SUMMER; sem >= FALL; sem--)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem); //all courser in that semester.

			//Checking	CoRequisits
			map<Course*, vector<Course_Code>*>* allCoReq = getAllCoReqCourseCodesFromOneSem(currentSemester);
			CheckCoReqInSemesterAndAddToMap(allCoReq, currentSemester, allCoReqForAllYears);


			//Checking Prerequsits
			CheckPreReqInSemesterAndRemoveFroMap(allPreReqForAllYears, currentSemester);

			map<Course*, vector<Course_Code>*>* allPreReq = getAllPreReqCourseCodesFromOneSem(currentSemester);
			insertMapIntoMap(allPreReq, allPreReqForAllYears);

		}
	}
	//Adding courses that have problem to invalidCourses map.
	for (map<Course*, vector<Course_Code>*>::iterator itPre = allPreReqForAllYears->begin(); itPre != allPreReqForAllYears->end(); ++itPre)
	{
		map <PROBLEM_VALIDATION_TYPE, vector<Course_Code>>* tmpMap=new map <PROBLEM_VALIDATION_TYPE, vector<Course_Code>>;
		tmpMap->insert({ PREREQ_ISSUE, *(*itPre).second });
		invalidCourses->insert({(*itPre).first,*tmpMap });
	}
	
	for (map<Course*, vector<Course_Code>*>::iterator itCo = allCoReqForAllYears->begin(); itCo != allCoReqForAllYears->end(); ++itCo)
	{
		//TODO:: understant why end?
		if (invalidCourses->find((*itCo).first) == invalidCourses->end())
		{
			//It's found -->has been added by prerequisits.
			invalidCourses->find((*itCo).first)->second.insert({ COREQ_ISSUE, *(*itCo).second });
		}
		else 
		{
			//not found
			map <PROBLEM_VALIDATION_TYPE, vector<Course_Code>>* tmpMap = new map <PROBLEM_VALIDATION_TYPE, vector<Course_Code>>;
			tmpMap->insert({ COREQ_ISSUE, *(*itCo).second });
			invalidCourses->insert({ (*itCo).first,*tmpMap });
		}
		
	}

	//cout << "Final version size" << invalidCourses->size() << endl;

	return invalidCourses;
}



map<Course*, vector<Course_Code>*>* StudyPlan::getAllPreReqCourseCodesFromOneSem(list<Course*> currentSemester)
{
	map<Course*, vector<Course_Code>*>* preReqWithCourse = new map<Course*, vector<Course_Code>*>; //this is every course that has a prerequisit courses.
	std::list<Course*>::iterator it;
	for (auto it = currentSemester.begin(); it != currentSemester.end(); ++it)
	{
		if ((*it)->getPreReq().size() != 0)
		{
			preReqWithCourse->insert({ (*it), getVectorFromList((*it)->getPreReq()) });
		}
	}
	return preReqWithCourse;
}

map<Course*, vector<Course_Code>*>* StudyPlan::getAllCoReqCourseCodesFromOneSem(list<Course*> currentSemester)
{

	map<Course*, vector<Course_Code>*>* coReqWithCourse = new map<Course*, vector<Course_Code>*>; //this is every course that has a prerequisit courses.
	std::list<Course*>::iterator it;
	for (auto it = currentSemester.begin(); it != currentSemester.end(); ++it)
	{
		if ((*it)->getCoReq().size() != 0)
		{
			coReqWithCourse->insert({ (*it), getVectorFromList((*it)->getCoReq()) });
		}
	}
	return coReqWithCourse;

}

vector<Course_Code>* StudyPlan::getVectorFromList(list<Course_Code>& lst)
{
	vector<Course_Code>* courseCodes = new vector< Course_Code>;
	std::list<Course_Code>::iterator it;
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		courseCodes->push_back((*it));
	}
	return courseCodes;
}



void StudyPlan::insertMapIntoMap(map<Course*, vector<Course_Code>*>* from, map<Course*, vector<Course_Code>*>* into)
{

	for (std::map< Course*, vector<Course_Code>*>::iterator it = from->begin(); it != from->end(); ++it)
	{
		into->insert({ (*it).first, (*it).second });
	}
}
void StudyPlan::CheckPreReqInSemesterAndRemoveFroMap(map<Course*, vector<Course_Code>*>* allPreReq, list<Course*> currentSemester)
{
	if (allPreReq->size() == 0 || currentSemester.size() == 0)
		return;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		Course* currentCourse = (*it); //Course in that semester
		for (std::map< Course*, vector<Course_Code>*>::iterator itM = allPreReq->begin(); itM != allPreReq->end();)
		{
			vector<Course_Code>* crsCodesForPre = (*itM).second;
			for (int i =0; i< crsCodesForPre->size();)
			{
				if (crsCodesForPre->at(i) == currentCourse->getCode())
				{
					crsCodesForPre->erase(crsCodesForPre->begin() + i);
				}
				else
					++i;

			}
			if (crsCodesForPre->size() == 0)//removing course if all its prerRequisits are found.
				allPreReq->erase(itM++);

			else
				++itM;
		}
	
	}

}

void StudyPlan::CheckCoReqInSemesterAndAddToMap(map<Course*, vector<Course_Code>*>* allCoReq, list<Course*> currentSemester, map<Course*, vector<Course_Code>*>* allCoReqForAllYears)
{
	std::list<Course*>::iterator itSem;
	for (auto itSem = currentSemester.begin(); itSem != currentSemester.end(); ++itSem)
	{
		Course* currentCourse = (*itSem);

		for (map<Course*, vector<Course_Code>*>::iterator itM = allCoReq->begin(); itM != allCoReq->end(); )
		{
			vector<Course_Code>* crsCodesForCo = (*itM).second;
			for (int i = 0; i < crsCodesForCo->size(); )
			{
				if (crsCodesForCo->at(i) == currentCourse->getCode())
				{
					crsCodesForCo->erase(crsCodesForCo->begin() + i);
				}
				else
					++i;
			}
			if (crsCodesForCo->size() == 0)//removing course if all its prerRequisits are found.
				allCoReq->erase(itM++);

			else
				++itM;
		}
	}

	insertMapIntoMap(allCoReq, allCoReqForAllYears);
}







void StudyPlan::CheckPreReqInSemesterAndRemove(list<Course_Code>& allPreReq, list<Course*> currentSemester)
{
	if (allPreReq.size() == 0 || currentSemester.size() == 0)
		return;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		Course* currentCourse = (*it); //Course in that semester
		std::list<Course_Code>::iterator prereqiterator = allPreReq.begin();

		while (prereqiterator != allPreReq.end())
		{
			if ((*prereqiterator) == currentCourse->getCode())
			{
				allPreReq.erase(prereqiterator++);
			}
			else
			{
				++prereqiterator;
			}


		}
		if (allPreReq.size() == 0)
			return;
	}
}
list<Course_Code>* StudyPlan::getAllPreReqFromOneSemester(list<Course*> currentSemester)
{
	list<Course_Code>* allPreReq = new list<Course_Code>;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		insertListIntoList((*it)->getPreReq(), *allPreReq);
	}
	std::list<Course_Code>::iterator iit;
	return allPreReq;
}

//

string StudyPlan::getStudentLevel()
{
	if (doneCredits <= 32)
		return "Student Level: Freshman";
	else if (doneCredits <= 64)
		return "Student Level: Sophomore";
	else if (doneCredits <= 96)
		return "Student Level: Junior";
	else if (doneCredits <= 128)
		return "Student Level: Senior I";
	else
		return "Student Level: Senior II";
}

//the function returns 2 if overload, 1 if underload, 0 if no violation
int StudyPlan::isPetitionNeeded()
{

	int semCredits=0; // remove it and use getCredits() from shady.
	for (int i = 0; i < 5; i++) //5 years
	{
		for (int j = 0; j < 3; j++) //3 sem
		{
			//put here  semCredits=getCredits();
			if ((*plan)[i]->getYearCourses(j).empty()) //if sem is empty then, do not check this sem
			{
				continue;
			}
			if (j < 2) //fall or spring
			{
				if (semCredits < 12)
					return 1;
				if (semCredits>18)
					return 2;
			}
			else if (j == 2)  //summer 
			{
				if (semCredits > 7)
					return 2;
			}
		}
	}
	return false; //if it reached this line then no violation happened.
}

double StudyPlan::getGpa()
{
	return gpa;
}
int StudyPlan::getDoneCredits()
{
	return doneCredits;
}

void StudyPlan::setGpa(double gpa)
{
	this->gpa = gpa;
}
void StudyPlan::setDoneCredits(int credits)
{
	doneCredits = credits;
}



bool StudyPlan::isDependenciesCorrect()
{
	//checking the two main fucntions.
	bool H = isCoReqDependenciesCorrect();
	bool HH = isPreReqDependenciesCorrect();
	cout << "Co: " << H << endl << "Pre: " << HH<<endl;
	return isCoReqDependenciesCorrect() && isPreReqDependenciesCorrect();
}

/*
* Algorithm used
* I simply collect all coreqs from one semester in one loop
* and check that all these coreq couse code are preset in the same semester
*/
bool StudyPlan::isCoReqDependenciesCorrect()
{
	
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		//Looping overSemesters
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			list<Course_Code>* allCoReq = getAllCoReqFromOneSemester(currentSemester);
			if (!isCoReqInSemester(*allCoReq, currentSemester))
			{
				return false;
			}

		}
	}
	return true;
}



bool StudyPlan::isPreReqDependenciesCorrect()
{
	//TODO understand that in Course data structure and algorithms
	list<Course_Code>* allPreReqForAllYears = new list<Course_Code>;
	for (vector<AcademicYear*>::reverse_iterator academicYear = plan->rbegin(); academicYear != plan->rend(); ++academicYear)
	{
		for (int sem = SUMMER; sem >= FALL; sem--)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			CheckPreReqInSemesterAndRemove(*allPreReqForAllYears, currentSemester);

			list<Course_Code>* allPreReq = getAllPreReqFromOneSemester(currentSemester);
			insertListIntoList(*allPreReq, *allPreReqForAllYears);

		}
	}

	if (allPreReqForAllYears->size() == 0)
		return true;
	else
		return false;
}
//It loops over courses of one semester to get all Coreqs
list<Course_Code>* StudyPlan::getAllCoReqFromOneSemester(list<Course*> currentSemester)
{
	list<Course_Code>* allCoReq = new list<Course_Code>;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		insertListIntoList((*it)->getCoReq(), *allCoReq);
	}
	return allCoReq;
}



//direct the argument to the proper function
bool StudyPlan::isCoReqInSemester(list<Course_Code>& CoReq, list<Course*> currentSemester)
{
	if (CoReq.size() == 0)
		return true;
	if (CoReq.size() == 1)
		return isCoReqInSemesterForCoreq1(CoReq, currentSemester);
	return isCoReqInSemesterForCoreqMany(CoReq, currentSemester);

}




bool StudyPlan::isCoReqInSemesterForCoreq1(list<Course_Code>& CoReq, list<Course*> currentSemester)
{
	int numDesired = 1;
	int numFound = 0;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		Course* currentCourse = (*it); //Course in that semester
		if ((*CoReq.begin() == currentCourse->getCode()))
			return true;

	}
	return false;
}

bool StudyPlan::isCoReqInSemesterForCoreqMany(list<Course_Code>& CoReq, list<Course*> currentSemester)
{
	int numDesired = CoReq.size();
	int numFound = 0;
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		Course* currentCourse = (*it); //Course in that semester
		std::list<Course_Code>::iterator coreqiterator;
		for (coreqiterator = CoReq.begin(); coreqiterator != CoReq.end(); coreqiterator++)
		{
			if ((*coreqiterator) == currentCourse->getCode())
			{
				//remove what was found already
				CoReq.remove(*coreqiterator);
				numFound++;
				break;

			}
		}
		//Meaning all CoReqs have been found.
		if (numFound == numDesired)
			return true;

	}
	return false;
}







void StudyPlan::insertListIntoList(list<Course_Code>& from, list<Course_Code>& into)
{
	if (from.size() == 1)
		into.push_back((*from.begin()));
	else
	{
		std::list<Course_Code>::iterator it;
		for (it = from.begin(); it != from.end(); it++)
		{
			into.push_back((*it));
		}
	}
}
bool StudyPlan::checkForProgrammeRequirements(Rules& rules)
{
	this->RegRules = rules;
	instantiateTempVector();
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		divideAcademicYearIntoSemstersForTempVectors((*academicYear));
	}

	return true;
}

void StudyPlan::instantiateTempVector()
{

	UniTempComp = new vector<Course*>;
	UniTempElec = new vector<Course*>;

	TrackTempComp = new vector<Course*>;
	TrackTempElec = new vector<Course*>;

	MajorTempComp = new vector<Course*>;
	MajorTempElec = new vector<Course*>;
	numUniCompCredit = 0;
}

void StudyPlan::divideAcademicYearIntoSemstersForTempVectors(AcademicYear* academicYear)
{
	std::list<Course*>::iterator it;
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		divideSemseterIntoCoursesForTempVectors(academicYear->getYearCourses(sem));
	}

}

void StudyPlan::divideSemseterIntoCoursesForTempVectors(list<Course*> currentSemester)
{
	std::list<Course*>::iterator it;
	for (it = currentSemester.begin(); it != currentSemester.end(); it++)
	{
		Course* currentCourse = (*it);
		clasifyCourseForTempVectores(currentCourse);

	}
}

void StudyPlan::clasifyCourseForTempVectores(Course* crs)
{
	if (isCourseInVector(crs, RegRules.UnivCompulsory))
	{
		this->UniTempComp->push_back(crs);
	}
	else if (isCourseInVector(crs, RegRules.UnivElective))
	{
		this->UniTempElec->push_back(crs);
	}
	else if (isCourseInVector(crs, RegRules.TrackCompulsory))
	{
		this->TrackTempComp->push_back(crs);
	}
	else if (isCourseInVector(crs, RegRules.TrackElective))
	{
		this->TrackTempElec->push_back(crs);
	}
	else if (isCourseInVector(crs, RegRules.MajorCompulsory))
	{
		this->MajorTempComp->push_back(crs);
	}
	else if (isCourseInVector(crs, RegRules.MajorElective))
	{
		this->MajorTempElec->push_back(crs);
	}
}
bool StudyPlan::isCourseInVector(Course* crs, vector<Course_Code> vktr)
{
	for (int i = 0; i < vktr.size(); i++)
	{
		if (crs->getCode() == vktr.at(i))
		{
			return true;
		}
	}
	return false;
}

bool StudyPlan::checkUniComp()
{
	bool isCompRight;
	numUniCompCredit = checkCompulsary(*UniTempComp, RegRules.UnivCompulsory, isCompRight);
	return  isCompRight;
}

int StudyPlan::checkCompulsary(vector<Course*> checkable, vector<Course_Code> from, bool& RIGHT)
{
	vector<Course*> _checkable = checkable;
	std::vector<Course*>::iterator itC;
	std::vector<Course_Code>::iterator it;
	int numCredits = 0;
	for (it = from.begin(); it != from.end(); ++it)
	{
		for (itC = _checkable.begin(); itC != _checkable.end(); ++itC)
		{
			if ((*itC)->getCode() == (*it))
			{
				numCredits += (*itC)->getCredits();
				from.erase(it++);
				_checkable.erase(itC++);
			}
		}
	}
	return numCredits;

}



bool StudyPlan::checkUniElec()
{
	return false;
}


StudyPlan::~StudyPlan()
{
}

//EMAN STUFF

bool StudyPlan::AddWarning(string content)
{
	warningMessage->AddContent(content);

	return true;

}

void StudyPlan::ClearWarnings() {
	warningMessage->ClearWarnings();
	resetColors();
}


void StudyPlan::resetColors()
{
	for (auto academicYear = plan->begin(); academicYear != plan->end(); ++academicYear)
	{
		for (int sem = FALL; sem < SEM_CNT; sem++)
		{
			list<Course*> currentSemester = (*academicYear)->getYearCourses(sem);
			std::list<Course*>::iterator it;
			if ((currentSemester).size() == 0)
				continue;
			for (it = currentSemester.begin(); it != currentSemester.end(); it++)
			{
				Course* currentCourse = (*it);
				currentCourse->setColor(0);
			}
		}
	}
}

void StudyPlan::saveTxtFile()
{
	warningMessage->saveTxtFile();
}

ErrorList* StudyPlan::getErrors()
{
	int cnt = 0;

	ErrorList* errorList = new ErrorList();

	// THIS SHOULD BE REPLACED WITH ACTUAL ERROR CHECKS
	
	map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>* invalidCourse = checkCoPreReqValidation();

	//for (map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>::iterator itCourse = invalidCourse->begin(); itCourse != invalidCourse->end(); ++itCourse)
	//for (auto const &itCourse : invalidCourse)
	for (auto itCourse = invalidCourse->begin(); itCourse != invalidCourse->end(); ++itCourse)
	{
		//cout << itCourse->first->getCode() << endl;
		errorList->addError(BasicError(1, itCourse->first));
	}
	
	
	Rules rules = this->RegRules;
	map<Course_Code, PROBLEM_VALIDATION_TYPE>* invalidProg = checkForProgramReq(rules);
	//for (map<Course_Code, PROBLEM_VALIDATION_TYPE>::iterator it = invalidProg->begin(); it != invalidProg->end(); it++)
	cout << "BEFORE LOOP" << endl;
	for (auto it = invalidProg->begin(); it != invalidProg->end(); ++it) {
		errorList->addError(BasicError(3));
		break;
	}
	




	//Just for testing purposes
	/*
	Course* x = new Course("CIE 321", "qdwefrgtrhyt", 3);
	BasicError error_1 = BasicError(1, x);

	SEMESTER sem = SUMMER;
	BasicError error_2 = BasicError(2, sem, 3);

	BasicError error_3 = BasicError(3);

	BasicError error_4 = BasicError(4);

	Course* x2 = new Course("CIE 101", "pew", 5);
	BasicError error_5 = BasicError(5, x2);

	errorList->addError(error_1);
	errorList->addError(error_2);
	errorList->addError(error_3);
	errorList->addError(error_4);
	errorList->addError(error_5);
	*/

	/*
	for (int i = 0; i < 5; i++)
	{
		BasicError new_error = BasicError(1, x);
		errorList->addError(new_error);
	}
	*/

	//int arr1[5] = { 1,2,3,4,5 };
	//string arr2[5] = { "CIE 202", "Summer Year1","", "", "ENGR 210" };
	return errorList;
}

void StudyPlan::displayWarning(ErrorList* errorList)
{
	ClearWarnings();
	int cnt = errorList->getCount();
	BasicError* errorArray = errorList->getErrorArray();
	for (int i = 0; i < cnt; i++)
	{
		AddWarning(errorArray[i].get_error_msg());
		cout << errorArray[i].get_error_msg() << endl;

		if (errorArray[i].getType() == 1)
		{
			errorArray[i].getCourse()->setColor(2);

		}

	}
}



