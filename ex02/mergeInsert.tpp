#ifndef MERGEINSERT_TPP
# define MERGEINSERT_TPP

# include <iostream>
# include <climits>
# include <cstdlib>
# include <fstream>
# include <string>

/*
In the algorithm, the Jacobsthal numbers are used as indexes
to binary insert B in the main chain.
Only the first 33 numbers of the Jacobsthal sequence are < INT_MAX:
https://oeis.org/A001045
But the algorithm inserts the first number (b1) in the main chain
and requires more than 1 element in the container, so we define it as
*/
# define JACOBSTHAL_LENGTH 32
static const int JACOBSTHAL_SEQUENCE[] = {
    0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845,
    43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811,
    22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};


template <typename T>
void printContainer(T &cont)
{
    for (typename T::iterator it=cont.begin(); it != cont.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

/*
std::lower_bound performs a log(n) search on a sorted vector or deque.
It returns the first element <= val
https://en.cppreference.com/w/cpp/algorithm/lower_bound.html
*/
template <typename T>
static void binaryInsertInt(T &mainChain, int &num)
{
    typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), num);
    mainChain.insert(pos, num);
}

template <typename T>
static void binaryInsert(T &mainChain, T &toInsert)
{
    int  len = toInsert.size();

    for (int i = 1; i < JACOBSTHAL_LENGTH; ++i)
    {
        int startIndex = std::min(JACOBSTHAL_SEQUENCE[i], len) - 1;
        int endIndex = JACOBSTHAL_SEQUENCE[i - 1] - 1;
        if (startIndex <= endIndex)
            break ;
        while (startIndex > endIndex)
            binaryInsertInt(mainChain, toInsert[startIndex--]);
    }
}

template <typename T>
void mergeInsert(T &intContainer)
{
    if (intContainer.size() <= 1)
        return ;

    // split
    T a, b;
    for (size_t i = 0; i + 1 < intContainer.size(); i += 2)
    {
        if (intContainer[i] > intContainer[i + 1])
        {
            a.push_back(intContainer[i]);
            b.push_back(intContainer[i + 1]);
        }
        else
        {
            a.push_back(intContainer[i + 1]);
            b.push_back(intContainer[i]);
        }
    }
    int hasLeftover = intContainer.size() % 2;
    int leftover = hasLeftover ? intContainer.back() : 0;

    // recursion on A
    mergeInsert(a);
    // start main chain with sorted A
    T mainChain;
    mainChain = a;

    // binary insertion from B to main chain
    if (b.size() >= 1)
        binaryInsert(mainChain, b);

    // insert leftover if n is odd
    if (intContainer.size() > 1 && hasLeftover)
        binaryInsertInt(mainChain, leftover);

    intContainer = mainChain;
}

#endif