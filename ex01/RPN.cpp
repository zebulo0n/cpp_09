#include "RPN.hpp"


void RPN::calculate (char sign)
{
    if (nbs.size() < 2)
        throw std::runtime_error("expression is not properly formated");
    int second = getTopNb();
    int first = getTopNb();
    int res;

    int i = 0;
    for (; i < 4 && _sign[i] != sign; i++);
    if (i == 4)
        throw std::runtime_error("how tf did that even happen");
    res = (this->*_calcFunctions[i])(first, second);
    nbs.push(res);
}

int RPN::processArg(std::string arg)
{
    for (int i = 0; arg[i] != '\0'; i++)
    {
        if (isspace(arg.at(i)))
            continue;
        else if (isnum(arg.at(i)))
            nbs.push(arg.at(i) - 48);
        else if (issign(arg.at(i)))
            calculate(arg.at(i));
        else if (i > 0 && isnum(arg.at(i - 1)) && isnum(arg.at(i)))
            throw std::runtime_error("only single digit numbers are allowed");
        else 
            throw std::runtime_error("wrong character in expression argument");
    }
    if (nbs.size() != 1)
        throw std::runtime_error("expression not properly formated");
    return (nbs.top());
}

/*********ORTHODOX CANONICAL FORM**********/

// Default constructor
RPN::RPN(void)
{
   // std::cout << "Default constructor called" << std::endl;
    _sign[0] = '+';
    _sign[1] = '-';
    _sign[2] = '*';
    _sign[3] = '/';

    _calcFunctions[0] = &RPN::add;
    _calcFunctions[1] = &RPN::substract;
    _calcFunctions[2] = &RPN::multiply;
    _calcFunctions[3] = &RPN::divide;
    return ;
}

// Copy constructor
RPN::RPN(const RPN &other)
{
   // std::cout << "Copy constructor called" << std::endl;
    nbs = other.nbs;

    for (int i = 0; i < 4; i++)
    {
        _sign[i] = other._sign[i];
        _calcFunctions[i] = other._calcFunctions[i];
    }
    return ;
}

// Assignment operator overload
RPN &RPN::operator=(const RPN &other)
{
  //  std::cout << "Assignment operator called" << std::endl;
    if (this != &other)
    {
        nbs = other.nbs;

        for (int i = 0; i < 4; i++)
        {
            _sign[i] = other._sign[i];
            _calcFunctions[i] = other._calcFunctions[i];
        }
    }
    return (*this);
}

// Destructor
RPN::~RPN(void)
{
    //std::cout << "Destructor called" << std::endl;
    return ;
}


/************UTILS*************/

bool RPN::isnum (char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool RPN::issign (char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

bool RPN::isValid(char c)
{
    if (isspace(c) || isnum(c) || issign(c))
        return true;
    return false;
}

int RPN::getTopNb(void)
{
    int res = nbs.top();
    nbs.pop();
    return res;
}

int RPN::add (int first, int second)
{
    return (first + second);
}

int RPN::substract (int first, int second)
{
    return (first - second);
}

int RPN::multiply (int first, int second)
{
    return (first * second);
}

int RPN::divide (int first, int second)
{
    if (second == 0)
        throw std::runtime_error("Division by 0 is not allowed");
    return (first / second);
}

/************DEBUG*************/

// void printStack(std::stack<int> &stack)
// {
//     std::stack<int> tmp(stack);

//     std::cout << std::endl << "TOP" << std::endl;
//     while (!tmp.empty())
//     {
//         std::cout << tmp.top() << std::endl;
//         tmp.pop(); 
//     }
//     std::cout << "BOTTOM" << std::endl << std::endl;
// }