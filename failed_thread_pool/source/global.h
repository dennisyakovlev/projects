#pragma once

#include <cstdio>

#define _POOL thread_pool
#define _POOL_START namespace _POOL {
#define _POOL_END }

/*  _ when start with means pionter
    __ when start with means reference
    _ end with means container

    Prefixing with _M_ means private member variable. Then other rules are applied as above.

    using declations are of form
        NAME_t for type
        NAME__t for pointer type
        _NAME__t for container pointer
*/

#define PTHREAD_MUTEX_INIT(_m, _attr, msg) { \
    if (pthread_mutex_init(_m, _attr) != 0) { \
        std::perror(msg); \
    } \
}

#define PTHREAD_MUTEX_LOCK(_m, msg) { \
    if (pthread_mutex_lock(_m) != 0) { \
        std::perror(msg); \
    } \
}

#define PTHREAD_MUTEX_UNLOCK(_m, msg) { \
    if (pthread_mutex_unlock(_m) != 0) { \
        std::perror(msg); \
    } \
}

#define PTHREAD_CREATE(_t, _attr, _f, _arg, msg) { \
    if (pthread_create(_t, _attr, _f, _arg) != 0) { \
        std::perror(msg); \
    } \
}

#define PTHREAD_JOIN(t, __ret, msg) { \
    if (pthread_join(t, __ret) != 0) { \
        std::perror(msg); \
    } \
}

_POOL_START

/*  Structs to request type of execution.
*/
class async{};
class sync{};

using async_t = async;
using sync_t = sync;
/*  Use own size_t to avoid having dealing with the multiple
    types of it from different places.
*/
using size_t = long;
using usize_t = unsigned long;

_POOL_END