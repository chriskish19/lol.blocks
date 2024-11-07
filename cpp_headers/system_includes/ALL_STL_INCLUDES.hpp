#pragma once


#if defined(_MSVC_LANG)
#define USING_MSVC_CPP_LANG_VERSION _MSVC_LANG
#define GENERAL_MACRO_CPP_LANG_VERSION _MSVC_LANG
#elif defined(__clang__)
#define USING_CLANG_CPP_LANG_VERSION __cplusplus
#define GENERAL_MACRO_CPP_LANG_VERSION __cplusplus
#elif defined(__GNUC__)
#define USING_GCC_CPP_LANG_VERSION __cplusplus
#define GENERAL_MACRO_CPP_LANG_VERSION __cplusplus
#else
#define COMPILER_NOT_SUPPORTED 1
#error "ALL_STL_INCLUDES.hpp only supports 3 compiler vendors MSVC, GCC and Clang"
#endif

#if ((GENERAL_MACRO_CPP_LANG_VERSION < 201402L) || (GENERAL_MACRO_CPP_LANG_VERSION > 202302L))
#define CPP_LANG_VERSION_NOT_SUPPORTED 1
#error "ALL_STL_INCLUDES.hpp only supports c++ 14 to 23"
#endif


#if GENERAL_MACRO_CPP_LANG_VERSION == 201402L
// C++14
#define CPP_14 2014
#elif GENERAL_MACRO_CPP_LANG_VERSION == 201703L
// C++17
#define CPP_17 2017
#elif GENERAL_MACRO_CPP_LANG_VERSION == 202002L
// C++20
#define CPP_20 2020
#elif GENERAL_MACRO_CPP_LANG_VERSION == 202302L
// C++23
#define CPP_23 2023
#endif


#if defined(CPP_14)
// CPP 14 Support and below
#include <cfloat>
#include <climits>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <typeindex>
#include <typeinfo>
#include <version>
#include <cassert>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <memory>
#include <scoped_allocator>
#include <ratio>
#include <type_traits>
#include <bitset>
#include <functional>
#include <tuple>
#include <utility>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <string>
#include <cctype>
#include <clocale>
#include <codecvt>
#include <cuchar>
#include <cwctype>
#include <locale>
#include <regex>
#include <cfenv>
#include <cmath>
#include <complex>
#include <random>
#include <valarray>
#include <chrono>
#include <ctime>
#include <cinttypes>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <strstream>
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <thread>

#elif defined(CPP_17)
// CPP 17 Support and below
#include <execution>
#include <cfloat>
#include <climits>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <typeindex>
#include <typeinfo>
#include <version>
#include <cassert>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <memory>
#include <memory_resource>
#include <scoped_allocator>
#include <ratio>
#include <type_traits>
#include <any>
#include <bitset>
#include <functional>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <string>
#include <string_view>
#include <cctype>
#include <charconv>
#include <clocale>
#include <codecvt>
#include <cuchar>
#include <cwctype>
#include <format>
#include <locale>
#include <regex>
#include <cfenv>
#include <cmath>
#include <complex>
#include <numbers>
#include <random>
#include <valarray>
#include <chrono>
#include <ctime>
#include <cinttypes>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <strstream>
#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <thread>

#elif defined(CPP_20)
// CPP 20 Support and below
#include <execution>
#include <cfloat>
#include <climits>
#include <compare>
#include <coroutine>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <source_location>
#include <typeindex>
#include <typeinfo>
#include <version>
#include <concepts>
#include <cassert>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <memory>
#include <memory_resource>
#include <scoped_allocator>
#include <ratio>
#include <type_traits>
#include <any>
#include <bit>
#include <bitset>
#include <functional>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <string>
#include <string_view>
#include <cctype>
#include <charconv>
#include <clocale>
#include <codecvt>
#include <cuchar>
#include <cwctype>
#include <format>
#include <locale>
#include <regex>
#include <cfenv>
#include <cmath>
#include <complex>
#include <numbers>
#include <random>
#include <valarray>
#include <chrono>
#include <ctime>
#include <cinttypes>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <strstream>
#include <syncstream>
#include <atomic>
#include <barrier>
#include <condition_variable>
#include <future>
#include <latch>
#include <mutex>
#include <semaphore>
#include <shared_mutex>
#include <stop_token>
#include <thread>

#elif defined(CPP_23)
// CPP 23 Support and below
#include <execution>
#include <cfloat>
#include <climits>
#include <compare>
#include <coroutine>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <source_location>
#include <stdfloat>
#include <typeindex>
#include <typeinfo>
#include <version>
#include <concepts>
#include <cassert>
#include <cerrno>
#include <stacktrace>
#include <stdexcept>
#include <system_error>
#include <memory>
#include <memory_resource>
#include <scoped_allocator>
#include <ratio>
#include <type_traits>
#include <any>
#include <bit>
#include <bitset>
#include <functional>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <mdspan>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <string>
#include <string_view>
#include <cctype>
#include <charconv>
#include <clocale>
#include <codecvt>
#include <cuchar>
#include <cwctype>
#include <format>
#include <locale>
#include <regex>
#include <cfenv>
#include <cmath>
#include <complex>
#include <numbers>
#include <random>
#include <valarray>
#include <chrono>
#include <ctime>
#include <cinttypes>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <print>
#include <spanstream>
#include <sstream>
#include <streambuf>
#include <strstream>
#include <syncstream>
#include <atomic>
#include <barrier>
#include <condition_variable>
#include <future>
#include <latch>
#include <mutex>
#include <semaphore>
#include <shared_mutex>
#include <stop_token>
#include <thread>

#endif