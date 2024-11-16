#pragma once
// NOTE: this testing pch includes everything in the whole main project (lol.blocks.exe)


// preprocessor setup
#include "debugging/LOL_BLOCKS_SYSTEM_DEBUG_MACROS.hpp" // must always be first include!
// #include "system_includes/ALL_LIBRARY_LINKING.hpp" // NOTE: this is handled by cmake now and not the preprocessor macros

// project dependant library code
#include "system_includes/ALL_STL_INCLUDES.hpp"
#include "system_includes/ALL_DX12_INCLUDES.hpp"
#include "system_includes/ALL_WINDOWS_INCLUDES.hpp"

// our project code
#include "system_includes/ALL_UTILITY_INCLUDES.hpp"
#include "win32_api/resource.h"
#include "win32_api/window_class.hpp"
