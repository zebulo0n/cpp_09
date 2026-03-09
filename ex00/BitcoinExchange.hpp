#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <exception>
# include <map>
# include <string>
# include <fstream>
# include <sstream>    
# include <time.h>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _data;

        void _loadData(void);
        void _checkHeader (std::string &line);
        void _checkDate (std::string &date);
        int _getToken(std::stringstream &dateFd);
        double _checkExchangeRate(std::string &line);

        void _checkFileExtension(std::string fileName);
    
        void _calculateOutput(std::string &inputFile);
        double _getBitcoinValue(std::string &date, double value);
        double _checkValue(std::string &rate);
        void _checkHeaderInput(std::string &line);

        //utils
        std::string _removeSpaces(std::string str);


    public:
        BitcoinExchange(std::string &inputFile);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
};


#endif

