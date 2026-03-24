#ifndef FORDJOHNSON_TPP
#define FORDJOHNSON_TPP

#include "PMergeMe.hpp"

template <typename Container>
void PMergeMe<Container>::FordJohnson(int ac, char **av)
{
    parseInput(av);
    double t1 = getTimeMicros();
    createAndSortPairs(ac - 1, 0);
    // printLayers();
    binarySearchInsert(0);
    double t2 = getTimeMicros();
    execTime = t2 - t1;
}

// init the recursion layers with the winner/loser competition
template <typename Container>
void PMergeMe<Container>::createAndSortPairs(int seqSize, int lvl)
{
    if (RecursionLayers[lvl].main.size() <= 1 || lvl >= _totalLayers)
        return;

    int j = 0;
    int i = 0;
    while (i < seqSize && (i + 1) < seqSize)
    {
        if (RecursionLayers[lvl].main[i] >= RecursionLayers[lvl].main[i + 1])
        {
            RecursionLayers[lvl + 1].main[j] = RecursionLayers[lvl].main[i];
            RecursionLayers[lvl + 1].pend[j] = RecursionLayers[lvl].main[i + 1];
        }
        else
        {
            RecursionLayers[lvl + 1].main[j] = RecursionLayers[lvl].main[i + 1];
            RecursionLayers[lvl + 1].pend[j] = RecursionLayers[lvl].main[i];
        }
        i += 2;
        j++;
    }
    if (seqSize % 2 == 1)
        RecursionLayers[lvl + 1].pend[j] = RecursionLayers[lvl].main[seqSize - 1];

    createAndSortPairs(seqSize / 2, lvl + 1);
    // technicaly can add second part of binarySearchInsert to avoid
    // re going up recursion lvls
}

template <typename Container>
void PMergeMe<Container>::binarySearchInsert(int lvl)
{
    if ((int)RecursionLayers[lvl].main.size() == 1)
    {
        insertBaseCase(lvl);
        return;
    }
    // goes up recursion lvls and sort base case
    binarySearchInsert(lvl + 1);

    // save sequences for later
    RecursionLayers[lvl].originalMain = RecursionLayers[lvl].main;
    RecursionLayers[lvl].main = RecursionLayers[lvl + 1].main;

    if ((int)RecursionLayers[lvl].pend.size() > 0)
        insertPendIntoMain(lvl);

    // final sorted sequence
    if (lvl == 0)
        output = RecursionLayers[0].main;
}

// insert base case as in sequence size = 1
template <typename Container>
void PMergeMe<Container>::insertBaseCase(int lvl)
{
    Container &m = RecursionLayers[lvl].main;
    Container &p = RecursionLayers[lvl].pend;

    int ps = findArraySize(lvl, PEND);

    for (int i = 0; i < ps; i++)
    {
        typename Container::iterator pos =
            std::lower_bound(m.begin(), m.end(), p[i]);
        m.insert(pos, p[i]);
    }
}

template <typename Container>
void PMergeMe<Container>::insertPendIntoMain(int lvl)
{
    Container &mainSeq = RecursionLayers[lvl].main;
    Container &pendSeq = RecursionLayers[lvl].pend;
    Container &orig = RecursionLayers[lvl].originalMain;

    // printVector(mainSeq, "main: ");
    // printVector(pendSeq, "pend: ");
    // printVector(orig, "orig: ");

    int pendSize = (int)pendSeq.size();
    Container insertOrder = constructJacobsthalIndexSequence(pendSize);

    for (int k = 0; k < (int)insertOrder.size(); k++)
    {
        int pendIdx = insertOrder[k] - 1;
        if (pendIdx < pendSize)
            boundedInsert(mainSeq, orig, pendSeq[pendIdx], pendIdx);
    }
}

// construct Jacobsthal index to improve binary (bounded) search performances
// ex : jacob = 0 1 1 3 5 11, need 14 index : 1 3 2 5 4 11 10 9 8 7 6 12 13 14
template <typename Container>
Container PMergeMe<Container>::constructJacobsthalIndexSequence(int pendSize)
{
    Container seq;
    Container jacobNums;

    for (int n = 1; jacobsthal(n) <= pendSize; n++)
    {
        int j = jacobsthal(n);
        if (jacobNums.empty() || j != jacobNums.back())
            jacobNums.push_back(j);
    }
    int prev = 0;
    for (int i = 0; i < (int)jacobNums.size(); i++)
    {
        int curr = jacobNums[i];
        for (int val = curr; val > prev; val--)
            if (val <= pendSize)
                seq.push_back(val);
        prev = curr;
    }
    for (int val = prev + 1; val <= pendSize; val++)
        seq.push_back(val);
    return seq;
}

template <typename Container>
void PMergeMe<Container>::boundedInsert(Container &mainSeq,
                                        const Container &orig,
                                        int value, int pendIdx)
{
    typename Container::iterator searchEnd = mainSeq.end();

    if (pendIdx < (int)orig.size())
    {
        int winner = orig[pendIdx];
        typename Container::iterator winPos =
            std::lower_bound(mainSeq.begin(), mainSeq.end(), winner);
        if (winPos != mainSeq.end())
            searchEnd = winPos + 1; // bound binary search to winner of the inserted one (from pend)
    }

    typename Container::iterator pos =
        std::lower_bound(mainSeq.begin(), searchEnd, value);
    mainSeq.insert(pos, value);
    // printVector(mainSeq, "after insertion main: ");
}

#endif