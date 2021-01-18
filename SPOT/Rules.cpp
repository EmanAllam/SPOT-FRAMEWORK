#include "Rules.h"
#include <iostream>
using namespace std;
void Rules::insertCourseInfoIntoCourseCatalog(CourseInfo* crsinfo)
{
	CourseCatalog->push_back((*crsinfo));
}

CourseInfo* Rules::getCourseInfoAtCode(const Course_Code& courseCode)
{

	for (auto ci = CourseCatalog->begin(); ci != CourseCatalog->end(); ++ci)
	{
		if ((ci->Code) != courseCode)
		{
			continue;

		}
		//Little more Understand
		return &(*ci);
		//return (*CourseCatalog[0]);

	}
	
	//cout <<courseCode <<",TEST,5,,"<< endl;
	//CourseInfo* cf=new CourseInfo;
	//return cf;
	throw "Course Not Found";
}
