#include "PMergeMe.hpp"
#include <fstream>
#include <sstream> 


//RECURSION LVL * SEQSIZE ==> 
void PMergeMe::printRecursionLayer(int recursionLvl, int seqSize)
{
    std::cout << "RECURSION LVL No" << recursionLvl << std::endl;
    std::cout << "Main Sequence : " ;
    for (int i = 1; i <= seqSize; i++)
        std::cout << _tab[seqSize + i * recursionLvl * MAIN] << "\t";
    std::cout << std::endl << "Pend Sequence : ";
    for (int i = 1; i <= seqSize; i++)
        std::cout << _tab[seqSize + i * recursionLvl * PEND] << "\t";
    std::cout << std::endl << std::endl;
}

void PMergeMe::createAndSortPairs(int seqSize, int recursionLvl)
{
   // static int recursionLvl = 1;        //since we begin at 1 for flattened 3d vector and 1 is already used by the parsed sequenced

    if (seqSize <= 1)
        return;
        
   // printRecursionLayer(recursionLvl, seqSize);

    int j = 1;
    int i = 1;
    //int max = seqSize % 2 ? seqSize : seqSize - 1;
    while (i < seqSize)
    {
        std::cout << "comparing : " << _tab[i * recursionLvl * MAIN] << "\t and \t" << _tab[(i + 1) * recursionLvl * MAIN] << std::endl;
        if (_tab[i * recursionLvl * MAIN] >= _tab[(i + 1) * recursionLvl * MAIN])
        {
            _tab[seqSize + j * (recursionLvl + 1) * MAIN] = _tab[i * recursionLvl * MAIN];
            _tab[seqSize + j * (recursionLvl + 1) * PEND] = _tab[(i + 1) * recursionLvl * MAIN];
        }
        else
        {
            _tab[seqSize + j * (recursionLvl + 1) * MAIN] = _tab[(i + 1) * recursionLvl * MAIN];
            _tab[seqSize + j * (recursionLvl + 1) * PEND] = _tab[i * recursionLvl * MAIN];
        }
        i += 2;
        j++;
    }
    if (seqSize % 2 == 1)
        _tab[j * (recursionLvl + 1) * PEND] = _tab[(seqSize - 1) * recursionLvl * MAIN];
    
    printRecursionLayer(recursionLvl, seqSize);
    recursionLvl++;
    createAndSortPairs(seqSize / 2, recursionLvl + 1);

}

void PMergeMe::printVector()
{
    for (int i = 0; _tab[i]; i++)
        std::cout << "at index " << i << "\t" << _tab[i] << std::endl;
}

void PMergeMe::parseInput(char **av)
{
    
    for (int i = 1; av[i] != NULL; i++)
    {
        std::stringstream ss(av[i]);
        if (!(ss >> _tab[i]))
            throw std::invalid_argument("Input contains non-parsable element");
    }
}

int findMemSpace(int n)
{
    static int res = 0;

    if (n == 1)
        return res;
    // std::cout << "res : " << res << std::endl;
    // std::cout << "n : " << n << std::endl;
    res += n;
    return (findMemSpace(n/2));
}

// Default constructor
PMergeMe::PMergeMe(int elementCount)
{
    int memSpace = findMemSpace(elementCount);
    _tab.reserve(memSpace);
    _tab.resize(memSpace, 0);

    //std::cout << "Default constructor called" << std::endl;
    return ;
}

// Copy constructor
PMergeMe::PMergeMe(const PMergeMe &other)
{
   // std::cout << "Copy constructor called" << std::endl;
    *this = other;
    return ;
}

// Assignment operator overload
PMergeMe &PMergeMe::operator=(const PMergeMe &other)
{
    ///std::cout << "Assignment operator called" << std::endl;
    if (this != &other)
    {
        //_name = other._name;
    }
    return (*this);
}

// Destructor
PMergeMe::~PMergeMe(void)
{
   // std::cout << "Destructor called" << std::endl;
    return ;
}


void PMergeMe::printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z) {
    if (tab.empty()) {
        std::cout << "[Empty Vector]" << std::endl;
        return;
    }

    std::cout << "Flattened 3D Vector Dimensions: " << X 
              << " x " << Y 
              << " x " << Z << "\n\n";

    for (size_t i = 0; i < X; ++i) {
        std::cout << "--- Layer i=" << i << " ---\n";
        for (size_t j = 0; j < Y; ++j) {
            std::cout << "  Row j=" << j << ": [ ";
            for (size_t k = 0; k < Z; ++k) {
                // Calculate manual index
                size_t index = i * (Y * Z) + j * Z + k;
                std::cout << tab[index] << " ";
            }
            std::cout << "]\n";
        }
        std::cout << "\n";
    }
}