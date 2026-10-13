cmake_minimum_required(VERSION 3.25)
project(beast2_unknown_method LANGUAGES CXX)
include(FetchContent)

set(BUILD_TESTING OFF)
# Build JSON and URL; Boost resolves their header-library dependencies.
set(BOOST_INCLUDE_LIBRARIES json url)
FetchContent_Declare(boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.91.0-1/boost-1.91.0-1-cmake.tar.xz)
FetchContent_MakeAvailable(boost)

macro(fetch name revision)
    FetchContent_Declare(${name}
        URL https://github.com/cppalliance/${name}/archive/${revision}.tar.gz
        ${ARGN})
    FetchContent_MakeAvailable(${name})
endmacro()
fetch(capy f764adc5b3e211558a88311feae79313e3d6f17c)
fetch(http 0c854fc2790968cdf3f117a47b4b90d6a3a1300e)
# Populate Beast2 without its full server build (which requires Corosio/TLS).
fetch(beast2 4c3261053a18a1464c4c2b63b6cf67d73a30b3ff
    SOURCE_SUBDIR unused)

# Compile the original session loop directly, without copying or patching it.
add_executable(repro main.cpp ${beast2_SOURCE_DIR}/src/http_worker.cpp)
target_compile_features(repro PRIVATE cxx_std_20)
target_compile_definitions(repro PRIVATE BOOST_BEAST2_NO_LIB)
target_include_directories(repro PRIVATE ${beast2_SOURCE_DIR}/include)
target_link_libraries(repro PRIVATE Boost::http)
