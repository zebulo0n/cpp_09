#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <iostream>

enum seqName
{
    MAIN,
    PEND
};

struct layer
{
    std::vector<int> main;
    std::vector<int> pend;
    int lvl;
};

class PMergeMe
{
    private:
        layer *RecursionLayers;
        std::vector<int> output;
        


        // int index(int recursionlvl, int arrName, int i);
        int findArraySize(int recursionlvl, int arrName);
        void swap(int Rlvl, int index);
        // int getLvlOffset(int targetLvl);
        int _seqSpace;
        // int _memSpace;
        // std::vector<int>_tab;

    public:
        void parseInput(char **av);
        void createAndSortPairs(int seqSize, int lvl);
        void binarySearchInsert(int lvl);
        PMergeMe(int elementCount);
        PMergeMe(const PMergeMe& other);
        PMergeMe &operator=(const PMergeMe &other);
        ~PMergeMe();

        int _totalLayers;
        


        void printVector();
        void printLayers(int totalLayers);
        void printRecursionLayer(int recursionLvl, int seqSize);
        void printFlattened3D(const std::vector<int>& tab, size_t X, size_t Y, size_t Z);


};

#endif

