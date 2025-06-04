#include "Utils.hpp"

static bool	isDecimal(const std::string &toConvert)
{
	for (size_t i = 0; i < toConvert.length(); ++i)
	{
		if (!std::isdigit(toConvert[i]))
			return (false);
	}
	return (true);
}

/*
https://en.cppreference.com/w/cpp/chrono/c/mktime
*/
bool	isDateValid(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);
	if (!isDecimal(yearStr) || !isDecimal(monthStr) || !isDecimal(dayStr))
		return (false);

	int year = std::atoi(date.c_str());
	int month = std::atoi(monthStr.c_str());
	int day = std::atoi(dayStr.c_str());

	struct tm	tm = {};
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	std::time_t temp = std::mktime(&tm);
	if (temp == -1 || tm.tm_year != year - 1900 || tm.tm_mon != month - 1 || tm.tm_mday != day)
		return (false);
	return (true);
}

/*
We make a valid float value in data between [0, FLT_MAX]
*/
bool	isValueValid(const std::string &value)
{
	if (value.empty())
		return (false);
	char	*endPtr;
	double tmp = std::strtod(value.c_str(), &endPtr);
	return (*endPtr == '\0' && tmp >= 0 && tmp <= FLT_MAX);
}

/*
this should be used after we know toConvert is a valid float literal
https://cplusplus.com/reference/cstdlib/strtod/
std::strtof() was added in C++99
*/
float convertToFloat(const std::string &toConvert)
{
	return (static_cast<float>(std::strtod(toConvert.c_str(), 0)));
}
