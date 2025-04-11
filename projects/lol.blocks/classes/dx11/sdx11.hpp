/***********************************************
* File: sdx11.hpp (setup direct x 11)
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include EDX11U_INCLUDE_PATH


namespace dx11 {
	
	
	struct device_description {
		IDXGIAdapter*				pAdapter;
		D3D_DRIVER_TYPE				DriverType;
		HMODULE						Software;
		UINT						Flags;
		const D3D_FEATURE_LEVEL*	pFeatureLevels;
		UINT						FeatureLevels;
		UINT						SDKVersion;
		const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc;
		IDXGISwapChain*				pSwapChain;
		ID3D11Device*				pDevice;
		D3D_FEATURE_LEVEL*			pFeatureLevel;
		ID3D11DeviceContext*		pImmediateContext;
	};

	// create device and swapchain
	lb::codes create_device(HWND handle, device_description* const dd);


}