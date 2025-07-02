#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include "mergeInsert.tpp"
# include <algorithm>
# include <ctime>
# include <deque>
# include <vector>

class PmergeMe
{
    public:
        PmergeMe(const int n, char *input[]);
        PmergeMe(const PmergeMe &other);
        ~PmergeMe();

        PmergeMe &operator=(const PmergeMe &other);

        void sort();
    private:
        std::vector<int>    vec;
        std::deque<int>     deq;
    
        void parseInput(const int n, char *input[]);
};

#endif