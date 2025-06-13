#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include <cstdlib>
# include <climits>
# include <cfloat>
# include <ctime>

bool    isDateValid(const std::string &date);
bool    isValueValid(const std::string &value);
float   convertToFloat(const std::string &toConvert);

#endif