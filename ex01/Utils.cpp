#include "Utils.hpp"

bool    isOperation(const std::string &elem)
{
    return (elem == "+" || elem == "-"
        || elem == "*" || elem == "/");
}

/*
https://cplusplus.com/reference/istream/istream/operator%3E%3E/
uses string stream to detect if the string is a valid int.
s >> number attemps to store the string as an int.
s >> rest checks if there is something after the number.
*/
bool	isInt(const std::string &elem)
{
    if (elem.empty())
        return (false);
    std::stringstream   s(elem);
    int number;
    s >> number;
    if (s.fail())
        return (false);
    char rest;
    s >> rest;
    return (s.fail());
}

/*
applies op to the 2 top elements of the stack (assumes size > 1).
1) copy top of the stack in a tmp value ("popped"),
2) pop the stack,
3) apply op to new top of the stack using the popped value.
*/
void     applyOperation(const std::string &op, std::stack<int> &stack)
{
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
