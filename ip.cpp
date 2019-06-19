#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "filters.h"

#include <range/v3/all.hpp>

using ip_pool_strings  = std::vector<std::vector<std::string>>;


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void ip_log(){};
template<typename T, typename ... Args>
decltype(auto) ip_log(T t, Args ... args)
{
    ip_pool_data printable = t;

    for (auto pr = printable.cbegin(); pr!=printable.cend();pr++) 
    {
        for (auto it1 = pr->cbegin(); it1 != pr->cend();++it1)
        {
            if (it1 != pr->cbegin())
            {
                std::cout << ".";
            }
            std::cout<<*it1;
        }
        std::cout<< std::endl;

    }
    ip_log(args...);

}

int main()
{
    try
    {
        ip_pool_strings ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        for (auto it = ip_pool.begin(); it != ip_pool.end();it++)
        {
            
            for (auto it1 = it->begin(); it1 != it->end();it1++)
            {
                ip.push_back(std::stoi(*it1));
            }
            ip_data_pool.push_back(ip);
            ip.clear();
        }
        
        // TODO reverse lexicographically sort
        //std::sort(ip_data_pool.begin(),ip_data_pool.end(),std::greater<>());
        ranges::sort_heap(ip_data_pool);
        //print sorted ip vector
        ip_log(ip_data_pool);
        //print filtered ip vector with first byte 1
         auto ip = filter(1);
         ip_log(ip);
         ip.clear();
        //print filtered ip vector with first byte 46, second 70
         ip = filter(46,70);
         ip_log(ip);
        //print filtered ip vector with any byte 46
         ip = filter_any(46);
         ip_log(ip);
         ip.clear();

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
   return 0;
}