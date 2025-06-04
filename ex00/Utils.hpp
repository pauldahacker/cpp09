#ifndef INCLUDE_HPP
# define INCLUDE_HPP

# include <iostream>
# include <climits>
# include <cfloat>
# include <cmath>
# include <cstdlib>
# include <ctime>
# include <string>

bool	isDateValid(const std::string &date);
bool	isValueValid(const std::string &value);
float   convertToFloat(const std::string &toConvert);

#endif