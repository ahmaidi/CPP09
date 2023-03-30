#include "PmergeMe.hpp"


PmergeMe::PmergeMe()
{

}
PmergeMe::PmergeMe(char **ar)
{
    std::string str;
    int i = 1;
    int tmp;
    (void)ar;
    this->before ="Before: ";
    while(ar[i])
    {
        str.append(ar[i]);
        this->before += str + " ";
        if(str.find_first_not_of("01234567789") != std::string::npos)
            throw PmergeMe::ERROR();
        tmp = atoi(str.c_str());
        if (tmp < 0)
            throw PmergeMe::G_ERROR();
        this->vector.push_back(tmp);
        this->deque.push_back(tmp);
        str.clear();
        i++;
    }

}
PmergeMe::PmergeMe(const PmergeMe &P)
{
    *this = P;
}
PmergeMe& PmergeMe::operator=(const PmergeMe &P)
{
    this->deque = P.deque;
    this->vector = P.vector;
    return(*this);
}
const char *PmergeMe::ERROR::what() const throw()
{
    return ("\033[31m\033[1mInvalid data\033[0m");
}

const char *PmergeMe::G_ERROR::what() const throw()
{
    return ("\033[31m\033[1marg greater than MAX_INT \033[0m");
}

void PmergeMe::sort_verctor()
{
    clock_t start, end;
    start = clock();
    int tmp = -1;
    if (this->vector.size() % 2 != 0)
    {
        tmp = this->vector[this->vector.size() - 1];
        this->vector.pop_back();
    }
    std::vector<std::pair<unsigned int, unsigned int> > sort_vec; 
    size_t i = 0;
    while(i < this->vector.size())
    {
        std::pair<unsigned int, unsigned int> p;
        p.first = this->vector.at(i);
        p.second = this->vector.at(i + 1);
        if (p.first > p.second)
            std::swap(p.first, p.second);
        sort_vec.push_back(p);
        i+=2;
    }
    this->vector.clear();
    std::sort(sort_vec.begin(),sort_vec.end());
    for(std::vector<std::pair<unsigned int, unsigned int> >::iterator it = sort_vec.begin(); it < sort_vec.end(); it++)
    {
        this->vector.push_back((*it).first);
    }
    std::vector<unsigned int>::iterator low;
    for(std::vector<std::pair<unsigned int, unsigned int> >::iterator it = sort_vec.begin(); it < sort_vec.end(); it++)
    {
        low = std::upper_bound(this->vector.begin(),this->vector.end(), (*it).second);
        this->vector.insert(low ,(*it).second);
    }
    if (tmp != -1)
    {
        low = std::upper_bound(this->vector.begin(),this->vector.end(), tmp);
        this->vector.insert(low ,tmp);
    }
    end = clock();
    this->t_vector = (end - start);
}
void PmergeMe::sort_deque()
{
    clock_t start, end;
    start = clock();
    int tmp;
    if (this->deque.size() % 2 != 0)
    {
        tmp = this->deque.back();
        this->deque.pop_back();
    }
    std::deque<std::pair<unsigned int, unsigned int> > sort_vec; 
    size_t i = 0;
    while(i < this->deque.size())
    {
        std::pair<unsigned int, unsigned int> p;
        p.first = this->deque.at(i);
        p.second = this->deque.at(i + 1);
        if (p.first > p.second)
            std::swap(p.first, p.second);
        sort_vec.push_back(p);
        i+=2;
    }
    this->deque.clear();
    std::sort(sort_vec.begin(),sort_vec.end());
    for(std::deque<std::pair<unsigned int, unsigned int> >::iterator it = sort_vec.begin(); it < sort_vec.end(); it++)
    {
        this->deque.push_back((*it).first);
    }
    std::deque<unsigned int>::iterator low;
    for(std::deque<std::pair<unsigned int, unsigned int> >::iterator it = sort_vec.begin(); it < sort_vec.end(); it++)
    {
        low = std::upper_bound(this->deque.begin(),this->deque.end(), (*it).second);
        this->deque.insert(low ,(*it).second);
    }
    if (tmp != -1)
    {
        low = std::upper_bound(this->deque.begin(),this->deque.end(), tmp);
        this->deque.insert(low ,tmp);
    }
    end = clock();
    this->t_deque = (end - start);
}

void PmergeMe::display_data()
{
    std::cout << this->before<< std::endl;
    std::cout <<  "after: ";
    for(std::vector<unsigned int>::iterator it = this->vector.begin(); it < this->vector.end(); it++)
    {
       std::cout << (*it) << " ";
    }
    std::cout << "\n";
    std::cout << "Time to process a range of " << this->vector.size() << " elements with std::vector : " << this->t_vector<< " us" << std::endl;
    std::cout << "Time to process a range of " << this->deque.size() << " elements with std::deque : " << this->t_deque << " us"<< std::endl;

}
PmergeMe::~PmergeMe()
{

}