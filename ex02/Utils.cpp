#include "Utils.hpp"

bool    isPositiveInt(const std::string &elem)
{
    char *rest = 0;
    long val = std::strtol(elem.c_str(), &rest, 10);
    if (val < 0 || val > INT_MAX || *rest != '\0')
        return (false);
    return (true);
}