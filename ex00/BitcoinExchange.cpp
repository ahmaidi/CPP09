#include "BitcoinExchange.hpp"

std::string itoa(int nbre)
{
    std::string str;
    if (nbre >= 1 && nbre <=9)
    {
        str += '0';
        str += ('0' + nbre);
    }
    else
    {
        if (nbre / 1000)
            str.append(1,'0' + nbre / 1000);
        if ((nbre / 1000) || (nbre % 1000) / 100)
            str.append(1, '0' + ((nbre % 1000) / 100));
        str.append(1,'0' + (((nbre % 1000) % 100) / 10));
        str.append(1, '0' + (((nbre % 1000) % 100) % 10));
    }
    return (str);
}
bool BitcoinExchange::check_date(std::string date)
{
    std::stringstream ss;
    size_t year = 0;
    size_t month = 0;
    size_t day = 0;
    std::string date_tmp;
     if(date.find_first_not_of("01234567789-") != std::string::npos)
            return false;
    int	c = count(date.begin(), date.end(), '-');
    date_tmp = date;
    if (c != 2)
        return false;
    char *token = strtok((char *)date.c_str(), "-");
    while (token != NULL)
    {
        if (!year)
        {
            year = atoi(token);
            token = strtok(NULL, "-");
            continue;
        }
        if (!month)
        {
            month = atoi(token);
            token = strtok(NULL, "-");
            continue;
        }
        if (!day)
        {
            day = atoi(token);
            token = strtok(NULL, "-");
            continue;
        }
    }
    if (!( year >= 2009 ))
    {
        std::cout << "\033[31m\033[1mBitcoin not published yet 😢\033[0m" << std::endl;
        return false;
    }
    if (!(month >= 1 && month <= 12))
        return false;
    if (!(day >= 1 && day <= 31))
        return false;
    if ((month == 2) && ((year%400 == 0) || ((year%100 != 0)&&(year%4 == 0))))
    {
        if (day == 30 || day == 31)
            return (false);
    }
    else if (month == 2)
    {
        if (day == 29 || day == 30 || day == 31)
            return (false);
    }
    if (!this->database[date_tmp].empty())
    {
        this->factor = atof(this->database[date_tmp].c_str());
        return true;
    }
    else
    {
        std::map<std::string, std::string>::iterator low;
        low = this->database.lower_bound(date_tmp);

        if (low != this->database.end())
        {
            low--;
            this->factor = atof(this->database[low->first].c_str());
            std::cout << low->first << " "<< low->second << " " << this->factor << std::endl;
        }
        else
            this->factor = 0;
        return true;
       
    }
    return false;
}
BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(std::string path_data_base)
{
    std::ifstream infile; 
    std::string line;
    const char    *ps;
    int           pst;
    this->ivalue = this->fvalue = -1;
    infile.open(path_data_base);
    if (!infile.is_open())
        throw BitcoinExchange::ERROR_DATA();
    while (std::getline(infile, line))
    {
        if (line.empty() || !std::strrchr(line.c_str(), ','))
            continue;
        ps = std::strrchr(line.c_str(), ',');
        pst = ps - line.c_str();
        this->database[line.substr(0, pst)] = line.substr(pst + 1, line.size() - ( pst + 1));
    }
    if (this->database.empty())
        throw BitcoinExchange::EMPTY_DATA();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& B)
{
    *this = B;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& B)
{
    this->database = B.database;
    return (*this);
}

const char *BitcoinExchange::ERROR_DATA::what() const throw()
{
    return ("\033[31m\033[1mcan't Open databese\033[0m");
}

const char *BitcoinExchange::EMPTY_DATA::what() const throw()
{
    return ("\033[31m\033[1mEmpty databese\033[0m");
}

bool BitcoinExchange::check_line(std::string line)
{
    const char    *ps;
    int           pst;
    ps = std::strrchr(line.c_str(), '|');
    if (!ps)
    {
        std::cerr << "Error: Format invalid =>" << line << std::endl;
        return (false);
    }
    pst = ps - line.c_str();
    if (line[pst - 1] != ' ' || line[pst + 1] != ' ')
    {
        std::cerr << "Error: Format invalid =>" << line << std::endl;
        return (false);
    }  
    this->date = line.substr(0, pst - 1);
    if (!this->check_date(this->date))
    {
        std::cerr << "Error: Format invalid =>" << line << std::endl;
        return (false);
    }
    this->value = line.substr(pst + 2, line.size() - ( pst + 1));
    if (this->value.front() == '-')
    {
        std::cerr << "Error: not a positive number" << std::endl;
        return (false);
    }
    size_t found = this->value.find('.');
    if (found != std::string::npos)
    {
        this->fvalue = atof((char *)this->value.c_str());
        if (this->fvalue > 1000)
        {
            std::cerr << "Error: too large a number "<< std::endl;
            return (false);
        }
        this->factor *= this->fvalue;
    }
    else
    {
        this->ivalue = atoi((char *)this->value.c_str());
        if (this->ivalue > 1000 || this->ivalue < 0)
        {
            std::cerr << "Error: too large a number "<< std::endl;
            return (false);
        }
        this->factor *= this->ivalue;
    }
    return (true);
}

void BitcoinExchange::handleBitcoinExchange(std::ifstream &infile)
{
    std::string line;
    int frst = 0;
    while(std::getline(infile, line))
    {
        if (!frst || line.empty())
        {
            if (!line.empty()){
                const char    *ps;
                int           pst;
                ps = std::strrchr(line.c_str(), '|');
                if (!ps)
                {
                    std::cerr << "Error: Format invalid =>" << line << std::endl;
                    return ;
                }
                pst = ps - line.c_str();
                if (line[pst - 1] != ' ' || line[pst + 1] != ' ')
                {
                    std::cerr << "Error: Format invalid =>" << line << std::endl;
                    return ;
                }
            }
            frst = 1;
            continue;
        }
        if (!this->check_line(line))
            continue;
        std::cout << this->date << " => "<< this->value << " = " << this->factor<< std::endl; 
    }
}

BitcoinExchange::~BitcoinExchange()
{
    
}