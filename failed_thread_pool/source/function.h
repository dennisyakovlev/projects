#pragma once
#include "global.h"
#include <tuple>

_POOL_START

template<typename>
class _F;

template<typename Ret, typename... Args>
class _F<Ret(Args...)> {
public:
    using ret_t = Ret;
    using args_t = std::tuple<Args...>;
};

template<typename _Func, typename... Args>
class Function {
public:
    using ret_t = typename _F<std::remove_pointer_t<_Func>>::ret_t;
    using args_t = std::tuple<Args...>;

    Function(_Func _f, Args... args) :
        _M__f{ _f }, _M_args{args...} {}

    auto call() { // decltype the auto?
        return std::apply(_M__f, _M_args);
    }

private:
    _Func _M__f;
    args_t _M_args;
};

/*  Create a function.
*/
template<typename _Func, typename... Args>
constexpr auto make_function(_Func _f, Args&&... args) {
    return Function<_Func, Args...>{ _f, std::forward<Args>(args)... };
};

/*  Make function pool.

    Can only be called once. All function to be added must be 
    added in single call.
*/
template<typename... Args>
constexpr auto make_function_pool(Args&&... funcs) {
    return std::make_tuple(std::forward<Args>(funcs)...);
}

_POOL_END