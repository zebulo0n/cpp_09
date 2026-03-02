#include "RPN.hpp"

int main (int ac, char **av)
{
    try {
        if (ac != 2)
            throw std::runtime_error("usage : ./rpn [reverse polish notation]");
        RPN rpn;
        std::string arg(av[1]);
        int res = rpn.processArg(arg);

        std::cout << "Result : " << res << std::endl;
    }
    catch (const std::exception& e)
    {    std::cout << "Error: " << e.what() << std::endl;}

}