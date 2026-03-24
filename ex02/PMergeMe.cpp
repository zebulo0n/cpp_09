#include "PMergeMe.hpp"
#include <fstream>
#include <sstream> 
#include <cmath>

void PMergeMe::printLayers(int totalLayers)
{
    for (int l = 0; l < totalLayers; l++)
    {
        std::cout << "RECURSION LVL " << l << std::endl;

        std::cout << "Main Sequence : ";
        for (size_t i = 0; i < RecursionLayers[l].main.size(); i++)
            std::cout << RecursionLayers[l].main[i] << "\t";

        std::cout << std::endl;

        std::cout << "Pend Sequence : ";
        for (size_t i = 0; i < RecursionLayers[l].pend.size(); i++)
            std::cout << RecursionLayers[l].pend[i] << "\t";

        std::cout << std::endl << std::endl;
    }
}

//RECURSION LVL * SEQSIZE ==> 
void PMergeMe::printRecursionLayer(int lvl, int seqSize)
{
    (void)seqSize;
    // int mainSize = findArraySize(lvl, MAIN);
    // int pendSize = findArraySize(lvl, PEND);

    std::cout << "RECURSION LVL No" << lvl << std::endl;
    std::cout << "Main Sequence : " ;
    for (int i = 0; RecursionLayers[lvl].main[i]; i++)
        std::cout << RecursionLayers[lvl].main[i] << "\t";
    std::cout << std::endl << "Pend Sequence : ";
    for (int i = 0; RecursionLayers[lvl].pend[i]; i++)
        std::cout << RecursionLayers[lvl].pend[i] << "\t";
    std::cout << std::endl << std::endl;
}


//when seqsize impair last comparison is between the 2 winner of this RLvl ????
void PMergeMe::createAndSortPairs(int seqSize, int lvl)
{
   // static int recursionLvl = 1;        //since we begin at 1 for flattened 3d vector and 1 is already used by the parsed sequenced

    if (RecursionLayers[lvl].main.size() <= 1)
        return;
        
    int j = 0;
    int i = 0;
    //int max = seqSize % 2 ? seqSize : seqSize - 1;
    while (i < seqSize && (i + 1) < seqSize)
    {
        std::cout << "comparing : " << RecursionLayers[lvl].main[i] << "\t and \t" << RecursionLayers[lvl].main[i + 1] << "\t with seqsize = " << seqSize << std::endl;
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
    
   // printRecursionLayer(recursionLvl, seqSize);
    //recursionLvl++;
    createAndSortPairs((seqSize) / 2, lvl + 1);
}

int jacobsthal(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++)
    {
        int tmp = b + 2 * a;
        a = b;
        b = tmp;
    }
    return b;
}


std::vector<int> constructJacobsthalIndexSequence(int pendSize)
{
    std::vector<int> seq;

    // Step 1: collect Jacobsthal numbers > 0 that fit within pendSize
    // jacobsthal(1) = 1, jacobsthal(2) = 1, jacobsthal(3) = 3, ...
    // start at n=1 to get the sequence 1, 3, 5, 11, 21...
    std::vector<int> jacobNums;
    for (int n = 1; jacobsthal(n) <= pendSize; n++)
    {
        int j = jacobsthal(n);
        // skip duplicates (jacobsthal(1) == jacobsthal(2) == 1)
        if (jacobNums.empty() || j != jacobNums.back())
            jacobNums.push_back(j);
    }

    // Step 2: build insertion order
    // for each Jacobsthal number, insert from it DOWN TO previous+1
    int prev = 0;
    for (int i = 0; i < (int)jacobNums.size(); i++)
    {
        int curr = jacobNums[i];
        // insert curr, curr-1, curr-2, ..., prev+1
        for (int val = curr; val > prev; val--)
        {
            if (val <= pendSize)
                seq.push_back(val);
        }
        prev = curr;
    }

    // Step 3: append any remaining indices past the last Jacobsthal number
    // (in case pendSize > last jacobsthal number, fill forward)
    for (int val = prev + 1; val <= pendSize; val++)
        seq.push_back(val);

    return seq;
}

