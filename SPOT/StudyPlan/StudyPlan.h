#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
#include <vector>
#include "..\Rules.h"
#include <map>
#include "..\Rules.h"
//A full study plan for as student
const string UNI_MIN_NOT_FOUND_COURSE_CODE = "1";
const string TRACK_MIN_NOT_FOUND_COURSE_CODE = "2";
const string MAJOR_MIN_NOT_FOUND_COURSE_CODE = "3";
enum PROBLEM_VALIDATION_TYPE 
{
	COREQ_ISSUE,
	PREREQ_ISSUE,
	UNI_COMP_NOT_FOUND_ISSUE,
	TRACK_COMP_NOT_FOUND_ISSUE,
	MAJOR_COMP_NOT_FOUND_ISSUE,
	UNI_MIN_NOT_FOUND,
	TRACK_MIN_NOT_FOUND,
	MAJOR_MIN_NOT_FOUND,
	COURSE_NOT_IN_ANY_CATEGORY

};
class StudyPlan:public Drawable
{
	double gpa=0;
	int doneCredits=0;

	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	vector<AcademicYear*>* plan= new vector<AcademicYear*>;	//plan is a list of academic years


	//for temporary useage
	vector<Course*>* UniTempComp;
	vector<Course*>* UniTempElec;

	vector<Course*>* TrackTempComp;
	vector<Course*>* TrackTempElec;

	vector<Course*>* MajorTempComp;
	vector<Course*>* MajorTempElec;
	Rules RegRules;	//Registration rules
	int numUniCompCredit;

	string PlanNotes;
	void instantiatePlan();
	//this fucntion expects the CoReq.size ==1 to check for it.
	bool isCoReqInSemesterForCoreq1(list<Course_Code>& CoReq, list<Course*> currentSemester);
	//this fucntion expects the CoReq.size >1 to check for it.
	bool isCoReqInSemesterForCoreqMany(list<Course_Code>& CoReq, list<Course*> currentSemester);
	// Simply it loops over all courses of one sem to get all CoReq; to loop over it again for simple finding if all coreqs are in the same semester
	list<Course_Code>* getAllCoReqFromOneSemester(list<Course*> currentSemester);
	//Simpley it loops over all Course in one semester to get all PreReqs, as to check if these are found in the next down semester or later.
	
	list<Course_Code>* getAllPreReqFromOneSemester(list<Course*> currentSemester);
	/*it inserts all elements from from to into
	* I Could made by template, and I found that I will enly need that kind 
	*/
	void insertListIntoList(list<Course_Code>& from, list<Course_Code>& into);
	// used to check CoReq dependecies

