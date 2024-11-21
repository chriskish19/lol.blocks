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


