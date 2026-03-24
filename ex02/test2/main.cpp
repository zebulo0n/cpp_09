#include "PMergeMe.hpp"
#include <sys/time.h>

long getTimeMicros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L + tv.tv_usec;
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: no input" << std::endl;
        return 1;
    }
    try
    {
        PMergeMe m(ac - 1);
        m.parseInput(av);
        long t1 = getTimeMicros();
        m.createAndSortPairs(ac - 1, 0);
        m.binarySearchInsert(0);
        long t2 = getTimeMicros();
        m.execTime = t1 - t2;
        m.printOutput();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
