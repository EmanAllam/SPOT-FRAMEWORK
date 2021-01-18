#include "StringUtils.h"
#include <string>
#include <vector>
#include <iostream>
#include "DEFs.h"
using namespace std;



vector<string> StringUtils::getVectorFromStringSeperatedByTrim(string text, string by)
{

	vector<string> tempVktr;
	//it's expected to be like "And" and I make " And " so it's 3+2(space)
	by = " " + by + " ";
	int lengthBy = by.length();
	int startIndex = 0;
	int lastLength = 0;
	while (lastLength <= text.length())
	{

		int pos = text.find(by, startIndex);
		string tmpString = text.substr(startIndex, pos - lastLength);
		startIndex = pos + lengthBy;
		StringUtils::trim(tmpString);
		tempVktr.push_back(tmpString);
		lastLength += tmpString.length() + lengthBy;

	}
	return tempVktr;
}

string& StringUtils::trim(string& str)
{
	str = ltrim(str);
	str = rtrim(str);
	return str;
}

string StringUtils::trimCourseCode(Course_Code str)
{
	string newstr = ltrim(str);
	newstr = rtrim(str);
	return newstr;
}
string& StringUtils::ltrim(string& str, const std::string& chars)
{
	//0 holes for starting index
	//second arg is len
	//find_first_not_of: return the position not the index
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

std::string& StringUtils::rtrim(std::string& str, const std::string& chars)
{
	//if it takes one Arg: it removes all char after pos <BOLD> pos not Index<BOLD>
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}


bool StringUtils::isStringContainsNumber(const string& c)
{
	//to be understood later
	return false;
	if (c.find('0') != std::string::npos ||
		c.find('1') != std::string::npos ||
		c.find('2') != std::string::npos ||
		c.find('3') != std::string::npos ||
		c.find('4') != std::string::npos ||
		c.find('5') != std::string::npos ||
		c.find('6') != std::string::npos ||
		c.find('7') != std::string::npos ||
		c.find('8') != std::string::npos ||
		c.find('9') != std::string::npos)
	{
		return false;
	}
	return true;
}

bool StringUtils::contains(const string& input, const string& searchable)
{
	if (input.find(searchable) != std::string::npos)
		return true;
	return false;
}