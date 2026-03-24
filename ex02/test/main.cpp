#include "PMergeMe.hpp"

// Returns microseconds since epoch


int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: no input" << std::endl;
        return 1;
    }

    try
    {        
        PMergeMe m;
        m.parseInput(av);
        m.printSeq("Before: ", m.vecInput);
        m.sortAndTime();
        m.printSeq("After: ", m.vecSorted);
        m.printTime();

        
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}