#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "ActionImportCourseCatalog.h"
#include "ActionImportRules.h"
#include "EmptyAction.h"
#include <iostream>
#include "EmptyAction.h"
#include "ActionImportDefaulPlan.h"
#include "ActionImpOffering.h"
#include "ActionImpReq.h"
#include "ActionDeleteCourse.h"
#include "ActionShowCourseInfo.h"
#include  "Student.h"
#include"ActionAddNotes.h"
#include"ActionShowNotes.h"
#include "ActionChangeByCode.h"
#include "ActionDragAndDropCrs.h"
#include "ActionSignUserUp.h"
#include "ActionMarkAsDone.h"
#include "ActionAddGrade.h"
#include "ActionDisplayStudentLevel.h"
#include "ActionSupportMinor.h"
#include "ActionShowGpa.h"

//EMAN
#include "ActionValidityReport.h"


#include <map>
using namespace std;
Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	pSignedStudent = new Student();

}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}



//checks if a course is in some vector or not
bool Registrar::findCourseCodeInVector(vector<Course_Code> vector, Course_Code code)
{
	for (auto it = vector.begin(); it != vector.end(); it++)
	{
		if (code == *it)
			return true;
	}
	return false;
}
//searches for type of courses in different vectors
string Registrar::findTypeOfCourse(Course_Code code)
{
	string type;
	if (this->findCourseCodeInVector(this->getRules().MajorCompulsory, code))
		type = "MajorCompulsory";
	else if (this->findCourseCodeInVector(this->getRules().MajorElective, code))
		type = "MajorElective";
	else if (this->findCourseCodeInVector(this->getRules().TrackCompulsory, code))
		type = "TrackCompulsory";
	else if (this->findCourseCodeInVector(this->getRules().UnivCompulsory, code))
		type = "UnivCompulsory";
	else if (this->findCourseCodeInVector(this->getRules().UnivElective, code))
		type = "UnivElective";
	else if (this->findCourseCodeInVector(this->getRules().MinorCourses, code))
		type = "Minor";
	else type = "Extra";

	return type;
}

//Sets the courses offering data
void Registrar::setOfferingRules(Rules newRules)
{
	for (int i = 0; i < 5; i++)
	{
		RegRules.OffringsList[i] = newRules.OffringsList[i];
	}

}

//sets the Rules 
void Registrar::setRules(Rules newRules)
{
	RegRules.TotalCredits = newRules.TotalCredits;
	RegRules.SemMinCredit = 12;
	RegRules.SemMaxCredit = 18;
	RegRules.ReqUnivCreditsCompulsory = newRules.ReqUnivCreditsCompulsory;
	RegRules.ReqUnivCreditsElective = newRules.ReqUnivCreditsElective;
	RegRules.ReqTrackCredits = newRules.ReqTrackCredits;
	RegRules.ReqTrackCreditsElective = 0;
	RegRules.ReqMajorCreditsCompulsory = newRules.ReqMajorCreditsCompulsory;
	RegRules.ReqMajorCreditsElective = newRules.ReqMajorCreditsElective;
	RegRules.ConcentrationsNumber = newRules.ConcentrationsNumber;
	RegRules.ReqConcentrationCredits = newRules.ReqConcentrationCredits;
	RegRules.UnivCompulsory = newRules.UnivCompulsory;
	RegRules.UnivElective = newRules.UnivElective;
	RegRules.TrackCompulsory = newRules.TrackCompulsory;
	RegRules.MajorCompulsory = newRules.MajorCompulsory;
	RegRules.MajorElective = newRules.MajorElective;
	RegRules.ConcentrationsCompulsory = newRules.ConcentrationsCompulsory;
	RegRules.ConcentrationsElective = newRules.ConcentrationsElective;


}

//sets the minor courses one by one
void Registrar::setMinorCourse(Course_Code code)
{
		RegRules.MinorCourses.push_back( code );
}
void Registrar::addMinorCredits(int credits)
{
	RegRules.TotalCredits += credits;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}

