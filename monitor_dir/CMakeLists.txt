cmake_minimum_required(VERSION 3.2)

set(EXE_NAME obj)
set(CMAKE_BUILD_TYPE Debug)
set(LIB_DIR src)

project(proj)

find_package(Threads REQUIRED)

add_subdirectory(${LIB_DIR})

add_executable(${EXE_NAME} main.cpp)

target_include_directories(${EXE_NAME} PRIVATE ${LIB_DIR})
target_link_libraries(${EXE_NAME} monitor)
target_link_libraries(${EXE_NAME} Threads::Threads)
