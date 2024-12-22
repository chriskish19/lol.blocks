// This is to control the cpp version before using the library and throw a comp error if its not cpp 20
// the macros defined here are only meant for this import header
// currently the library is designed to use cpp 20 only...

#if defined(_MSVC_LANG)
#define WIN32_GUI_USING_MSVC_CPP_LANG_VERSION _MSVC_LANG
#define WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION _MSVC_LANG
#elif defined(__clang__)
#define WIN32_GUI_USING_CLANG_CPP_LANG_VERSION __cplusplus
#define WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION __cplusplus
#elif defined(__GNUC__)
#define WIN32_GUI_USING_GCC_CPP_LANG_VERSION __cplusplus
#define WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION __cplusplus
#else
#define COMPILER_NOT_SUPPORTED 1
#error "only supports 3 compiler vendors MSVC, GCC and Clang"
#endif

#if ((WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION < 201402L) || (WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION > 202302L))
#define CPP_LANG_VERSION_NOT_SUPPORTED 1
#error "only supports c++ 14 to 23"
#endif


#if WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION == 201402L
// C++14
#define WIN32_GUI_CPP_14 2014
#elif WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION == 201703L
// C++17
#define WIN32_GUI_CPP_17 2017
#elif WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION == 202002L
// C++20
#define WIN32_GUI_CPP_20 2020
#elif WIN32_GUI_GENERAL_MACRO_CPP_LANG_VERSION == 202302L
// C++23
#define WIN32_GUI_CPP_23 2023
#endif


// check which os we are using
#ifndef _WIN32
#error "This is a Windows OS specific Library!"
#endif

// make sure we are using cpp 20
#ifdef WIN32_GUI_CPP_20
#else
#error "win32 gui library is only meant for cpp 20"
#endif


// define these macros in the preprocessor or in your project that is using win32 gui lib...
#ifdef PREPRO_DLL_COMPILING_WIN32_GUI_LIB
#define WIN32_GUI_API __declspec(dllimport)
#elif defined(PREPRO_USING_WIN32_GUI_LIB)
#define WIN32_GUI_API __declspec(dllexport)
#else 
#error "You need to define the proper macros in order to use win32 gui lib!"
#endif

