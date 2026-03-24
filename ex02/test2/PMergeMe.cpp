#include "PMergeMe.hpp"

// ─────────────────────────────────────────────
//  Jacobsthal (iterative)
// ─────────────────────────────────────────────
static int jacobsthal(int n)
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

static std::vector<int> constructJacobsthalIndexSequence(int pendSize)
{
    std::vector<int> seq;
    std::vector<int> jacobNums;

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

// ─────────────────────────────────────────────
//  Constructor
//
//  FIX: allocate _totalLayers + 1 layers.
//  Your createAndSortPairs writes to RecursionLayers[lvl + 1]
//  at every recursion level including the last one,
//  so with only totalRlvl slots the last write is OOB.
// ─────────────────────────────────────────────
PMergeMe::PMergeMe(int elementCount)
{
    int totalRlvl = (int)std::ceil(log2((double)elementCount));
    _seqSpace    = elementCount;
    _totalLayers = totalRlvl;

    RecursionLayers = new layer[totalRlvl + 1];  // +1 for the OOB fix
    for (int i = 0; i <= totalRlvl; i++)
    {
        RecursionLayers[i].main.resize(findArraySize(i, MAIN), 0);
        RecursionLayers[i].pend.resize(findArraySize(i, PEND), 0);
        RecursionLayers[i].lvl = i;
    }
    output.resize(elementCount, 0);
}

// ─────────────────────────────────────────────
//  parseInput — your code, unchanged
// ─────────────────────────────────────────────
void PMergeMe::parseInput(char **av)
{
    for (int i = 1; av[i] != NULL; i++)
    {
        std::stringstream ss(av[i]);
        int val;
        if (!(ss >> val) || val < 0)
            throw std::invalid_argument("Input contains non-parsable or negative element");
        RecursionLayers[0].main[i - 1] = val;
    }
    printVector(RecursionLayers[0].main, "Before:\t");
}

// ─────────────────────────────────────────────
//  createAndSortPairs — your code, one fix:
//  added  || lvl >= _totalLayers  to the base-case
//  guard so we never write past the allocated array.
// ─────────────────────────────────────────────
void PMergeMe::createAndSortPairs(int seqSize, int lvl)
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
}

void printVector(std::vector<int> output, std::string mess)
{
    std::cout << mess;
    for (size_t i = 0; i < output.size(); i++)
        std::cout << output[i] << " ";
    std::cout << std::endl;
}

// ─────────────────────────────────────────────
//  insertBaseCase
//  Base case for binarySearchInsert.
//  main has exactly 1 element (deepest sorted winner).
//  Insert all pend elements written at this level into it.
// ─────────────────────────────────────────────
void PMergeMe::insertBaseCase(int lvl)
{
    std::vector<int> &m = RecursionLayers[lvl].main;
    std::vector<int> &p = RecursionLayers[lvl].pend;
    // printVVector(m, "main :");
    // printVVector(p, "pend : ");
    int ps = findArraySize(lvl, PEND);
 
    for (int i = 0; i < ps; i++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(m.begin(), m.end(), p[i]);
        m.insert(pos, p[i]);
    }
    // printLayers(_totalLayers);
    // printVVector(m, "main :");
    // printVVector(p, "pend : ");
}
 
// ─────────────────────────────────────────────
//  boundedInsert
//  Insert a single value into mainSeq using binary search.
//  The search is bounded by the position of its paired winner
//  in originalMain — pend[pendIdx] < originalMain[pendIdx]
//  is guaranteed by createAndSortPairs, so we never need to
//  search past the winner's current position in mainSeq.
// ─────────────────────────────────────────────
void PMergeMe::boundedInsert(std::vector<int> &mainSeq,
                              const std::vector<int> &orig,
                              int value, int pendIdx)
{
    std::vector<int>::iterator searchEnd = mainSeq.end();
 
    if (pendIdx < (int)orig.size())
    {
        int winner = orig[pendIdx];
        std::vector<int>::iterator winPos =
            std::lower_bound(mainSeq.begin(), mainSeq.end(), winner);
        if (winPos != mainSeq.end())
            searchEnd = winPos + 1;
    }
 
    std::vector<int>::iterator pos =
        std::lower_bound(mainSeq.begin(), searchEnd, value);
    mainSeq.insert(pos, value);
}
 
