#include "BitcoinExchange.hpp"
#include <sstream>
#include <bits/stdc++.h>

static bool isSpace(char c)
{
    return std::isspace(static_cast<unsigned char>(c));
}

std::string BitcoinExchange::_removeSpaces(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), isSpace), str.end());
    return str;
}

void BitcoinExchange::_checkHeader(std::string &line)
{
    line = _removeSpaces(line);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Data file header not comform");
}

double BitcoinExchange::_checkExchangeRate(std::string &line)
{
    std::stringstream ss(line);
    double rate;

    if (!(ss >> rate) || !ss.eof())
        throw std::runtime_error("Rate value not numeric : " + line);
    return rate;
}

int BitcoinExchange::_getToken(std::stringstream &dateFd)
{
    std::string token;
    int value;

    getline(dateFd, token, '-');        //remove spaces??
    std::stringstream ss(token);
    if (!(ss >> value))
        throwInvalidArgument("Date not conform : ", token);
    return value;
}

void BitcoinExchange::_checkDate(std::string &date)
{
    std::stringstream dateFd(date);
    tm tm = {};

    tm.tm_year = _getToken(dateFd) - 1900;
    tm.tm_mon = _getToken(dateFd) - 1;
    tm.tm_mday = _getToken(dateFd);
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    if (mktime(&tm) == -1)
        throw std::runtime_error("Date do not exist : " + date);
}

void BitcoinExchange::_loadData(void)
{
    std::ifstream dataFd("data.csv");
    if (!dataFd.is_open())
        throw std::runtime_error("couldn't open data file");
    std::string line;
    std::getline(dataFd, line);
    _checkHeader(line);

    while(std::getline(dataFd, line))
    {
        std::stringstream lineFd(line);
        std::string date;
        std::string rateStr;
        double rate;

        if (!std::getline(lineFd, date, ',') || 
            !std::getline(lineFd, rateStr))
            throw std::runtime_error("bad data file line: " + line);
        rate = _checkExchangeRate(rateStr);
        _checkDate(date);
        _data[date] = rate;
    }
}

double BitcoinExchange::_getBitcoinValue(std::string &date, double value)
{
    std::map<std::string, double>::iterator it =_data.lower_bound(date);
    if (it == _data.end() || it->first != date)
    {
        if (it == _data.begin())
            throw std::invalid_argument("No rate available for date: " + date);
        --it;
    }

    return it->second * value;

}

double BitcoinExchange::_checkValue(std::string &rate)
{
    std::stringstream ss(rate);
    double value;

    if (!(ss >> value) || !ss.eof())
        throw std::invalid_argument("Value not numeric : " + rate);

    if (value < 0 || value > 1000)
        throw std::invalid_argument("Value not in range : must be between 0 and 1000 and is : " + rate);

    return value;
}

void BitcoinExchange::_checkHeaderInput(std::string &line)
{
    line = _removeSpaces(line);
    if (line != "date|value")
        throw std::runtime_error("Data file header not comform");
}

void BitcoinExchange::_calculateOutput(std::string &inputFile)
{
    std::ifstream inputFd(inputFile);
    if (!inputFd.is_open())
        throw std::runtime_error("couldn't open input file");
    std::string line;
    std::getline(inputFd, line);
    _checkHeaderInput(line); //to change

    while (std::getline(inputFd, line))
    {
        try {
            std::stringstream lineFd(line);
            std::string date;
            std::string valueStr;
            double value;
            double res;

            if (!std::getline(lineFd, date, '|') ||
                !std::getline(lineFd, valueStr))
                throw std::invalid_argument("bad input");
            _checkDate(date);
            value = _checkValue(valueStr);
            res = _getBitcoinValue(date, value);
            std::cout << date << " => " << value << " = " << res << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
void BitcoinExchange::_checkFileExtension(std::string fileName)
{
    size_t len = fileName.length();
    if (len < 4)
        throw (std::runtime_error("File extension is not .csv"));

    size_t extensionPos = len - 4;
    std::string extension = fileName.substr(extensionPos);
    if (extension != ".csv")
        throw (std::runtime_error("File extension is not .csv"));
}
// Default constructor
BitcoinExchange::BitcoinExchange(std::string &inputFile)
{
    //std::cout << "Default constructor called" << std::endl;
    _loadData();
    _checkFileExtension(inputFile);
    _calculateOutput(inputFile);
   // printMapToFile(_data, "testData");
    return ;
}

// Copy constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
   // std::cout << "Copy constructor called" << std::endl;
    *this = other;
    return ;
}

// Assignment operator overload
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    //std::cout << "Assignment operator called" << std::endl;
    if (this != &other)
    {
        //_name = other._name;
    }
    return (*this);
}

// Destructor
BitcoinExchange::~BitcoinExchange(void)
{
    //std::cout << "Destructor called" << std::endl;
    return ;
}

