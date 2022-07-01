# Code Coverage with Gtest
Learn how to use GNU's code coverage tools of `gcov` and `lcov` combined with `gtest`.

## High Level Goal
Attempt to integrate many items into one project while using as few "question and answer" resources as possible. Use only documentation provided by the given items.  
Items completely new to me were `gtest`, `gcov`, and `lcov`. I knew cmake basics.

## Result
### Functionality
A mostly working as intended project. Only thing not working is adding coverage to cmake file.  
A flaw in the top-level cmake design is adding ability to choose which tergets recieve code coverage. Better idea would be make use of different build types and add flags as needed.

### Goal Achieval
Achieved quite well. Only esed QA resources enough times to be counted on one hand. The documentation combined with basic self testing is capable of demonstrating a completely new technology enough to have a basic user understanding of it.

## Documentation
### Usage
To build, create build directory in top-level of project and run `cmake` from inside said build directory. If JSON is updated, must rerun `cmake` configuration.  

Can use either camke command line flags with `-D`, or json file.  

If a JSON file is given, build automatically defaults to using the file until. Only when flags are given, will they be used as they are not saved.

### JSON
To use JSON file, use `-D` to `cmake` setting vairable `JSON_PATH=`*rel_or_abs_path*   
JSON file has format of 
```json
{
    "target": ["main", "test"],
    "coverage": ["main", "test"]
}
```
Where  
&nbsp;&nbsp;&nbsp;&nbsp;`target` defines which executables should be built  
&nbsp;&nbsp;&nbsp;&nbsp;`coverage` defines which executables will recieve coverage  
&nbsp;&nbsp;&nbsp;&nbsp;`test, main` defines executables

### Cmake Flags
Use with `-D` to `cmake`.  
Set the value to anything, so long as the flag is given it will be valid.
```
    TARGET_MAIN    - build main executable "main_exe" 
    TARGET_TEST    - build test executable "tests/tout"
    COVERAGE_MAIN  - add coverage to "main_exe"
    COVERAGE_TEST  - add coverage to "tests/tout" 
```