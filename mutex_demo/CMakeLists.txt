cmake_minimum_required(VERSION 3.23.1)

set(CMAKE_BUILD_TYPE Debug) # debug build

IF(CMAKE_COMPILER_IS_GNUCC) # gaurentee no optimizations occur
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

set(CMAKE_CXX_STANDARD 17) # set standard

project(proj) # do NOT change

add_executable(${PROJECT_NAME} main.cpp)

find_package(Threads) # find default thread package
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) # link to the thread library
