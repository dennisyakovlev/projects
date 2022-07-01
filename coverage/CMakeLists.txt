# original ideas was to have cmake file which could generate
#   code coverage and executables using json or command line
#   flags.
# to be honest I don't care enough to figure out how to get
#   coverage working with cmake, doing some basic things
#   and the .gcno files weren't generating.

cmake_minimum_required(VERSION 3.20)

project(main_proj)

# keys in json file
#   everything depends on naming on these keys
# key names are used as list variable names
#   values stored in lists are the associated targets
set(JSON_KEYS
    target
    coverage
)
# flags, so that can use either json or command line
# naming of flags will be used by
#       changing to lower case, splitting by _
#       using first to access created lists
#       using second to add variables to lists
set(COMMAND_LINE_ARGS
    TARGET_MAIN
    TARGET_TEST
    COVERAGE_MAIN
    COVERAGE_TEST
)
# whether to use json file
set(USE_JSON 0)

# create all variable lists, these lists will be used to determine
#   which logic to run
# lists will have same values (depending on given) whether using
#   flags or json
foreach(KEY IN LISTS ${JSON_KEYS})
    set(${KEY} "")
endforeach()

# one function per target

# function for adding executable for main project
function(main)
    message(STATUS "building target main")

    add_executable(main_exe main.cpp)
    target_link_libraries(main_exe algo)
endfunction()

# function for adding executable for tests 
function(test)
    message(STATUS "building target test")

    add_subdirectory(tests)
endfunction()

# check for any command line args, if one exists then use those
#   if none exist, use json file
foreach(COMMAND_ARG IN LISTS COMMAND_LINE_ARGS)
    message(CHECK_START "look for arg " ${COMMAND_ARG})

    # check if command arg given
    if(DEFINED ${COMMAND_ARG})
        message(CHECK_PASS "found")

        set(USE_JSON 1)
        # modify command arg name to be able to have same logic
        #   as with json case
        string(TOLOWER ${COMMAND_ARG} COMMAND_ARG)
        string(REPLACE "_" " " COMMARD_LIS ${COMMAND_ARG})
        separate_arguments(COMMARD_LIS)
        list(GET COMMAND_LIS 0 JSON_KEY)
        list(GET COMMAND_LIS 1 TARGET)

        list(APPEND ${JSON_KEY} ${TARGET}) # append to correct list target
    else()
        message(CHECK_FAIL "not found")
    endif()
endforeach()

message(CHECK_START "given args?")
if (${USE_JSON} EQUAL 1)
    message(CHECK_PASS "yes")
else()
    message(CHECK_PASS "no, use json")
    message(CHECK_START "givenon file?")
    
    if (DEFINED JSON_PATH)
        message(CHECK_PASS "yes, use" ${JSON_PATH})
        list(APPEND CMAKE_MESSAGE_INDENT "  ")

        file(READ ${JSON_PATH} JSON)
        foreach(JSON_KEY IN LISTS JSON_KEYS) # serach for json keys is file
            message(CHECK_START "look for \"" ${JSON_KEY} "\"")
            
            # read json key, value assumed to be list
            string(JSON LIS ERROR_VARIABLE ERR GET ${JSON} ${JSON_KEY})
            if (${ERR} STREQUAL "NOTFOUND") # found json key
                message(CHECK_PASS "found")
    
                string(JSON LEN LENGTH ${LIS})
                if (NOT ${LEN} EQUAL 0) # account for empty list 
                    math(EXPR END "${LEN} - 1") # RANGE is inclusive 
                    foreach(INDEX RANGE 0 ${END})
                        string(JSON TARGET GET ${LIS} ${INDEX})
    
                        list(APPEND ${JSON_KEY} ${TARGET}) # append to correct list
                    endforeach()            
                endif()
            else()
                message(CHECK_FAIL "not found or wrong format")
            endif()
        endforeach()
    else()
        message(CHECK_FAIL "no")
        # don't have default behaviour of how to build
        message(FATAL_ERROR "must gives args or json path")
    endif()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
endif()

# given json path, parse json file
# once used once, will automatically use even if not given
#   unitl command line args given

# NEED TO check if any in COMMAND_LINE_ARGS exist, if so then dont use JSON_PATH
# if(DEFINED JSON_PATH)
#     # message(CHECK_PASS "yes, using " ${JSON_PATH})
#     # list(APPEND CMAKE_MESSAGE_INDENT "  ")

#     file(READ ${JSON_PATH} JSON)
#     foreach(JSON_KEY IN LISTS JSON_KEYS) # serach for json keys is file
#         message(CHECK_START "look for \"" ${JSON_KEY} "\"")
        
#         # read json key, value assumed to be list
#         string(JSON LIS ERROR_VARIABLE ERR GET ${JSON} ${JSON_KEY})
#         if (${ERR} STREQUAL "NOTFOUND") # found json key
#             message(CHECK_PASS "found")

#             string(JSON LEN LENGTH ${LIS})
#             if (NOT ${LEN} EQUAL 0) # account for empty list 
#                 math(EXPR END "${LEN} - 1") # RANGE is inclusive 
#                 foreach(INDEX RANGE 0 ${END})
#                     string(JSON TARGET GET ${LIS} ${INDEX})

#                     list(APPEND ${JSON_KEY} ${TARGET}) # append to correct list
#                 endforeach()            
#             endif()
#         else()
#             message(CHECK_FAIL "not found or wrong format")
#         endif()
#     endforeach()
#     # list(POP_BACK CMAKE_MESSAGE_INDENT)

# else()
#     # need to do this first, and always, then if all flags come back as undefined,
#     #   use json
#     # message(CHECK_FAIL "not given, use flags")
#     # list(APPEND CMAKE_MESSAGE_INDENT "  ")


    
#     # list(POP_BACK CMAKE_MESSAGE_INDENT)
# endif()

add_subdirectory(lib) # always add library since both executable link to it

foreach(FLAG IN LISTS target)
    cmake_language(CALL ${FLAG})
endforeach()