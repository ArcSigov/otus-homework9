#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <range/v3/all.hpp>

using ip_pool_strings  = std::vector<std::vector<std::string>>;
using ip_data = std::vector<int>;
using ip_pool_data = std::vector<ip_data>;

ip_data         ip;
ip_pool_data    ip_data_pool;
ip_pool_strings ip_pool;

auto filter1 = [](ip_data& cur)
{
    return (cur[0] == 1);
};

auto filter4670 = [](ip_data& cur)
{
    return (cur[0] == 46 && cur[1] == 70);
};

auto filter_any = [](ip_data& cur)
{
    return ranges::any_of(cur,[](int& i){return i == 46;});
};

auto print = [](ip_data& cur)
{
    for (auto it = cur.begin(); it != cur.end() ; it++)
    {
        if (it !=cur.begin())
            std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl;
};


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

int main()
{
    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
             auto v = split(line, '\t');
             ip_pool.emplace_back(split(v.at(0), '.'));
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
        ranges::for_each(ip_data_pool,print);
        ranges::for_each(ip_data_pool| ranges::view::filter(filter1),print);
        ranges::for_each(ip_data_pool| ranges::view::filter(filter4670),print);
        ranges::for_each(ip_data_pool| ranges::view::filter(filter_any),print);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
   return 0; 
}