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

auto filter = [](ip_data& cur)
{
    return (cur[0] == 46 && cur[1] == 70);
};

auto filter_any = [](ip_data& cur)
{
    return ranges::any_of(cur,[](int i){return i == 46;});
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

int main()
{
    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            auto splitted  = ranges::action::split(line, ranges::view::c_str("\t"));
            ip_pool.push_back(ranges::action::split(splitted[0], ranges::view::c_str(".")));
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
        
        ranges::sort(ip_data_pool,std::greater<>());
        ranges::for_each(ip_data_pool,print);
        ranges::for_each(ip_data_pool| ranges::view::filter(filter),print);
        ranges::for_each(ip_data_pool| ranges::view::filter(filter_any),print);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
   return 0;
}