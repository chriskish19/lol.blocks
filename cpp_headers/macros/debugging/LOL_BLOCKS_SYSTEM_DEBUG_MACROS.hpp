#pragma once
// This header is for debuging control and defines macros used in the main project (lol.blocks.exe)


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


// Exception handling control
#ifndef LOL_BLOCKS_EXCEPTIONS_ENABLED
#define LOL_BLOCKS_EXCEPTIONS_ENABLED TRUE
#endif

#ifdef LOL_BLOCKS_EXCEPTIONS_SWITCH

#endif


#ifdef DEBUG
#ifndef LOL_BLOCKS_GENERAL_DEBUGGING_ENABLED
#define LOL_BLOCKS_GENERAL_DEBUGGING_ENABLED TRUE
#endif // #ifndef LOL_BLOCKS_GENERAL_DEBUGGING_ENABLED
#endif // #ifdef DEBUG

#ifdef LOL_BLOCKS_GENERAL_DEBUGGING_ENABLED
#define LOL_BLOCKS_DX12_DEBUGGING_ENABLED TRUE
#define LOL_BLOCKS_LOGGING_SYSTEM_DEBUGGING_ENABLED TRUE
#define LOL_BLOCKS_MEMORY_MANAGER_DEBUGGING_ENABLED TRUE
#endif




// prevent problems in other headers that may use TRUE (windows.h)
#ifdef TRUE
#undef TRUE
#endif

// prevent problems in other headers that may use FALSE (windows.h)
#ifdef FALSE
#undef FALSE
#endif