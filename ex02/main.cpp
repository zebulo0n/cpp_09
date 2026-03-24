#include "PMergeMe.hpp"


int main (int ac, char **av)
{
    try {
        PMergeMe m(ac - 1);
        m.parseInput(av);
        m.printRecursionLayer(1, ac - 1);
        m.createAndSortPairs(ac - 1, 0);
        m.printLayers(m._totalLayers);
    }
     catch (const std::exception& e)
    {    std::cout << "Error: " << e.what() << std::endl;}
    
}


// int main (void)
// {
//     std::vector<int>jacob = constructJacobsthalIndexSequence(30);

//     std::cout << "FUCK CPP" << std::endl;
  
//     for (int i = 0; jacob[i]; i++)
//         std::cout << jacob[i] << std::endl;
//     std::cout << "WRITE SMTH" << std::endl;
// }