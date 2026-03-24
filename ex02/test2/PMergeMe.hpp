#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <vector>
# include <iostream>
# include <sstream>
# include <cmath>
# include <algorithm>

enum seqName
{
    MAIN,
    PEND
};

struct layer
{
    std::vector<int> main;
    std::vector<int> pend;
    std::vector<int> originalMain;  // winners before recursive sort, used to bound binary search
    int lvl;
};

class PMergeMe
{
private:
    layer               *RecursionLayers;
    std::vector<int>    output;
    int                 findArraySize(int recursionlvl, int arrName);
    void                swap(int Rlvl, int index);
    int                 _seqSpace;

public:
    void    parseInput(char **av);
    void    createAndSortPairs(int seqSize, int lvl);
    void    binarySearchInsert(int lvl);
    void    insertBaseCase(int lvl);
    void    insertPendIntoMain(int lvl);
    void    boundedInsert(std::vector<int> &mainSeq, const std::vector<int> &orig, int value, int pendIdx);
    PMergeMe(int elementCount);
    PMergeMe(const PMergeMe& other);
    PMergeMe &operator=(const PMergeMe &other);
    ~PMergeMe();
    int     _totalLayers;
    void    printOutput();
    void    printLayers(int totalLayers);
    void    printRecursionLayer(int recursionLvl, int seqSize);
    void    printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z);
    long    execTime;
};

void printVector(std::vector<int> output, std::string mess);

#endif
