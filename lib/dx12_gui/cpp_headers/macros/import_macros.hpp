#pragma once

// check which os we are using
#ifndef _WIN32
#error "This is a Windows OS specific Library!"
#endif

// check for directx12 on system
#if __has_include(<d3d12.h>)
#else
#error "This library requires direct x 12 to be present on system!"
#endif


// define these macros in the preprocessor or in your project that is using dx12 gui lib...
#ifdef PREPRO_DLL_COMPILING_DX12_GUI_LIB
#define DX12_GUI_API __declspec(dllimport)
#elif defined(PREPRO_USING_DX12_GUI_LIB)
#define DX12_GUI_API __declspec(dllexport)
#else 
#error "You need to define the proper macros in order to use dx12 gui lib!"
#endif
