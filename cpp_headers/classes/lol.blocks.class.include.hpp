#pragma once

#define USING_MAIN_PROJECT_CLASSES

// we include here all classes in the main project (lol.block.exe)
#include "win32_api/resource.h" // Must be top include here!

#include "dx12/direct12_init.hpp"
#include "win32_api/window_class.hpp"

#ifdef USING_MAIN_PROJECT_CLASSES
#undef USING_MAIN_PROJECT_CLASSES
#endif