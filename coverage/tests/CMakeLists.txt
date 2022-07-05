# google tests for testing library

set(EXE_TEST tout)
# simply adding the sources means their tests will be included 
#   when main.cpp runs all tests
set(sources 
    main_tests.cpp
    algo_test_1.cpp
    algo_test_2.cpp
)
set(libs
    gtest
    Threads::Threads
    main_proj::algo
)

add_executable(${EXE_TEST} ${sources})

find_package(Threads REQUIRED)

# my gtest is in /usr/lib/gtest
target_link_directories(${EXE_TEST} PRIVATE /usr/lib/gtest) # let static linker know where gtest is

foreach(lib IN LISTS libs)
    target_link_libraries(${EXE_TEST} ${lib})
endforeach()