// ─────────────────────────────────────────────
//  insertPendIntoMain
//  Inserts all pend elements at this level into mainSeq
//  in Jacobsthal order, using boundedInsert for each one.
// ─────────────────────────────────────────────
void PMergeMe::insertPendIntoMain(int lvl)
{
    std::vector<int> &mainSeq = RecursionLayers[lvl].main;
    std::vector<int> &pendSeq = RecursionLayers[lvl].pend;
    std::vector<int> &orig    = RecursionLayers[lvl].originalMain;
 
    int pendSize = (int)pendSeq.size();
    std::vector<int> insertOrder = constructJacobsthalIndexSequence(pendSize);
 
    for (int k = 0; k < (int)insertOrder.size(); k++)
    {
        int pendIdx = insertOrder[k] - 1;
        if (pendIdx < pendSize)
            boundedInsert(mainSeq, orig, pendSeq[pendIdx], pendIdx);
    }
}
 
// ─────────────────────────────────────────────
//  binarySearchInsert
//  Orchestrates the bottom-up merge:
//    1. Recurse to sort the winners at lvl+1
//    2. Save main (the unsorted winner list) before overwriting
//    3. Pull the sorted result up from lvl+1
//    4. Insert pend into the sorted main in Jacobsthal order
//    5. At level 0, copy the result into output
// ─────────────────────────────────────────────
void PMergeMe::binarySearchInsert(int lvl)
{
    if ((int)RecursionLayers[lvl].main.size() == 1)
    {
        insertBaseCase(lvl);
        return;
    }
 
    binarySearchInsert(lvl + 1);
  
    RecursionLayers[lvl].originalMain = RecursionLayers[lvl].main;
    RecursionLayers[lvl].main         = RecursionLayers[lvl + 1].main;
 
    if ((int)RecursionLayers[lvl].pend.size() > 0)
        insertPendIntoMain(lvl);
 
    if (lvl == 0)
        output = RecursionLayers[0].main;
}
 

// ─────────────────────────────────────────────
//  findArraySize — your code, unchanged
// ─────────────────────────────────────────────
int PMergeMe::findArraySize(int recursionlvl, int arrName)
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

// ─────────────────────────────────────────────
//  Print helpers — your code, unchanged
// ─────────────────────────────────────────────
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

void PMergeMe::printRecursionLayer(int lvl, int seqSize)
{
    (void)seqSize;
    std::cout << "RECURSION LVL No" << lvl << std::endl;
    std::cout << "Main Sequence : ";
    for (size_t i = 0; i < RecursionLayers[lvl].main.size(); i++)
        std::cout << RecursionLayers[lvl].main[i] << "\t";
    std::cout << std::endl << "Pend Sequence : ";
    for (size_t i = 0; i < RecursionLayers[lvl].pend.size(); i++)
        std::cout << RecursionLayers[lvl].pend[i] << "\t";
    std::cout << std::endl << std::endl;
}



void PMergeMe::printOutput()
{
    std::cout << "After:\t";
    for (size_t i = 0; i < output.size(); i++)
        std::cout << output[i] << " ";
    std::cout << std::endl;
}

void PMergeMe::printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z)
{
    for (size_t x = 0; x < X; x++)
        for (size_t y = 0; y < Y; y++)
            for (size_t z = 0; z < Z; z++)
                std::cout << tab[x * Y * Z + y * Z + z] << " ";
    std::cout << std::endl;
}

void PMergeMe::swap(int Rlvl, int index)
{
    int tmp = RecursionLayers[Rlvl].main[index];
    RecursionLayers[Rlvl].main[index] = RecursionLayers[Rlvl].pend[index];
    RecursionLayers[Rlvl].pend[index] = tmp;
}

// ─────────────────────────────────────────────
//  Canonical form
// ─────────────────────────────────────────────
PMergeMe::PMergeMe(const PMergeMe &other)
{
    *this = other;
}

PMergeMe &PMergeMe::operator=(const PMergeMe &other)
{
    if (this != &other) {}
    return (*this);
}

PMergeMe::~PMergeMe(void)
{
    delete[] RecursionLayers;
}
