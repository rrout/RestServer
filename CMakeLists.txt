cmake_minimum_required(VERSION 3.10)

# Project name and version
project(restserver VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Alternatively, you can specify the build type on the command line
# when running CMake:
# cmake -DCMAKE_BUILD_TYPE=Debug ..

# If you want to specify the optimization level and debug symbols separately
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

set(CMAKE_VERBOSE_MAKEFILE ON)


set(OPENSSL_ROOT_DIR /usr/lib/ssl)
set(OPENSSL_INCLUDE_DIR /usr/include/openssl)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)


# Specify the include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Find Boost libraries
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost libraries not found!")
endif()

# Add the executable
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(restserver ${SOURCES})

target_include_directories(restserver PRIVATE ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
# Link Boost libraries
target_link_libraries(restserver ${Boost_LIBRARIES} pthread rt boost_system boost_thread boost_chrono OpenSSL::SSL OpenSSL::Crypto)

