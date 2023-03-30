#pragma once

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>

class BitcoinExchange
{
    private:
    std::map<std::string, std::string> database;
    std::string   date;
    std::string   value;
    float         fvalue;
    int           ivalue;
    float         factor;
    public:
    BitcoinExchange();
    BitcoinExchange(std::string path_data_base);
    BitcoinExchange(const BitcoinExchange& B);
    BitcoinExchange& operator=(const BitcoinExchange& B);
    ~BitcoinExchange();
    void handleBitcoinExchange(std::ifstream &infile);
    bool check_line(std::string line);
    bool check_date(std::string date);
    class ERROR_DATA: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };
    class EMPTY_DATA: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };

};
std::string itoa(int nbre);