set(lib test_two)
set(lib_private private)

add_subdirectory(${lib_private})

add_library(${lib} OBJECT)
target_sources(${lib} 
    PUBLIC
    test.h
    PRIVATE # must be private
    test.cpp
)

# these must be private because cannot link library into library
#   since "lib_private -> lib -> exe" cannot happen
target_link_libraries(${lib} PRIVATE ${lib_private})
target_include_directories(${lib} PRIVATE ${lib_private})