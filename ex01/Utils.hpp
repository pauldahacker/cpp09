#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <stack>

bool    isOperation(const std::string &elem);
bool	isInt(const std::string &elem);
void    applyOperation(const std::string &op,std::stack<int> &stack);

#endif