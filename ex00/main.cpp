#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    std::ifstream infile; 
    if (argc == 2)
    {
        infile.open(argv[1]);
        if (infile.is_open())
        {
            try
            {
                BitcoinExchange BitcoinExchange("/Users/ahmaidi/Desktop/cpp09/ex00/data.csv");
                BitcoinExchange.handleBitcoinExchange(infile);
            }
            catch(const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else
            std::cerr << "\033[31m\033[1mError: couldn't open file.\033[0m"<< std::endl;
    }
    else
        std::cerr << "\033[31m\033[1mError: number of args not valid.\033[0m"<< std::endl;
    return 0;
}