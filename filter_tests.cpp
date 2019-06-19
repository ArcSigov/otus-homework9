#define BOOST_TEST_MODULE ip_test_module

#include "filters.h"


#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filtration_test_suite)

//Тест проверки фильтров (по умолчанию используется эталлоный ip! на выходе из теста ip должен совпадать с эталоном)

BOOST_AUTO_TEST_CASE(filter_bytes) {
    
    ip_data ip_task = {1 , 0 , 234, 8};
    ip_data_pool.push_back(ip_task);
    

    auto ip = filter(1,0,234,8);
    BOOST_CHECK(ip == ip_data_pool);
    ip = filter(1,0,234);
    BOOST_CHECK(ip == ip_data_pool);
    ip = filter(1,0);
    BOOST_CHECK(ip == ip_data_pool);
    ip = filter(1);
    BOOST_CHECK(ip == ip_data_pool);

    ip_data_pool.clear();
    
}

BOOST_AUTO_TEST_CASE(filter_any_byte)
{
    ip_data ip   = {45 ,46,47,48};
    ip_data_pool.push_back(ip);

    auto ip_any = filter_any(45);
    BOOST_CHECK(ip_any == ip_data_pool);
     ip_any = filter_any(46);
    BOOST_CHECK(ip_any == ip_data_pool);
    ip_any = filter_any(47);
    BOOST_CHECK(ip_any == ip_data_pool);
    ip_any = filter_any(48);
    BOOST_CHECK(ip_any == ip_data_pool);

}

BOOST_AUTO_TEST_CASE(throw_test)
{

    BOOST_CHECK_THROW(filter(1,2,3,4,5,6),std::bad_alloc);

}
BOOST_AUTO_TEST_SUITE_END();