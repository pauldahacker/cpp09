#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const int n, char *input[])
{
    parseInput(n, input);
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq), hasLeftover(other.hasLeftover), leftover(other.leftover)
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
        hasLeftover = other.hasLeftover;
        leftover = other.leftover;
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
    double vecTime = static_cast<double>(vecEnd - vecStart) / CLOCKS_PER_SEC * 1000;
    std::clock_t deqStart = std::clock();
    mergeInsert(deq);
    std::clock_t deqEnd = std::clock();
    double deqTime = static_cast<double>(deqEnd - deqStart) / CLOCKS_PER_SEC * 1000;
    std::cout << "After: ";
    printContainer(vec);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : "
        << vecTime << "  milliseconds" << std::endl;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::deque : "
        << deqTime << "  milliseconds" << std::endl;
}

void PmergeMe::parseInput(const int n, char *input[])
{
    for (int i = 0; i < n; ++i)
    {
        std::string elem(input[i]);
        if (!isPositiveInt(elem))
            throw (std::runtime_error("Not a valid positive integer: " + elem));
        int value = std::atoi(input[i]);
        if (std::find(vec.begin(), vec.end(), value) != vec.end())
            throw (std::runtime_error("Repeating integer in input: " + elem));
        vec.push_back(value);
        deq.push_back(value);
    }
}