Rules Registrar::getRules() const
{
	return this->RegRules;
}

Student* Registrar::getSignedStudest()
{
	return pSignedStudent;
}

void Registrar::loadNewDefaultPlan()
{
	pSPlan->DeleteAll();
	Action* acc = new  ActionImportDefaulPlan(this);
	acc->Execute();
}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;

	
	case CHANGE_BY_CODE:	//add_course action
		RequiredAction = new ActionChangeByCode(this);
		break;
	
	case DEL_CRS:
		RequiredAction = new ActionDeleteCourse(this);
		break;

	case REORDER:	//add_course action
		RequiredAction = new ActionDragAndDropCrs(this);
		break;

	
	case ADD_NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case SHOW_NOTES:
		RequiredAction = new ActionShowNotes(this);
		break;
	
	case SETTINGS:
		RequiredAction = new ActionSignUserUp(this);
		break;

	case COURSE_STATUS:
		RequiredAction = new ActionMarkAsDone(this);
		break;

	case ADD_GRADE:
		RequiredAction = new ActionAddGrade(this);
		break;

	case SHOW_GRADE:
		RequiredAction = new ActionShowGpa(this);
		break;
	case SUPPORT_MINOR:
		RequiredAction = new ActionSupportMinor(this);
		break;

	//EMAN
	case VALIDITY_REPORT:
		RequiredAction = new ActionValidityReport(this);
		break;



	case DRAW_AREA:	
		RequiredAction = getActionsForClickingOnDrawArea(RequiredAction, actData);
		cout << (RequiredAction == nullptr);
		break;
	

	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{

	if (!pSignedStudent->isUserSigned())
	{
		Action* sign = new ActionSignUserUp(this);
		sign->Execute();

	}
	//cout << "Reg" << pSignedStudent->getMajor() << endl;
	loadRules();

	//cout <<"Size: "<<RegRules.CourseCatalog->size();

	Action* acc =new  ActionImportDefaulPlan(this);
	acc->Execute();
	//cout <<"Psplan: "<<pSPlan->getAcadamicYearAt(1)[FALL].sizeOfYearCourses();
	
	cout <<"univcompu: " <<(RegRules.ConcentrationsNumber)<<endl;

	//this is made essentialy to stop bliking while it's not needed, if the action can handle the drawing; then no need to draw all courses from scratch./
	bool isUpdateInterface = true;
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		if(isUpdateInterface)
			UpdateInterface();
		isUpdateInterface = false;
		cout << "Dependencies: " << getStudyPlay()->isDependenciesCorrect()<<endl;
		cout << "ProgrammeReq: " << getStudyPlay()->checkForProgrammeRequirements(RegRules)<<endl;

		map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>* MAP = getStudyPlay()->checkCoPreReqValidation();
		getStudyPlay()->checkForProgramReq(RegRules);


		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			isUpdateInterface = ExecuteAction(pAct);
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

void Registrar::loadRules()
{

	Action* acc = new ActionImportRules(this);
	acc->Execute();
	Action* pOffering = new ActionImpOffering(this);
	Action* pReq = new ActionImpReq(this);
	pOffering->Execute();
	pReq->Execute();
	//delete acc, pOffering, pReq;
}

Action* Registrar::getActionsForClickingOnDrawArea(Action* RequiredAction, ActionData actData)
{
	graphicsInfo tempGI;
	tempGI.x = actData.x;
	tempGI.y = actData.y;
	try
	{
		cout << "drawArea" << endl;
		Course* crsClicked = pSPlan->getCourseAtGraphicsInfo(tempGI);
		cout << "drawArea" << endl;

		//then course found if it doesn't throw an exception
		return new ActionShowCourseInfo(this, crsClicked);

		cout << "drawArea"<<endl;

	}
	catch (const char* msg)
	{
		return new EmptyAction(this);
	}
}

Registrar::~Registrar()
{
	delete pGUI;
}
