#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe merge(argc - 1, argv + 1);
        merge.sort();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}