cmake_minimum_required(VERSION 3.25)
project(beast2_unknown_method LANGUAGES CXX)
include(FetchContent)

set(BUILD_TESTING OFF)
set(BOOST_INCLUDE_LIBRARIES json url system winapi)
set(CMAKE_DISABLE_FIND_PACKAGE_liburing ON)
set(CMAKE_DISABLE_FIND_PACKAGE_WolfSSL ON)
FetchContent_Declare(boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.91.0-1/boost-1.91.0-1-cmake.tar.xz)
FetchContent_MakeAvailable(boost)

function(fetch name revision)
    FetchContent_Declare(${name}
        URL https://github.com/cppalliance/${name}/archive/${revision}.tar.gz)
    FetchContent_MakeAvailable(${name})
endfunction()
fetch(capy f764adc5b3e211558a88311feae79313e3d6f17c)
fetch(corosio 15339147af84a9cc07d641d16acb6665248244db)
fetch(http 0c854fc2790968cdf3f117a47b4b90d6a3a1300e)
fetch(beast2 4c3261053a18a1464c4c2b63b6cf67d73a30b3ff)

add_executable(repro main.cpp)
target_compile_features(repro PRIVATE cxx_std_20)
target_link_libraries(repro PRIVATE Boost::beast2)