// void PMergeMe::binarySearchInsert(int lvl)
// {
//     static int i = 0;

//     if (lvl == 0)
//         return ;
    
// }


void PMergeMe::parseInput(char **av)
{
    
    for (int i = 1; av[i] != NULL; i++)
    {
        std::stringstream ss(av[i]);
        if (!(ss >> RecursionLayers[0].main[i - 1]))
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

int PMergeMe::findArraySize(int recursionlvl, int arrName)      //special case pend of Rlvl1
{
    if (recursionlvl == 0)
        return (arrName == MAIN ? _seqSpace : 0);
    int arrSize = _seqSpace;
    int prevArrSize;        //more like Main and Pend size of this Rlvl
    
    for (int i = 1; i < recursionlvl; i++)
        arrSize /= 2;

    prevArrSize = arrSize;
    arrSize /= 2;

    if (arrName == PEND && prevArrSize % 2 == 1)
        arrSize++;

    return arrSize;
}

// Default constructor
PMergeMe::PMergeMe(int elementCount)
{
    int totalRlvl = std::ceil(log2(elementCount));
    _seqSpace = elementCount;
    _totalLayers = totalRlvl;
    std::cout << "nb of Rlayers : " << totalRlvl << "\t element count : " << elementCount << std::endl;
    RecursionLayers = new layer[totalRlvl];
    for (int i = 0; i < totalRlvl; i++)
    {
        RecursionLayers[i].main.resize(findArraySize(i, MAIN));
        RecursionLayers[i].pend.resize(findArraySize(i, PEND));

    }
    output.resize(elementCount);
   // RecursionLayers[0].main.resize(elementCount);

     
    // _memSpace = findMemSpace(elementCount);
    // _tab.reserve(_memSpace);
    // _tab.resize(_memSpace, 0);

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
   delete [] RecursionLayers;
    return ;
}


// void PMergeMe::printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z) {
//     if (tab.empty()) {
//         std::cout << "[Empty Vector]" << std::endl;
//         return;
//     }

//     std::cout << "Flattened 3D Vector Dimensions: " << X 
//               << " x " << Y 
//               << " x " << Z << "\n\n";

//     for (size_t i = 0; i < X; ++i) {
//         std::cout << "--- Layer i=" << i << " ---\n";
//         for (size_t j = 0; j < Y; ++j) {
//             std::cout << "  Row j=" << j << ": [ ";
//             for (size_t k = 0; k < Z; ++k) {
//                 // Calculate manual index
//                 size_t index = i * (Y * Z) + j * Z + k;
//                 std::cout << tab[index] << " ";
//             }
//             std::cout << "]\n";
//         }
//         std::cout << "\n";
//     }
// }



// int PMergeMe::findArraySize(int recursionlvl, int arrName)      //special case pend of Rlvl1
// {
//     if (recursionlvl == 0)
//         return (arrName == MAIN ? _seqSpace : 0);
//     int arrSize = _seqSpace;
//     int prevArrSize;        //more like Main and Pend size of this Rlvl
    
//     for (int i = 1; i < recursionlvl; i++)
//         arrSize /= 2;

//     prevArrSize = arrSize;
//     arrSize /= 2;

//     if (arrName == PEND && prevArrSize % 2 == 1)
//         arrSize++;

//     return arrSize;
// }

// int PMergeMe::getLvlOffset(int targetLvl)
// {
//     int offset = 0;
//     for (int lvl = 1; lvl < targetLvl; lvl++) {
//         int mainSize = findArraySize(lvl, MAIN);
//         int pendSize = findArraySize(lvl, PEND);
//         offset += (mainSize + pendSize);
//     }
//     return offset;
// }

// int PMergeMe::index(int recursionlvl, int arrName, int i)
// {
//     int lvlStart = getLvlOffset(recursionlvl);
//     int mainSize = findArraySize(recursionlvl, MAIN);
//    // std::cout << "ARRAY SIZE = " << arrSize << std::endl;

//     int arrOffset = 0;
//      if (arrName == MAIN) {
//         arrOffset = i;
//     } else { 
//         arrOffset = mainSize + i;
//     }

//     return lvlStart + arrOffset;

// }