#ifndef DEBUG_TPP
#define DEBUG_TPP

#include "PMergeMe.hpp"

template <typename Container>
PMergeMe<Container>::PMergeMe(int elementCount)
{
    int totalRlvl = (int)std::ceil(log2((double)elementCount));
    _seqSpace = elementCount;
    _totalLayers = totalRlvl;

    RecursionLayers = new layer<Container>[totalRlvl + 1];
    for (int i = 0; i <= totalRlvl; i++)
    {
        RecursionLayers[i].main.resize(findArraySize(i, MAIN), 0);
        RecursionLayers[i].pend.resize(findArraySize(i, PEND), 0);
        RecursionLayers[i].lvl = i;
    }
    output.resize(elementCount, 0);
}

template <typename Container>
PMergeMe<Container>::PMergeMe() {}

template <typename Container>
PMergeMe<Container>::PMergeMe(const PMergeMe &other)
{
    *this = other;
}

template <typename Container>
PMergeMe<Container> &PMergeMe<Container>::operator=(const PMergeMe<Container> &other)
{
    if (this != &other)
    {
    }
    return (*this);
}

template <typename Container>
PMergeMe<Container>::~PMergeMe(void)
{
    delete[] RecursionLayers;
}

//

template <typename Container>
void PMergeMe<Container>::printLayers()
{
    for (int l = 0; l < _totalLayers; l++)
    {
        std::cout << "RECURSION LVL " << l << std::endl;
        std::cout << "Main Sequence : ";
        for (size_t i = 0; i < RecursionLayers[l].main.size(); i++)
            std::cout << RecursionLayers[l].main[i] << "\t";
        std::cout << std::endl;
        std::cout << "Pend Sequence : ";
        for (size_t i = 0; i < RecursionLayers[l].pend.size(); i++)
            std::cout << RecursionLayers[l].pend[i] << "\t";
        std::cout << std::endl
                  << std::endl;
    }
}

template <typename Container>
void PMergeMe<Container>::printRecursionLayer(int lvl, int seqSize)
{
    (void)seqSize;
    std::cout << "RECURSION LVL No" << lvl << std::endl;
    std::cout << "Main Sequence : ";
    for (size_t i = 0; i < RecursionLayers[lvl].main.size(); i++)
        std::cout << RecursionLayers[lvl].main[i] << "\t";
    std::cout << std::endl
              << "Pend Sequence : ";
    for (size_t i = 0; i < RecursionLayers[lvl].pend.size(); i++)
        std::cout << RecursionLayers[lvl].pend[i] << "\t";
    std::cout << std::endl
              << std::endl;
}

// from when i wanted to optimize memory by storing the Recursion LVLs in 3D vector flattened (did not work)
// but flattened multi-dimensionnal arrays == cool concept for memory
template <typename Container>
void PMergeMe<Container>::printFlattened3D(const Container &tab, size_t X, size_t Y, size_t Z)
{
    for (size_t x = 0; x < X; x++)
        for (size_t y = 0; y < Y; y++)
            for (size_t z = 0; z < Z; z++)
                std::cout << tab[x * Y * Z + y * Z + z] << " ";
    std::cout << std::endl;
}

template <typename Container>
void printVector(Container output, std::string mess)
{
    std::cout << mess;
    for (size_t i = 0; i < output.size(); i++)
        std::cout << output[i] << " ";
    std::cout << std::endl;
}

#endif