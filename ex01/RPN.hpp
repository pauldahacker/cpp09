#ifndef RPN_HPP
# define RPN_HPP

# include "Utils.hpp"

class RPN
{
    public:
        static void calculate(const std::string &expression);
    private:
        RPN();
        RPN(const RPN &other);
        ~RPN();

        RPN &operator=(const RPN &other);
};

#endif