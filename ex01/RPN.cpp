#include "RPN.hpp"

bool check_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c =='/')
        return true;
    return false;
}

RPN::RPN()
{

}

RPN::RPN(char **ar)
{
    int i = 1;
    int a; 
    int b;
   while(ar[i])
   {
        int j = 0;
        while(ar[i][j])
        {
            if (ar[i][j] != ' ' && ar[i][j] !='\t')
            {
                if (isdigit(ar[i][j]) )
                {
                    this->stack.push(ar[i][j] - '0');
                }
                else if (check_operator(ar[i][j]))
                {
                    a = stack.top();
                    stack.pop();
                    b = stack.top();
                    stack.pop();
                    do_operations(b, a, ar[i][j]);
                }
                else
                    throw (RPN::ERROR_DATA());
            }
            j++;
        }
        i++;
   }
   this->res = stack.top();
   stack.pop();
}

void RPN::do_operations(int op1, int op2, char operation)
{
    int res;
    switch (operation)
    {
    case '+':
        res = op1 + op2;
        this->stack.push(res);
        break;
    case '-':
        res = op1 - op2;
        this->stack.push(res);
        break;
    case '*':
        res = op1 * op2;
        this->stack.push(res);
        break;
    default:
        if (op2 == 0)
            throw (RPN::DIVED_ZERO());
        else
            res = op1 / op2;
            this->stack.push(res);
        break;
    }

}

int RPN::get_res(void)
{
    return (this->res);
}

const char *RPN::ERROR_DATA::what() const throw()
{
    return ("\033[31m\033[1m ERROR\033[0m");
}

const char *RPN::DIVED_ZERO::what() const throw()
{
    return ("\033[31m\033[1m Division by zero \033[0m");
}
RPN::RPN(const RPN& B)
{
    *this = B;
}

RPN& RPN::operator=(const RPN& B)
{
    this->stack = B.stack;
    return (*this);
}

RPN::~RPN()
{

}