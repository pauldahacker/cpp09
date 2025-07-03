#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const int n, char *input[])
{
    parseInput(n, input);
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq)
{
}

PmergeMe::~PmergeMe()
{}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
    return (*this);
}

void PmergeMe::sort()
{
    std::cout << "Before: ";
    printContainer(vec);
    std::clock_t vecStart = std::clock();
    mergeInsert(vec);
    std::clock_t vecEnd = std::clock();
    mergeInsert(deq);
    std::clock_t deqEnd = std::clock();
    double vecTime = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000;
    double deqTime = static_cast<double>(deqEnd - vecEnd) / CLOCKS_PER_SEC * 1000;
    std::cout << "After: ";
    printContainer(vec);
    std::cout << "Time to sort a range of " << vec.size() << " elements with std::vector : "
        << vecTime << "  milliseconds" << std::endl;
    std::cout << "Time to sort a range of " << deq.size() << " elements with std::deque : "
        << deqTime << "  milliseconds" << std::endl;
}

static bool    isPositiveInt(const std::string &elem)
{
    char *rest = 0;
    long val = std::strtol(elem.c_str(), &rest, 10);
    if (val < 0 || val > INT_MAX || *rest != '\0')
        return (false);
    return (true);
}

/*
Parsing cannot be done in parallel for the vector and deque
because we need to time the data management part for each.
*/
void PmergeMe::parseInput(const int n, char *input[])
{
    std::clock_t vecStart = std::clock();
    for (int i = 0; i < n; ++i)
    {
        std::string elem(input[i]);
        if (!isPositiveInt(elem))
            throw (std::runtime_error("Not a valid positive integer: " + elem));
        int value = std::atoi(input[i]);
        if (std::find(vec.begin(), vec.end(), value) != vec.end())
            throw (std::runtime_error("Repeating integer in input: " + elem));
        vec.push_back(value);
    }
    std::clock_t vecEnd = std::clock();
    for (int i = 0; i < n; ++i)
    {
        std::string elem(input[i]);
        if (!isPositiveInt(elem))
            throw (std::runtime_error("Not a valid positive integer: " + elem));
        int value = std::atoi(input[i]);
        if (std::find(deq.begin(), deq.end(), value) != deq.end())
            throw (std::runtime_error("Repeating integer in input: " + elem));
        deq.push_back(value);
    }
    std::clock_t deqEnd = std::clock();
    double vecTime = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000;
    double deqTime = static_cast<double>(deqEnd - vecEnd) / CLOCKS_PER_SEC * 1000;
    std::cout << "Time to parse a range of " << vec.size() << " elements with std::vector : "
        << vecTime << "  milliseconds" << std::endl;
    std::cout << "Time to parse a range of " << deq.size() << " elements with std::deque : "
        << deqTime << "  milliseconds" << std::endl;
}