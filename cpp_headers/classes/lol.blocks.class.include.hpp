#pragma once

#define USING_MAIN_PROJECT_CLASSES

// we include here all classes in the main project (lol.block.exe)
#include "win32_api/resource.h" // Must be top include here!

#include "dx12/direct12_init.hpp"

#ifdef WINDOW_CLASS_NOT_INCLUDE_HPP
#else
#include "win32_api/window_class.hpp"
#endif // WINDOW_CLASS_NOT_INCLUDE_HPP 



#ifdef USING_MAIN_PROJECT_CLASSES
#undef USING_MAIN_PROJECT_CLASSES
#endif