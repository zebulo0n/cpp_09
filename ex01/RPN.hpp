#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>

class RPN
{
    private:
        std::stack<int>nbs;

        char _sign[4];
        int(RPN::*_calcFunctions[4])(int, int);

        void calculate(char sign);

        int add (int first, int second);
        int substract (int first, int second);
        int multiply (int first, int second);
        int divide (int first, int second);

        int getTopNb(void);
        bool isValid (char c);
        bool isnum (char c);
        bool issign (char c);
       
    public:
        RPN(void);
        RPN(const RPN& other);
        RPN &operator=(const RPN &other);
        ~RPN();

        int processArg(std::string arg);
};

#endif