#pragma once
#include <vector>
#include <initializer_list>
#include <source_location>


class lolblock_ec {
public:
	lolblock_ec(std::source_location sl_loco = std::source_location::current()) noexcept
		:m_protected_error_code_location(sl_loco){}

	enum class codes {
		win32_window_fail = 0,
		cpu_memory_pool_successful_allocation =1
	};

	lolblock_ec(std::initializer_list<lolblock_ec::codes> error_codes, 
		std::source_location sl_loco = std::source_location::current()) noexcept
		:m_protected_error_code_location(sl_loco){
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