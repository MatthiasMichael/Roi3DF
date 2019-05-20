#pragma once

#include <type_traits>

#define CHECK_MEMBER( TAG, NAME )                                          \
template<typename, typename T>                                             \
struct has_member_##TAG                                                    \
{                                                                          \
    static_assert(                                                         \
        std::integral_constant<T, false>::value,                           \
        "Second template parameter needs to be of function type.");        \
};                                                                         \
                                                                           \
template<typename C, typename Ret, typename... Args>                       \
struct has_member_##TAG<C, Ret(Args...)>                                   \
{                                                                          \
private:                                                                   \
                                                                           \
    template<typename T, std::enable_if_t<                                 \
        std::is_convertible                                                \
        <                                                                  \
            decltype(std::declval<T>().##NAME (std::declval<Args>()...)),  \
            Ret                                                            \
        >::value                                                           \
    > * = nullptr >                                                        \
    static constexpr std::true_type check(nullptr_t);                      \
                                                                           \
    template<typename>                                                     \
    static constexpr std::false_type check(...);                           \
                                                                           \
public:                                                                    \
    using type = decltype(check<C>(nullptr));                              \
    static constexpr bool value = type::value;                             \
};


#define CHECK_FUNCTION( TAG, NAME )                                        \
template<typename T>                                                       \
struct has_function_##TAG {                                                \
    static_assert(                                                         \
        std::integral_constant<T, false>::value,                           \
        "Template parameter needs to be of function type.");               \
};                                                                         \
                                                                           \
template<typename Ret, typename... Args>                                   \
struct has_function_##TAG<Ret(Args...)> {                                  \
private:                                                                   \
    template<typename... A, std::enable_if_t                               \
    <                                                                      \
        std::is_convertible                                                \
        <                                                                  \
            decltype(NAME(std::declval<A>()...)),                          \
            Ret                                                            \
        >::value                                                           \
    > * = nullptr >                                                        \
    static constexpr std::true_type check(nullptr_t);                      \
                                                                           \
    template<typename...>                                                  \
    static constexpr std::false_type check(...);                           \
                                                                           \
public:                                                                    \
    typedef decltype(check<Args...>(nullptr)) type;                        \
    static constexpr bool value = type::value;                             \
};


// Broken in older versions of MSVC:
// https://developercommunity.visualstudio.com/content/problem/235349/conditionally-compiling-template-operator-overload.html
#define CHECK_OPERATOR( TAG, OP )                                          \
template<typename C, typename Ret, typename Arg>                           \
struct has_operator_##TAG {                                                \
private:                                                                   \
    template<typename L, typename R, std::enable_if_t<                     \
        std::is_convertible                                                \
        <                                                                  \
            decltype(std::declval<L>() OP std::declval<R>()),              \
            Ret                                                            \
        >::value                                                           \
    > * = nullptr >                                                        \
        static constexpr std::true_type check(nullptr_t);                  \
                                                                           \
    template<typename, typename>                                           \
    static constexpr std::false_type check(...);                           \
                                                                           \
public:                                                                    \
    typedef decltype(check<C, Arg>(nullptr)) type;                         \
    static constexpr bool value = type::value;                             \
};