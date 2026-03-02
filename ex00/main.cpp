#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <fstream>
#include <sstream>   
#include "BitcoinExchange.hpp" 


int main (int ac, char **av)
{
    try {
        if (ac != 2)
            throw (std::runtime_error("Usage : ./btc input.csv"));
        std::stringstream ss(av[1]);
        std::string input ;
        ss >> input;
        BitcoinExchange btc(input);
    }
    catch (const std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}
