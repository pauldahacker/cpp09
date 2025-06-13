#include "Utils.hpp"

bool    isOperation(const std::string &elem)
{
    return (elem == "+" || elem == "-"
        || elem == "*" || elem == "/");
}

bool	isInt(const std::string &elem)
{
    if (elem.empty())
        return (false);
    char last = elem[elem.size() - 1];
    if (!std::isdigit(last))
        return (false);
    long number = std::atol(elem.c_str());
	return (number <= INT_MAX && number >= INT_MIN);
}

void     applyOperation(const std::string &op, std::stack<int> &stack)
{
    if (stack.size() <= 1)
        return ;
    int popped = stack.top();
    stack.pop();
    long long result = stack.top();
    if (op == "/")
    {
        if (popped == 0)
            throw (std::runtime_error("Division by zero."));
        else
            result /= popped;
    }
    else if (op == "*")
        result *= popped;
    else if (op == "+")
        result += popped;
    else if (op == "-")
        result -= popped;
    if (result < INT_MIN || result > INT_MAX)
        throw (std::runtime_error("Result not in INT range."));
    stack.top() = static_cast<int>(result);
}
