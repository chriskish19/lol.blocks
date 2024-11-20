#pragma once
// NOTE: this testing pch includes everything in the whole main project (lol.blocks.exe)
// this header is only meant to be used in test_api.hpp

// preprocessor setup
#include "macros/debugging/LOL_BLOCKS_SYSTEM_DEBUG_MACROS.hpp" // must always be first include!
// #include "system_includes/ALL_LIBRARY_LINKING.hpp" // NOTE: this is handled by cmake now and not the preprocessor macros

// all project dependant library code
#include "pch/system_includes/ALL_STL_INCLUDES.hpp"
#include "pch/system_includes/ALL_DX12_INCLUDES.hpp"
#include "pch/system_includes/ALL_WINDOWS_INCLUDES.hpp"

// all our project code
#include "pch/system_includes/ALL_UTILITY_INCLUDES.hpp"
#include "classes/lol.blocks.class.include.hpp"
