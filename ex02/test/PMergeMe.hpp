#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <sys/time.h>

#define MAIN 0
#define PEND 1

struct layer {
    std::vector<int> main;
    std::vector<int> pend;
};

// --- Jacobsthal helpers (free functions) ---
int         jacobsthal(int n);
std::vector<int> constructJacobsthalIndexSequence(int pendSize);

// --- Ford-Johnson on a generic container ---
template <typename Container>
Container fordJohnsonSort(Container seq);

class PMergeMe
{
public:
    PMergeMe(void);
    PMergeMe(const PMergeMe &other);
    PMergeMe &operator=(const PMergeMe &other);
    ~PMergeMe(void);

    void    parseInput(char **av);
    void    printSeq(std::string mess, std::vector<int> seq);
    void    sortAndTime(void);
    void    printTime(void);

    void    createAndSortPairs(int seqSize, int lvl);
    //void    binarySearchInsert(int lvl);
    void    printLayers(int totalLayers);
    void    printRecursionLayer(int lvl, int seqSize);
    int     findArraySize(int recursionlvl, int arrName);

    //layer   *RecursionLayers;
    std::vector<int> output;
  //  int     _totalLayers;

    std::vector<int> vecInput;
    std::deque<int>  deqInput;

    std::vector<int> vecSorted;
    std::deque<int> deqSorted;

    long vecTime;
    long deqTime;

private:
    int     _seqSpace;
};