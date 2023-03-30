#pragma once

#include <stack>
#include <iostream>

class RPN
{
    private:
        std::stack<int> stack;
        int res;
    public:
    RPN();
    RPN(char **ar);
    RPN(const RPN& B);
    RPN& operator=(const RPN& B);
    ~RPN();
    int get_res(void);
    void do_operations(int op1 , int op2, char operation);
    class ERROR_DATA: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };
    
    class DIVED_ZERO: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };
};
bool check_operator(char c);