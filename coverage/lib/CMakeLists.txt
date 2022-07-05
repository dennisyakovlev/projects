# own library for some algorithms from leetcode
set(include
    algo_1.h
    algo_2.h
)
set(source
    algo_1.cpp
    algo_2.cpp
)
list(TRANSFORM include PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/include/algorithm/)
list(TRANSFORM source PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_library(algo STATIC
    ${include}
    ${source}    
)
# alias project as subproject of the main project, named "main_proj"
#   allows for usage is sub directories since non included targets
#   are always global
add_library(main_proj::algo ALIAS algo)

# adds ability to include <algorithm/FILE.h>
#   to every executable which links to algo
target_include_directories(algo PUBLIC include) 