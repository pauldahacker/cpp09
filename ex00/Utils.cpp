#include "Utils.hpp"

/*
https://en.wikipedia.org/wiki/IEEE_754-1985#Representation_of_non-numbers
https://www.doc.ic.ac.uk/~eedwards/compsys/float/nan.html
*/
static bool	isNan(double d)
{
	return (d != d);
}

/*
To check for infinity, first check that x != NaN.
The IEEE 754 has undefined operations, such as inf - inf, 0 / 0, etc.
-> if x is (+-)infinity, x - x = NaN.
*/
static bool	isInf(double d)
{
	return (!isNan(d) && isNan(d - d));
}

/*
The bounds of floats are [-FLT_MAX, FLT_MAX]
(FLT_MIN = smallest float value > 0)
*/
bool	isFloat(std::string toConvert)
{
	if (toConvert.empty())
		return (false);
	char	*endPtr;
	double tmp = std::strtod(toConvert.c_str(), &endPtr);
	return (*endPtr == '\0' && (isNan(tmp) || isInf(tmp)
		|| (tmp >= -FLT_MAX && tmp <= FLT_MAX)));
}

bool	isInt(std::string toConvert)
{
	long	tmp = std::strtol(toConvert.c_str(), 0, 10);
	return (tmp <= INT_MAX && tmp >= INT_MIN);
}

/*
this should be used after we know toConvert is a valid float literal
https://cplusplus.com/reference/cstdlib/strtod/
std::strtof() was added in C++99
*/
float convertToFloat(std::string toConvert)
{
	return (static_cast<float>(std::strtod(toConvert.c_str(), 0)));
}
