set(lib private)

add_library(${lib} OBJECT)
set_target_properties(${lib} PROPERTIES LINKER_LANGUAGE CXX)
target_sources(${lib} 
    PRIVATE
    items.h
)