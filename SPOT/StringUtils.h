#pragma once
#include <string>
#include <vector>
#include "DEFs.h"
using namespace std;
class StringUtils
{
public:
	
	static vector<string> getVectorFromStringSeperatedByTrim(string text, string by);
	//used to remove all white spaces from left and right
	/*
	\t: space
	\n: new line
	\v: unkown shape
	\f: unkwon shape
	\r: nothing
	*/
	static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
	static string& ltrim(string& str, const std::string& chars = "\t\n\v\f\r ");
	static string& trim(string& str);
	static string trimCourseCode(Course_Code str);
	static bool isStringContainsNumber(const string& c);
	static bool contains(const string& input, const string& searchable);


};

