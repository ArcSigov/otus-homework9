cmake_minimum_required(VERSION 3.2)
if ($ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else($ENV{TRAVIS_BUILD_NUMBER}) 
    project(ip_filter VERSION 0.0.1)
endif($ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ip.cpp)

add_executable(test_${PROJECT_NAME} filter_tests.cpp)

set_target_properties(${PROJECT_NAME}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(test_${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_${PROJECT_NAME}
    ${Boost_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)




set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT arcadii_ru@mail.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)

enable_testing()

add_test(filter_bytes     test_${PROJECT_NAME})
add_test(filter_any_byte  test_${PROJECT_NAME})
add_test(throw_test       test_${PROJECT_NAME})
