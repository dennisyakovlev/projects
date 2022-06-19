cmake_minimum_required(VERSION 3.23)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(target proj)
set(src source)

string(ASCII 27 Esc)
set(bold_cyan    "${Esc}[1;36m")

project(project LANGUAGES CXX) # do NOT change

if(debug EQUAL 1)
    message("${bold_cyan}Compiling with debug ON")
    add_compile_definitions(DEBUG=1)
    unset(debug CACHE) # unset cache variable, dont want to default to using debug
endif()

add_executable(${target} main.cpp)

add_subdirectory(source)
target_include_directories(${target} PRIVATE ${src})
target_link_directories(${target} PRIVATE ${src})
set_target_properties(thread_pool PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${target} thread_pool)

find_package(Threads)
target_link_libraries(${target} ${CMAKE_THREAD_LIBS_INIT})