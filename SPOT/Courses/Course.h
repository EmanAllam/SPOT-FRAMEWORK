#pragma once
#include <string>
#include <list>
//#include "../StudyPlan/StudyPlan.h"

#include "..\DEFs.h"

#include "../GUI/Drawable.h"
using namespace std;
class StudyPlan;

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	double Points; //for ex: course of 3 crd and grade A has points 3*4=12
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
public:
	Course(Course_Code r_code,string r_title, int crd);
	void setPreReq(list<Course_Code>);
	void setCoReq(list<Course_Code>);
	//
	void setType(string);
	void setPoints(string letter, StudyPlan* plan);
	void setDone(StudyPlan* plan, int choice);
	bool getDone();
	double getPoints();
	string getType() const;
	//
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	string getPreReqAsString() const;
	string getCoReqAsString() const;
	list<Course_Code> getPreReq()const;
	list<Course_Code> getCoReq()const;

	void addPreReq(string preReq);
	void addCoReq(string CoReq);
	void DrawMe(GUI*) const;
	bool operator=(const Course& anotherCourse);
	virtual ~Course();

};
