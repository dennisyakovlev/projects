cmake_minimum_required(VERSION 3.20)

set(exe obj)
set(add_libs # all the libraries which to compile to
    test
    test_two
)

project(proj)

add_executable(${exe} main.cpp)

target_include_directories(${exe} PRIVATE libs)
foreach(lib IN LISTS add_libs)
    add_subdirectory(libs/${lib})
    target_link_libraries(${exe} ${lib})
endforeach()
