#ifndef LOL_BLOCKS_MAIN_ERROR_CODES_HPP
#define LOL_BLOCKS_MAIN_ERROR_CODES_HPP

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// direct x api
#include "main_program_lol.blocks.exe/dependencies/dx12api/directx_includes.hpp"

// global variables
#include "main_program_lol.blocks.exe/dependencies/global/globals.hpp"


namespace utilities {
	class lolblock_ec {
	public:
		lolblock_ec(std::source_location sl_loco = std::source_location::current()) noexcept
			:m_protected_error_code_location(sl_loco) {
		}

		enum class codes {
			success = 0,
			win32_window_fail,
			cpu_memory_pool_successful_allocation
		};

		lolblock_ec(std::initializer_list<lolblock_ec::codes> error_codes,
			std::source_location sl_loco = std::source_location::current()) noexcept
			:m_protected_error_code_location(sl_loco) {
			for (auto error_code : error_codes) {
				m_protected_vec_error_codes.push_back(error_code);
			}
		}

		std::vector<codes> get_codes() noexcept { return m_protected_vec_error_codes; }
		void push_new_codes(std::initializer_list<lolblock_ec::codes> error_codes) noexcept {
			for (auto error_code : error_codes) {
				m_protected_vec_error_codes.push_back(error_code);
			}
		}

		void set_new_location(std::source_location new_loco = std::source_location::current()) noexcept {
			m_protected_error_code_location = new_loco;
		}

		std::source_location get_current_location() noexcept { return m_protected_error_code_location; }

	protected:
		std::vector<codes> m_protected_vec_error_codes = {};
		std::source_location m_protected_error_code_location = {};
	};
}


// LOL_BLOCKS_MAIN_ERROR_CODES_HPP
#endif