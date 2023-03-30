#pragma once

# include<iostream>
# include<vector>
# include<deque>
# include <sstream>  
class PmergeMe
{
    private:
        std::vector<unsigned int> vector;
        std::deque<unsigned int>  deque;
        std::string before;
        std::string after;
        clock_t t_vector;
        clock_t t_deque;

    public:
        PmergeMe();
        PmergeMe(char **ar);
        PmergeMe(const PmergeMe &P);
        PmergeMe& operator=(const PmergeMe &P);
        ~PmergeMe();
        void sort_verctor(void);
        void sort_deque(void);
        void display_data();
    class ERROR: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };
    class G_ERROR: public std::exception
    {
        public:
        virtual const char* what() const throw();
    };
};