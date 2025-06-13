#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
        std::cout << "Error: Too few or too many arguments." << std::endl;
    else
    {
        try
        {
            RPN::calculate(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return (0);
}