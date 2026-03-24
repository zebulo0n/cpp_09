#include "PMergeMe.hpp"

void printInput(char **av)
{
    std::cout << "Before:\t";
    for (int i = 1; av[i]; i++)
        std::cout << av[i] << " ";
    std::cout << std::endl;
}

//./PMergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
int main(int ac, char **av)
{
    if (ac < 2)
        std::cerr << "Error: no input" << std::endl;
    try
    {
        PMergeMe<std::vector<int> > vector(ac - 1);
        PMergeMe<std::deque<int> > deque(ac - 1);

        vector.FordJohnson(ac, av);
        deque.FordJohnson(ac, av);

        printInput(av);
        vector.printOutput();
        vector.printTime("vector");
        deque.printTime("deque");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
