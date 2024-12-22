// macros for controling the debugging process
#define RUN_TEST_API 1



#if defined(RUN_TEST_API)
#define ENTRY TEST_MAIN_ENTRY_CPP
#else
#define ENTRY 
#endif
