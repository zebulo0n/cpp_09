#include "PMergeMe.hpp"

// void verify(void)
// {
//     try {
//         std::string str;
//         do {
//             std::cin >> str;
//         } while (str != "After:");
//         std::stringstream tmp(str);
//         int prec;
//         tmp >> prec;
//         std::cout << "FIRST : " << prec;
//         int curr;

//         while (std::cin >> curr)
//         {
//             if (prec > curr)
//                 throw (std::runtime_error("sequence not sorted"));
//             prec = curr;
//         }
//         throw (std::runtime_error("sequence sorted"));
//     }
//     catch (const std::runtime_error& e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
// }

void printInput(char **av)
{
    std::cout << "Before:\t";
    for (int i = 1; av[i]; i++)
        std::cout << av[i] << " ";
    std::cout << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2)
        std::cerr << "Error: no input" << std::endl;
    try
    {
        PMergeMe<std::vector<int>> vector(ac - 1);
        PMergeMe<std::deque<int>> deque(ac - 1);

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
