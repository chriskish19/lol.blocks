/***********************************************
* File: names.hpp
*
* Purpose: makes for easy file name changes and file moves
*
*
*
************************************************/

// dependencies (include headers)
#define STL_PRIVATE_INCLUDE_PATH				stl_includes_hpp				// huge list of all c++ standard library includes
#define STL_INCLUDE_PATH						stl_hpp							// the header to use when including the c++ standard library
#define SETTINGS_INCLUDE_PATH					settings_hpp					// macro defines that set certain values
#define TYPES_INCLUDE_PATH						types_hpp						// handles unicode types
#define WINDOWS_INCLUDE_PATH					windows_includes_hpp			// all windows api includes listed 
#define DEPENDENCIES_INCLUDE_PATH				include_dependencies_hpp		// an include header that lists all dependencies for easy including
#define PCH_INCLUDE_PATH						pch_hpp							// pre compiled header that includes everything
#define STANDARD_INCLUDE_PATH					standard_hpp					// standard macro defines used throughout lol.blocks
#define DXAPI_INCLUDE_PATH						dx_api_inc_hpp					// all direct x includes


// lol_blocks_api (namespace)
#define LOLAPI_INCLUDE_PATH						lol_api_hpp						// list of helper functions

// lol_blocks (namespace)
#define CODES_INCLUDE_PATH						lol_codes_hpp					// error codes used throughout lol.blocks
#define CODE_UTILITIES_INCLUDE_PATH				cu_hpp							// helper functions used within error
#define CODEOBJECT_INCLUDE_PATH					co_hpp							// class for handling errors
#define WINDOW_INCLUDE_PATH						lol_window_hpp					// base functions for creating win32 window
#define WD_INCLUDE_PATH							lol_window_d_hpp				// (window demo) used to create a win32 window and display graphics
#define DESCRIPTION_INCLUDE_PATH				lol_description_hpp				// error code descriptions


// dx11 (namespace)
#define EDX11U_INCLUDE_PATH						e_dx11_u_hpp					// (errors direct x 11 utilities) helper functions for dx11 errors
#define DX11SETUP_INCLUDE_PATH					sdx11_hpp						// basic dx11 setup
#define DX11D_INCLUDE_PATH						lol_dx11_d_hpp					// (direct x 11 demo) some demos (drawing a triangle etc...)

// dx11 demo shaders
#define TDDX11VS_FILE_PATH						td_dx11_vs_hlsl					// (triangle demo direct x 11 vertex shader)
#define TDDX11PS_FILE_PATH						td_dx11_ps_hlsl					// (triangle demo direct x 11 pixel shader)
#define TXDDX11VS_FILE_PATH						txd_dx11_vs_hlsl				// (texture demo direct x 11 vertex shader)
#define TXDDX11PS_FILE_PATH						txd_dx11_ps_hlsl				// (texture demo direct x 11 pixel shader)


// dx11 demo textures
#define TX_GRAPH								graph_png
#define TX_STICK								stick_png						// stickman sprite