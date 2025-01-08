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

// Control Debug and optimizations
#define ENABLE_FULL_DEBUG ON
#if ENABLE_FULL_DEBUG
#define ENABLE_FULL_OPTIMIZATIONS OFF
#else
#define ENABLE_FULL_OPTIMIZATIONS ON
#endif

// Control logging
#define ENABLE_DEEP_LOGS OFF
#define ENABLE_MIN_LOGGING OFF
#define ENABLE_MED_LOGGING ON

// little mechanism to prevent errors
#if ENABLE_DEEP_LOGS
#define ENABLE_MIN_LOGGING OFF
#define ENABLE_MED_LOGGING OFF
#elif ENABLE_MIN_LOGGING
#define ENABLE_MED_LOGGING OFF
#else
#define ENABLE_MED_LOGGING ON
#endif






