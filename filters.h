#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>


using ip_data = std::vector<int>;
using ip_pool_data = std::vector<ip_data>;

ip_data ip;
ip_pool_data ip_data_pool;


template <typename ... Args> 
auto filter( Args ... args)
 {
    if (sizeof ... (Args)> 4)
        throw std::bad_alloc();

    ip_data vect_ip_tasks = {(args)...};

    ip_pool_data filtered_pool;
 
    for (auto it = ip_data_pool.cbegin(); it != ip_data_pool.cend();it++)
    {
        auto s_vector = *it;
        auto counter = 0;
        for (unsigned long i = 0; i < (sizeof...(Args));  i++)
        {
            if (s_vector[i] == vect_ip_tasks[i])
                counter++;
        }
        if (counter == sizeof ...(Args)) filtered_pool.push_back(*it);
    }
    return filtered_pool;
}

auto filter_any(int value)
{
    ip_pool_data filtered_pool;
    for (auto it = ip_data_pool.cbegin(); it !=ip_data_pool.cend();it++)
    {
        auto finded = std::find(it->begin(),it->end(),value);
        if (finded != it->end())
        {
            filtered_pool.push_back(*it);
        }    
    }
    return filtered_pool;
} 
