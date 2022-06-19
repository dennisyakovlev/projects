# Thread-Pool
Failed attempt at a user friednly, type safe thread pool.

## High Level Goal
Avoid using `void*` syntax in `thread_start` on start function as it forces a reinterpret cast to access function arguement. Attempt to do so using c++ utilities such as SFINAE, tuple, partial template specialization and a few more related. Would allow for type safe usage of threads.

## Issue
### Intro
A thread pool is a collection of threads which uses data synchoronization mechanisms combined with a data structure to execute specified functions. A function of the signature `void*(*)(void*)` is specified as the start function for a particualr thread. The starting function may then execute functions from the data structure as required.

## The problem
In the starting function, the single `void*` arguement must be `reinterpret_cast`. This forces the programmer to explicitly type out the type conversion to a single known type. That is, functions with arbitray signatures cannot be added to the executation data structure.

## Possible Solutions
Ideas come to mind of using some compile time utilities, pointer manipulatons, and macro hacks to store arbitrary function signatures. These are all achievable, some less adviasable. However, all solutions lead to needing to know the functions signatures within the start function with signature `void*(*)(void*)`. Somehow type information must be transfered into the start function without hardcoding types. As is stands, I do not know how to do this.

## Result
An unifinished poorly made _project_.
