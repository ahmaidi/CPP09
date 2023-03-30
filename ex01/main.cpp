# include "RPN.hpp"

int main(int ac, char **ar)
{
    if (ac > 1)
    {
        try
        {
            RPN rpn(ar);
            std::cout << rpn.get_res() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else
        std::cerr << "nbre of agrs wrong"<<std::endl;
}