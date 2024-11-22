// NOTE: dont use pragma once or any header guard for macro header files
// this header is used to prevent recurrsive #includes and any macro conflicts...
// it defines the header macros for certain header files.

// avoid conflicts with stl...
#if defined(min)
#undef min
#endif
#if defined(max)
#undef max
#endif

// control header includes throughout the whole project here by defining the include name
// example: #define PUBLIC_PCH_HEADER_HPP . this would turn off all header includes of the public pch header file


