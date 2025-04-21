/***********************************************
* File: settings.hpp
*
* Purpose: Manage macro settings thorughout lol.blocks
*
*
*
************************************************/

#define MAX_STRING 512

#if defined(UNICODE) || defined(_UNICODE)
#define COUT std::wcout
#define CERR std::wcerr

// read only string, prepends L"string literal"
#define ROS(x) L##x

// using wide strings
#define USING_WIDE_STRINGS 1
#define WIDE USING_WIDE_STRINGS

#else // ANSI

#define COUT std::cout
#define ROS(x) x
#define USING_STR 1
#define NARROW USING_STR
#endif // defined(UNICODE) || defined(_UNICODE)

// for running demos
#define DEMO_ENTRY 1

#ifdef TEST // compiler definition macro

#define ENTRY_TEST 1

#elif DEMO_ENTRY

// left blank intentionally
#else

#define MAIN_ENTRY 1

#endif


// driect x debug macro
#if defined(DEBUG) ||  defined(_DEBUG)


#define DX11_DEBUG 1
#define DX12_DEBUG 1


#endif


