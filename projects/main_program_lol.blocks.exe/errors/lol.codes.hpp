#pragma once

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug macros
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"


namespace errors {
	enum class codes {
		success = 0,
		win32_error,
		cpu_memory_pool_successful_allocation,
		using_new_memory_allocation_fail,
		pointer_is_nullptr,
		wide_string_copy_fail_wcs_cpy,
		strings_not_equal,
		empty_string
	};

	class success {
	public:
		codes m_ec = codes::success;
		string m_info = READ_ONLY_STRING("successful execution no errors returned!");
	};

	class win32_error : public std::exception {
	public:
		string get_more_info() noexcept { return m_info; }
		string get_last_error_win32() noexcept;
		const char* what() const noexcept override {
			return "win32 error occurred"; 
		}
		codes send_to_window(HWND window_handle) noexcept;
	private:
		codes m_ec = codes::win32_error;
		string m_info = READ_ONLY_STRING("win32 error: ") + get_last_error_win32();
	};

	class pointer_is_nullptr : public std::exception {
	public:
		const char* what() const noexcept override {
			return "nullptr!";
		}

	private:
		codes m_ec = codes::pointer_is_nullptr;
		string m_info = READ_ONLY_STRING("pointer has no memory to point to...");
	};

	class strings_not_equal : public std::exception {
	public:
		const char* what() const noexcept override {
			return "strings !=";
		}


	private:
		codes m_ec = codes::strings_not_equal;
		string m_info = READ_ONLY_STRING(
			"the strings you are comparing are different sizes or have different chars.");

	};












	template<typename function_return_type, typename ... function_arguments_types>
	inline auto handle_exceptions(
		std::function<function_return_type(function_arguments_types ...)> function_that_may_throw,
		function_arguments_types ... individual_arguments) -> std::optional<function_return_type> {


		try {
			return function_that_may_throw(individual_arguments ...);
		}
		catch (const std::logic_error& e) {

		}
		catch (const std::runtime_error& e) {

		}
		catch (const std::exception& e) {

		}

		return std::nullopt;
	}
}