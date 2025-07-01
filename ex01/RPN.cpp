#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN::~RPN()
{}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return (*this);
}

/*
https://www.geeksforgeeks.org/stringstream-c-applications/
*/
void    RPN::calculate(const std::string &expression)
{
    std::stack<int>     stack;
    std::string         elem;
    std::stringstream   s(expression);

    while (s >> elem)
    {
        if (!isInt(elem) && !isOperation(elem))
            throw (std::runtime_error("Invalid element: " + elem));
        if (isInt(elem))
            stack.push(std::atoi(elem.c_str()));
        else if (stack.size() < 2)
            throw (std::runtime_error("Missing operand before: " + elem));
        else
            applyOperation(elem, stack);
    }
    if (stack.size() != 1)
        throw (std::runtime_error("Missing operator."));
    std::cout << stack.top() << std::endl;
}