// This header is the public include header for using the window class

// INFO: When including this header in a cpp file #define INCLUDING_IN_SOURCE above the include statement
// NOTE: Use a macro check and #undef INCLUDING_IN_SOURCE at the end of the cpp source file

// INFO: When including this header in a header file #define INCLUDING_IN_HPP above the include statement
// NOTE: Use a macro check and #undef INCLUDING_IN_HPP at the end of the cpp source file


#ifndef PUBLIC_WINDOW_CLASS_HPP
#define PUBLIC_WINDOW_CLASS_HPP


// macro used when including in a cpp source file.
#ifdef INCLUDING_IN_SOURCE

// include public window class dependencies header
#include "classes/win32_api/window/dependencies/public/public_window_depend.hpp"

// private class header
#include "../private/window_class.hpp"

// INCLUDING_IN_SOURCE
#endif 


// macro used when including in a header file
#ifdef INCLUDING_IN_HPP

// include public window class dependencies header
#include "classes/win32_api/window/dependencies/public/public_window_depend.hpp"

// private class header
#include "../private/window_class.hpp"

// INCLUDING_IN_HPP
#endif 


// PUBLIC_WINDOW_CLASS_HPP
#endif 