	bool isCoReqDependenciesCorrect();
	// used to check PreReq dependecies
	/*
		The Algorithm used:
		it goes to the last semester and collects all PreReq and try to find them in the next semester
		if some are nout found, the prereq of that semster are added to the prereq of the current semester
		and I try to find them the next semester.....
	*/
	bool isPreReqDependenciesCorrect();
	//this function is to find if any of the given Prereq in that semeseter, and if found it removes it from list<Course_code>PreReq 
	void CheckPreReqInSemesterAndRemove(list<Course_Code>& allPreReq, list<Course*> currentSemester) ;
	void CheckPreReqInSemesterAndRemove(vector<Course_Code>& allPreReq, list<Course*> currentSemester) ;
	void instantiateTempVector();
	void divideAcademicYearIntoSemstersForTempVectors(AcademicYear* academicYear);
	void divideSemseterIntoCoursesForTempVectors(list<Course*> currentSemester);
	void clasifyCourseForTempVectores(Course* crs);
	bool isCourseInVector(Course* crs, vector<Course_Code> vktr);
	bool checkUniComp();
	bool checkUniElec();
	int checkCompulsary(vector<Course*> checkable, vector<Course_Code> from, bool& RIGHT);
	//if the size of this map is equal to zero then no problem with corequisits or prerequisits.
	map<Course*, vector<Course_Code>*>* getAllPreReqCourseCodesFromOneSem(list<Course*> currentSemester);
	//it loops over all courses in semester, and collects all corequisits, and return them as map.
	map<Course*, vector<Course_Code>*>* getAllCoReqCourseCodesFromOneSem(list<Course*> currentSemester);
	//it inserts elements of lst to vktr.
	void insertListToVector(list<Course_Code>& lst, vector< Course_Code>* vktr);
	//it insert element of first map to second map.
	void insertMapIntoMap(map<Course*, vector<Course_Code>*>* from, map<Course*, vector<Course_Code>*>* into);
	//convert list to vector.
	vector<Course_Code>* getVectorFromList(list<Course_Code>& lst);
	//it checks that all prereq of all courses in map, are found in curresntSemester, if found, it removes it from map.
	void CheckPreReqInSemesterAndRemoveFroMap(map<Course*, vector<Course_Code>*>*, list<Course*> currentSemester);
	//it verfiies that all courses given in map allCoReq, are in list of courses* (currentSemester), if not found, then it adds to allCoReqForAllYears, as to be shown to user, that this course its coreqisits are not found.
	void CheckCoReqInSemesterAndAddToMap(map<Course*, vector<Course_Code>*>*, list<Course*> currentSemester, map<Course*, vector<Course_Code>*>* allCoReqForAllYears);
	//it checks if crs is in any compulsory vectors like uni, track, maj, if true, it removes crs from it.
	bool isCourseInAnyCompulsory(Course* crs, vector<Course_Code>& uni, vector<Course_Code>& track, vector<Course_Code>& maj);
	//it checks if crs given is in in elective vectore{uni, track, majoor} if true it adds it to {uniTemp, TrackTemp, MajorTemp}
	bool isCourseInAnyElective(Course* crs, vector<Course_Code> uni,vector<Course*>& uniTemp, vector<Course_Code> track,vector<Course*>& trackTemp, vector<Course_Code> maj, vector<Course*>& majTemp);
	//it checks if crs is in vktr, if true, it removes it from vktr; and return true.
	bool isCourseInVectorAndRemove(Course* crs, vector<Course_Code>& vktr);
	//it check if crs is in vktr, if it's true, it pushs it to toBeAddedTo
	bool isCourseInVectorAndAddTo(Course* crs, vector<Course_Code> vktr, vector<Course*>& toBeAddedTo);
	//it searches for pointer of specific course, at a given course_code, /* not used */
	Course* getCourseForCourseCode(Course_Code);
	//It calculates the total number of credits in vector of course.
	int getCreditsCountInVector(vector<Course*> crss);
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool DeleteCourse(Course* pC, int year, SEMESTER sem,int orderOfCourse);
	void DeleteAll();
	void virtual DrawMe(GUI*) const;
	AcademicYear* getAcadamicYearAt(int year);
	//This function will determine topLeft and bottom right of each cours and academicyEAR
	void calculateGraphicsInfoForEachItem(int lastY);
	Course* getCourseAtGraphicsInfo(graphicsInfo point);
	Course* getCourseAtGraphicsInfo(graphicsInfo point, SEMESTER& deletedSemester, int& deletedYear, int& orderOfCourse);
	void getSemAndYearForPoint(int x, int y, SEMESTER& sem,int& year);

	bool isDependenciesCorrect();
	//This function direct the arguments to other two functions based on CoReq length, as every function has a unique body different from the other.
	bool isCoReqInSemester(list<Course_Code>& CoReq, list<Course*> currentSemester);
	bool checkForProgrammeRequirements(Rules& rules);

	string getStudentLevel();
	int isPetitionNeeded();
	double getGpa();
	int getDoneCredits();
	void setGpa(double gpa);
	void setDoneCredits(int credits);
	virtual ~StudyPlan();

	//The final version of validating pre/co requisits
	/*
		Every key in the outer map is Course* and its value is a map also
		the inner map has key PROBLEM_VALIDATION_TYPE with values of course codes that this problem relate to that.
		may be the same course* its value map, could have multiple problem elements, like problem with coreq and prereq.
	*/
	map<Course*, map<PROBLEM_VALIDATION_TYPE, vector<Course_Code>>>* checkCoPreReqValidation();
	//final version of validation of program require,ments.
	/*
		every course code is associated with it's problem type, by map.	
	*/
	map<Course_Code, PROBLEM_VALIDATION_TYPE>* checkForProgramReq(Rules rules);
};

