#!/bin/sh
# d227b0e036544d3cf71853c8dfc8c1c0
#   above is somewhat safe method to verify the path to manual.sh
#   is correct, but will give error

# manually do steps without makefile

# if planning on running manual.sh from not within the folder it
#   is in, must set below to be aboslute path to manual.sh
this_file_path=$(pwd)
# verify the above variable is correct
# need this_file_path to be the path of this file so that
#   the relative directories work.
# pwd will only be correct if the file is run from within
#   the directory it is located
echo "verify $this_file_path/manual.sh is correct"
if [ ! -f "$this_file_path/manual.sh" ]; then
    >2& echo "cannot find this file"
    exit 1
fi

# check 2nd line of given manual.sh file if it exists
#   to make sure its this given file
# for example, say this file being being run in some other 
#   directory which contains a manual.sh, above check passes,
#   but not this one 
echo "$(sed '2q;d' ${this_file_path}/manual.sh)" | grep -q d227b0e036544d3cf71853c8dfc8c1c0
if [ "$?" -eq 1 ]; then # use sed 
    >2& echo "found file matching file, but is not this file"
    exit 1
fi

# use "coverage" to be able to generate coverage
#   use -O0 so that optimization don't interfere 
coverage="-O0 --coverage"

# build directory
mkdir -p build
cd build
# compile into object files
g++ $coverage -c "${this_file_path}"/lib/src/*.cpp -I"${this_file_path}"/lib/include

#  -- start --
# steps for static lib
g++ -c $coverage -o libmy_algo.a *.o
ar rvs libmy_algo.a *.o
#  --  end  --

#  -- start -- 
# steps for shared library
# make into shared library
# g++ $coverage -shared -o libmy_algo.so *.o

# add to dynamic linker search path, assuming /usr/lib is in the path
#   then apply changes to linker cache
# echo "admin_password" | sudo -S cp libmy_algo.so /usr/lib
# echo "admin_password" | sudo -S ldconfig 
#  --  end  -- 

# clean
rm *.o

# in tests
#   - compile source files (moved libmy_algo.a into here)
#   - include algo headers, tell static linker where to find my_algo and gtest, tell dynamic linker to
#       link against my_algo, gtest, pthread, add coverage flags
#   - generates .gcno files, to generate .gcda files must run a.out
# g++ "${this_file_path}"/tests/*.cpp -O0 -I"${this_file_path}"/lib/include -L"${this_file_path}"/build -L/usr/lib/gtest -lmy_algo -lgtest -pthread -fprofile-arcs -ftest-coverage
g++ $coverage \
    "${this_file_path}"/tests/*.cpp \
    -I"${this_file_path}"/lib/include \
    -L"${this_file_path}"/build \
    -L/usr/lib/gtest \
    -lmy_algo \
    -lgtest \
    -pthread
unbuffer ./a.out > ../test_res.gtest

# generate lcov file
lcov -c -d . -o result.info
# remove all tests with /usr in their directory
# side effect is all paths get truncated to top most dir
#   Note: they always get truncated, just with /usr, most base dir is /
#   ie /home/me/proj/lib/src -> lib/src
lcov -r result.info "/usr*" -o result.info
mkdir html
# generate html files
genhtml -o html result.info

xdg-open html/index.html