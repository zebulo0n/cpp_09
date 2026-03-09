#include "PMergeMe.hpp"



int main (int ac, char **av)
{
    try {
        PMergeMe m(ac - 1);
        m.parseInput(av);
        m.printRecursionLayer(1, ac - 1);
        m.createAndSortPairs(ac - 1, 1);
        m.printVector();
    }
     catch (const std::exception& e)
    {    std::cout << "Error: " << e.what() << std::endl;}
    
}