#include "PmergeMe.hpp"

int main(int ac, char **ar)
{
    if (ac > 1)
    {
        try
        {
            PmergeMe P(ar);
            P.sort_verctor();
            P.sort_deque();
            P.display_data();
        }
         catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
        std::cerr << "\033[31m\033[1mnbre of args is Wrong\033[0m" << std::endl;
    return 0;
}