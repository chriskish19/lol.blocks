#pragma once
// Main precompiled header for the lol.blocks.exe program
// this header is only meant to be used in the main project

#define USING_MAIN_PCH_HPP

// preprocessor setup
#include "macros/include/lol.blocks.macro_guard.include.hpp" // must always be first include!

// project dependant library code
#include "system_includes/ALL_STL_INCLUDES.hpp"
#include "system_includes/ALL_DX12_INCLUDES.hpp"
#include "system_includes/ALL_WINDOWS_INCLUDES.hpp"

// general project utilities
#include "system_includes/ALL_UTILITY_INCLUDES.hpp"

// lol.blocks main project classes
#include "classes/lol.blocks.class.include.hpp"

#ifdef USING_MAIN_PCH_HPP
#undef USING_MAIN_PCH_HPP
#endif