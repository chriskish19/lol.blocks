#pragma once

// check which os we are using
#ifndef _WIN32
#error "This is a Windows OS specific Library!"
#endif

// define these macros in the preprocessor or in your project that is using win32 gui lib...
#ifdef PREPRO_DLL_COMPILING_WIN32_GUI_LIB
#define WIN32_GUI_API __declspec(dllimport)
#elif defined(PREPRO_USING_WIN32_GUI_LIB)
#define WIN32_GUI_API __declspec(dllexport)
#else 
#error "You need to define the proper macros in order to use win32 gui lib!"
#endif
