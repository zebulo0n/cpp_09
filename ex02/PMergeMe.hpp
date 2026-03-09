#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <iostream>

enum seqName
{
    MAIN = 1,
    PEND = 2
};

class PMergeMe
{
    private:
        std::vector<int>_tab;

    public:
        void parseInput(char **av);
        void createAndSortPairs(int seqSize, int recursionLvl);
        PMergeMe(int elementCount);
        PMergeMe(const PMergeMe& other);
        PMergeMe &operator=(const PMergeMe &other);
        ~PMergeMe();

        void printVector();
        void printRecursionLayer(int recursionLvl, int seqSize);
        void printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z);


};

#endif

