#pragma once

//This file contains data sturctures required to store all registration RULES
#include <vector>
using namespace std;
#include "DEFs.h"


//Information for each course
//Title, code, credit hours, and pre-req list, type
struct CourseInfo
{
	string Title;
	Course_Code	Code;
	vector<Course_Code> PreReqList;	//Pre-requesite list of courses codes
	vector<Course_Code> CoReqList;	//Co-requesite list of courses codes
	int Credits;
	string type;	//Univ, track, major course
};

struct AcademicYearOfferings
{
	string Year; //academic year of the offerings e.g. 2019-2020


	//Each year has an array of of 3 vectors of courses CODE. 
	//Each vector cossrsponds to a semester
	//So Offerings[FALL] is a vector of courses offered in FALL in THAT year
	//So Offerings[SPRING] is a vector of courses offered in SPRING in THAT year
	//So Offerings[SUMMER] is a vector of courses offered in SUMMER in THAT year
	vector<Course_Code> Offerings[SEM_CNT];
};

struct Rules	//contains all objects for registrations rules
{
	//TODO: add more fields if needed


	AcademicYearOfferings OffringsList[5];	//all offerings for all acedmic years
	vector<CourseInfo>* CourseCatalog=new vector<CourseInfo>;	//List of ALL courses with full info


	int TotalCredits;
	int SemMinCredit;		//min no. of credit hours per semester
	int SemMaxCredit;		//max no. of credit hours per semester
	int ReqUnivCreditsCompulsory;		//total no. of credits req by "Compulsory" Univ courses 
	int ReqUnivCreditsElective;		//total no. of credits req by "Elective" Univ courses
	int ReqTrackCredits;	//total no. of credits req by Track courses
	//int ReqTrackCreditsElective
	int ReqTrackCreditsElective;
	int ReqMajorCreditsCompulsory;	//total no. of credits req by "Compulsory" Major courses
	int ReqMajorCreditsElective;	//total no. of credits req by "Elective" Major courses
	int ConcentrationsNumber; //no. of concentration of the student's major

	vector<int> ReqConcentrationCredits; //total no of concentration credits

	vector<Course_Code> UnivCompulsory;	//Univ Compulsory courses
	vector<Course_Code> UnivElective;	//Univ Elective courses

	vector<Course_Code> TrackCompulsory;//Track Compulsory courses
	vector<Course_Code> TrackElective;
	vector<Course_Code> MajorCompulsory;//Major Compulsory courses
	vector<Course_Code> MajorElective;	//Major Elective courses
	vector < vector<Course_Code> > ConcentrationsCompulsory; //concentration compulsory courses
	vector < vector<Course_Code> > ConcentrationsElective; //concentration elective courses

	vector<Course_Code> MinorCourses; //Minor course codes

public:
	void insertCourseInfoIntoCourseCatalog(CourseInfo* crsinfo);
	CourseInfo* getCourseInfoAtCode(const Course_Code& courseCode);

};

