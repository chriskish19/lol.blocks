#pragma once
#include "pch/lol.blocks.main.PCH.hpp"

#ifdef USING_MAIN_PROJECT_CLASSES
#define DX12_INCLUDE_HPP
#include "classes/dx12/direct12_init.hpp"
#elif defined(USING_MAIN_PCH_HPP)
#define DX12_ALREADY_INCLUDED
#else
#define DX12_INCLUDE_HPP_NOT

class directx {
public:
	directx();

private:


};

#endif
