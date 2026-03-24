#ifndef HELPER_TPP
#define HELPER_TPP

#include "PMergeMe.hpp"

template <typename Container>
void PMergeMe<Container>::parseInput(char **av)
{
    for (int i = 1; av[i] != NULL; i++)
    {
        std::stringstream ss(av[i]);
        int val;
        if (!(ss >> val) || val < 0)
            throw std::invalid_argument("Input contains non-parsable or negative element");
        RecursionLayers[0].main[i - 1] = val;
    }
    // printVector(RecursionLayers[0].main, "Before:\t");
}

template <typename Container>
int PMergeMe<Container>::findArraySize(int recursionlvl, int arrName)
{
    if (recursionlvl == 0)
        return (arrName == MAIN ? _seqSpace : 0);
    int arrSize = _seqSpace;
    int prevArrSize;
    for (int i = 1; i < recursionlvl; i++)
        arrSize /= 2;
    prevArrSize = arrSize;
    arrSize /= 2;
    if (arrName == PEND && prevArrSize % 2 == 1)
        arrSize++;
    return arrSize;
}

template <typename Container>
int PMergeMe<Container>::jacobsthal(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++)
    {
        int tmp = b + 2 * a;
        a = b;
        b = tmp;
    }
    return b;
}

template <typename Container>
void PMergeMe<Container>::printOutput()
{
    int prec = output[0];
    std::cout << "After:\t";
    for (size_t i = 0; i < output.size(); i++)
    {
        std::cout << output[i] << " ";
        if (prec > output[i])
            throw(std::runtime_error("sequence not sorted"));
        prec = output[i];
    }

    std::cout << std::endl;
}

template <typename Container>
void PMergeMe<Container>::printTime(std::string type)
{
    std::cout << "Time to process a range of " << output.size()
              << " elements with std::" << type << " : " << execTime << " us" << std::endl;
}

long getTimeMicros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000L + tv.tv_usec);
}

#endif