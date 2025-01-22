#ifndef DIRECTX_INCLUDES_HPP
#define DIRECTX_INCLUDES_HPP

// macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// basic directx infrastucture
#include <dxgi.h>

// compiler header for interpreting hlsl
#include <d3dcompiler.h> 

// support for microsoft comptr
#include <wrl.h>


#if USING_DX12_API
// directx12 header
#include <d3d12.h>

// directx12 utilities
#include "main_program_lol.blocks.exe/dependencies/dx_api/d3dx12.h"

// USING_DX12_API
#endif 

#if USING_DX11_API

// directx 11 header
#include <d3d11.h>

// USING_DX11_API
#endif 


// DIRECTX_INCLUDES_HPP
#endif
