#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "filters.h"

#include <range/v3/all.hpp>

using ip_pool_strings  = std::vector<std::vector<std::string>>;
ip_pool_strings ip_pool;

auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto str_start = ranges::begin(str);
    auto stop = ranges::find(str,d);
    while(stop != ranges::end(str))
    {
        r.emplace_back(str_start, stop);

        str_start = ranges::next(stop);
        stop =  ranges::find(str_start,ranges::end(str), d);
    }
    r.emplace_back(str_start,ranges::end(str));
    return r;
}

void ip_log(){};
template<typename T, typename ... Args>
void ip_log(T t, Args ... args)
{
    ip_pool_data printable = t;
    ranges::for_each(printable,[](ip_data& cur)
    {
        for (auto it = ranges::begin(cur); it != ranges::end(cur) ; it++)
        {
            if (it !=ranges::begin(cur))
                std::cout << ".";
            std::cout << *it;
        }
        std::cout << std::endl;
    });
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

        for (auto it:ip_pool)
        {
            auto start = ranges::begin(it);
            while (start != ranges::end(it))
            {
                ip.emplace_back(std::stoi(*start));
                start++;
            }
            ip_data_pool.emplace_back(ip);
            ip.clear();
        }
        ranges::sort(ip_data_pool,std::greater<>());
        ip_log(ip_data_pool,filter(1),filter(46,70),filter_any(46));
      
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
   return 0;
}
