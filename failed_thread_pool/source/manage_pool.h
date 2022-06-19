#pragma once

#include <iostream>
#include <type_traits>
#include "global.h"
#include "context.h"

// #include <queue>
#include <vector>
// #include <pthread.h>

_POOL_START

/*  Begin a thread.

    _i is thread pool id
*/
void* _thread_start(void* _i) { // type trait need instead of reinterpret cast
    // new issue, new to cast it back,
    //  instead just have a global templated Context variable which user sets
    // while (_c->rem().load() > 0) {
    //     if (!_c->order()->empty()) {
    //         PTHREAD_MUTEX_LOCK(_c->m(), "pthread mutex lock")
    //         auto inf = _c->order()->front();
    //         _c->order()->pop_front();
    //         PTHREAD_MUTEX_UNLOCK(_c->m(), "pthread mutex unlock")

    //         --inf._M_n;
    //         _c->rem() -= 1;
    //         inf._M_f(inf._M_arg);

    //         if (inf._M_n != 0) {
    //             PTHREAD_MUTEX_LOCK(_c->m(), "pthread mutex lock")
    //             _c->order()->push_back(inf);
    //             PTHREAD_MUTEX_UNLOCK(_c->m(), "pthread mutex unlock")
    //         }
    //     } else {
    //         nanosleep(_c->timespec(), nullptr);
    //     }
    // }

    // pthread_exit(nullptr);
}

/*  Begin the thread pool. Either synchronously or asynchronously.
*/
template<typename T>
int start_pool(_cnxt_t<T> _c) {
// if debug present check if cnxt is empty empty

    PTHREAD_MUTEX_INIT(_c->m(), nullptr, "pthread mutex init")

    auto nf = _c->num_func();
    for (auto i = 0; i != nf; ++i) {
        pthread_t t;
        PTHREAD_CREATE(&t, nullptr, _thread_start, reinterpret_cast<void*>(_c), "pthread create")
        _c->threads()->push_back(t);
    }

    for (auto iter = _c->threads()->cbegin(); iter != _c->threads()->cend(); ++iter) {
        PTHREAD_JOIN(*iter, nullptr, "pthread join");
    }
    
    return 0;
}

// HOW ARE WE TERMINATING THE POOL?
//  we want to use say signal, but for that need to somehow
//  give this function to the sigaction struct
//      perhaps add to the context class function which takes (singal, action)
//      which will carry out action upon signal. action can be like terminate, pause
//      which will either terminate or pause all threads
//          dont add to context class, make a new manager classs

/*  Terminate the thread pool immedeatly. Either synchronously or asynchronously.
*/
template<typename T>
int stop_pool() {
    return 0;
}

template<>
int stop_pool<sync_t>() {
    return 0;
}

template<>
int stop_pool<async_t>() {
    return 0;
}

_POOL_END