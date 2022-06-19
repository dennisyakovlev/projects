#pragma once
#include <deque>
#include <atomic>
#include <vector>
#include <functional>
#include <tuple>
#include <pthread.h>
#include <type_traits>
#include <time.h>
#include "global.h"
#include "function.h"

// what we want is a deque of just number which correspond
//  to indicies of the tuple, and which function to extract

_POOL_START

/*  Manages variables for the pool.

    A new context is needed for each pool.
*/
template<typename T> // add storage container type?
class Context {
private:
    using f__t = std::deque<usize_t>;
    using t__t = std::vector<pthread_t>;
    using m_t = pthread_mutex_t;
    using ts_t = struct timespec;

    // should store thread number and index together?
    // that way can kill specific  thread as needed

public:
    using _f__t = f__t*;
    using _t__t = t__t*;
    using _m_t = m_t*;
    using _ts_t = ts_t*;
    using a_t = std::atomic<int>;

    using tupe_t = std::remove_reference_t<T>;

    // T cannot be lvalue reference
    // since want to be able to have rvalue reference
    // template<typename = std::enable_if_t<!std::is_lvalue_reference_v<T>>>
    // Context(T&& tupe) : _M_t_{}, _M_q_{}, _M_nf{ 0 }, _M_m{},
    Context() : _M_t_{}, _M_q_{}, _M_m{}, 
        _M_rem{ 0 }, _M_ts{ 0,25000000 }, _M_tupe{}  {}
    Context(T tupe) : _M_t_{}, _M_q_{}, _M_m{}, 
        _M_rem{ 0 }, _M_ts{ 0,25000000 }, _M_tupe{ tupe }  {} // need special case for move

    inline _m_t m() { return &_M_m; }
    inline _t__t threads() { return &_M_t_;  } // use std address of
    inline _f__t order() { return &_M_q_; } // same here
    inline _ts_t timespec() { return &_M_ts; }
    inline a_t& rem() { return _M_rem; }
    inline size_t num_func() const { return _M_nf; }

private:
    t__t _M_t_; // threads
    f__t _M_q_; // func info container
    m_t _M_m; // mutex
    ts_t _M_ts;
    a_t _M_rem; // number of remaining function calls
                // can also be found at compile time
    static constexpr auto _M_nf = std::tuple_size<T>::value; // number of functions
    tupe_t _M_tupe;
};

template<typename T>
using cnxt_t = Context<T>;

template<typename T>
using _cnxt_t = cnxt_t<T>*;

template <typename T> class Global {
public:    
    static T pVar;

private:    
    Global() {}
    Global(const Global& rhs) {}
    void operator=(const Global& rhs) {}
};

template <typename T> T Global<T>::pVar = T{};

_POOL_END