
#include <range/v3/all.hpp>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "filters.h"



using ip_pool_strings  = std::vector<std::vector<std::string>>;

void ip_log(){};
template<typename T, typename ... Args>
auto ip_log(T t, Args ... args)
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
            auto splitted  = ranges::action::split(line, ranges::view::c_str("\t"));
            ip_pool.push_back(ranges::action::split(splitted[0], ranges::view::c_str(".")));
        }

        //  auto data = ranges::view::transform(ip_pool,[](std::vector<std::string>& cur)
        //                          {
                                     
        //                             for (auto& it: cur )
        //                             {
        //                                 ip.push_back(std::stoi(it));
        //                             }
        //                             return ip;
        //                          });
        // //  std::cout << data->first << std::endl;
         

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
        ranges::sort(ip_data_pool,std::greater<>());
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
         for (auto it:ip_data_pool)
         {
             auto i  = ranges::any_of(it,[](int i){ return i == 46;});
             if (i)
             {
               for (auto it1 = it.cbegin();it1 != it.cend();++it1)
               {
                   if (it1 != it.cbegin())
                   {
                       std::cout << ".";
                   }
                   std::cout << *it1;
               }
               std::cout<< std::endl;
             }
         }
         
         ip_log(ip);
         ip.clear();

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
   return 0;
}