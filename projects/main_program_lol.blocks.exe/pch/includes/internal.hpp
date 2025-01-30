/****************************************************************
	Header: internal.hpp

	Purpose: includes all headers that are part of lol.blocks
		

****************************************************************/

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// error codes
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"

// globals
#include "main_program_lol.blocks.exe/global/globals.hpp"

// class utlities
#include "main_program_lol.blocks.exe/classes/utilities/keyboard_sys.hpp"
#include "main_program_lol.blocks.exe/classes/utilities/logging_sys.hpp"
#include "main_program_lol.blocks.exe/classes/utilities/lol.api.hpp"
#include "main_program_lol.blocks.exe/classes/utilities/mouse_sys.hpp"
#include "main_program_lol.blocks.exe/classes/utilities/thread_manager.hpp"
#include "main_program_lol.blocks.exe/classes/utilities/timer.hpp"

// math
#include "main_program_lol.blocks.exe/classes/math/lol.math.hpp"

// physics
#include "main_program_lol.blocks.exe/classes/physics/physics_sys.hpp"

// window
#include "main_program_lol.blocks.exe/classes/window/log_window_class.hpp"
#include "main_program_lol.blocks.exe/classes/window/main_window_class_mt.hpp"
#include "main_program_lol.blocks.exe/classes/window/starter.hpp"
#include "main_program_lol.blocks.exe/classes/window/system_log_window.hpp"
#include "main_program_lol.blocks.exe/classes/window/window_class_log_window.hpp"

// dx
#include "main_program_lol.blocks.exe/dx/dx_device_init.hpp"
#include "main_program_lol.blocks.exe/dx/loading.hpp"