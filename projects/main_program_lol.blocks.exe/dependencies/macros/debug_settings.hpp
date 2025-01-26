// macros for controling the debugging process
#define ON 1
#define OFF 0



// Control Main entry point for whole application
#define USE_MAIN_ENTRY_CPP ON
#if USE_MAIN_ENTRY_CPP
#define USE_TEST_API OFF
#else
#define USE_TEST_API ON
#endif

// Control Debug and optimizations for lol.blocks main
// graphics rendering has its own debug macro
#define ENABLE_FULL_DEBUG ON
#if ENABLE_FULL_DEBUG
#define ENABLE_FULL_OPTIMIZATIONS OFF
#else
#define ENABLE_FULL_OPTIMIZATIONS ON
#endif

// Control debug for graphics api
#define ENABLE_DX_DEBUG ON

// Control logging
#define ENABLE_DEEP_LOGS ON
#define ENABLE_MED_LOGGING ON
#define ENABLE_MIN_LOGGING ON


// Testing code
#define TESTING ON

// set which graphics api we are using
#define USING_DX12_API OFF
#define USING_DX11_API ON

// control exceptions
#define ENABLE_ALL_EXCEPTIONS ON