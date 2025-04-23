/***********************************************
*
*
*
*
*
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH


namespace lol_blocks {
	struct size_f {
		float szf_x, szf_y, szf_z;
	};
	
	struct size {
		std::size_t sz_x;
		std::size_t sz_y;
		std::size_t sz_z;

		// convert to gpu coordinates (floats)
		size_f convert_wc();
	};
	
	struct position {
		float x, y, z;
	};


	struct triangle {
		DirectX::XMFLOAT3 v1;
		DirectX::XMFLOAT3 v2;
		DirectX::XMFLOAT3 v3;
	};
	
	struct square {
		static const int size = 2;
		triangle faces[size];
	};

	struct cube {
		static const int size = 6;
		square faces[size];
	};
}