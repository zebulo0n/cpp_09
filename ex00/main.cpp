#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <fstream>
#include <sstream>    


void parse_file(std::map<std::string, double> data, char sep)
{
    std::ifstream file("data.csv");
    if (!file)
        throw (std::invalid_argument("Couldn't open data file"));
    std::string line;
    std::string date;
    double rate;
    size_t sepPos;
    while (getline(file, line, sep))
    {
        sepPos = line.find(sep);
        date = line.substr()
        data.insert()
    }

}

int main (int ac, char **av)
{
    try {
        if (ac != 2)
            throw (std::invalid_argument("Usage : ./btc input.csv"));
        std::map<std::string, double> data;
        parse_file(&data, ',');
    }
}