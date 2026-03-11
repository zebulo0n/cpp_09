#include "PMergeMe.hpp"



// int main (int ac, char **av)
// {
//     try {
//         PMergeMe m(ac - 1);
//         m.parseInput(av);
//        // m.printRecursionLayer(1, ac - 1);
//         m.createAndSortPairs(ac - 1, 0);
//         m.printLayers(m._totalLayers);
//     }
//      catch (const std::exception& e)
//     {    std::cout << "Error: " << e.what() << std::endl;}
    
// }


int Jacobsthal(int n)
{
    // base case
    if (n == 0)
        return 0;

    // base case
    if (n == 1)
        return 1;

    // recursive step.
    return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2);
}


std::vector<int> constructJacobsthalIndexSequence (int pendSize)
{
    std::vector<int> seq;
    std::vector<int>jacobSeq;
    seq.resize(pendSize);
    jacobSeq.resize(pendSize);

    for (int i = 0; Jacobsthal(i + 2) <= pendSize; i++)
        jacobSeq[i] = Jacobsthal(i + 2);

    // int j = 0;
    // for (; j < pendSize; j++)
    //     jacobSeq.at(j) = Jacobsthal(j);
    
    for (int i = 0; jacobSeq[i]; i++)
        std::cout << "TA MERE C UNE PUTE " << jacobSeq.at(i) << std::endl;

    
    int i = 0;

    int j = 0;
    int lastJacob = jacobSeq[j];
    seq[i++] = jacobSeq[j++];
    for (; jacobSeq[j]; j++)
    {
        seq[i++] = jacobSeq[j];
        int value = jacobSeq[j];
        while (value != lastJacob + 1)
            seq[i++] = --value;
        lastJacob = jacobSeq[j];
    }
    while (lastJacob < pendSize)
        seq[i++] = ++lastJacob;

    // int j = 1;
    // int i = 0;
    // int lastJacobsthal = Jacobsthal(1);
    // int value = lastJacobsthal;
    // seq[i++] = value;
    // for (; i < pendSize; i++)
    // {
    //     value = Jacobsthal(j);
    //     //lastJacobsthal = value;
    //     j++;
    //     seq[i++] = value;
    //     while (value != lastJacobsthal + 1)
    //         seq[i++] = value--;
    // }
    return seq;
}

int main (void)
{
    std::vector<int>jacob = constructJacobsthalIndexSequence(30);

    std::cout << "FUCK CPP" << std::endl;
  
    for (int i = 0; jacob[i]; i++)
        std::cout << jacob[i] << std::endl;
    std::cout << "WRITE SMTH" << std::endl;
}