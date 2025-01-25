// NOTES: This header is designed to be used anywhere and everywhere in lol.blocks
// it doesnt depend on any classes...



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
	// these functions are meant to be used only within lol.codes.hpp



	// returns the location of the function call site, used in exceptions classes constructor
	string get_location(std::source_location sl = std::source_location::current());
	


	// if there is no error an empty string is returned
	string get_last_error_win32();
	


	// if these functions fail they return an empty string.
	std::wstring to_wide_string(const std::string& narrow);
	std::string to_narrow_string(const std::wstring& wide);


	// a message box window that will display errors, for when system log window cant be used
	// or for pessky debug errors
	void show_error_message_window(const string& message, const string& title);



	// basic random error code mesages
	// most are class objects with the same names below
	// they are also exceptions
	enum class codes {
		success = 0, // this one must be zero
		win32_error,
		pointer_is_nullptr,
		wide_string_copy_fail_wcs_cpy,
		strings_not_equal,
		empty_string,
		string_length_too_long,
		index_out_of_range,
		win32_font_error,
		division_by_zero,
		unknown_keyboard_key_in_system_message_handler,
		unknown_mouse_button_in_system_message_handler,
		dx_error,
		get_client_rect_failed,
		invalidate_rect_failed,
		window_closing,
		window_cant_close,
		win32_menu_error,
		win32_HWND_error,
		win32_register_class_fail
	};



	class success {
	public:
		codes m_ec = codes::success;
		string m_info = READ_ONLY_STRING("successful execution no errors returned!");
	};



	class win32_error : public std::exception {
	public:
		win32_error(const string& location=errors::get_location());
		virtual string get_more_info() noexcept { return m_info; }
		virtual codes get_code() noexcept { return m_ec; }
		virtual string get_code_string() noexcept { return m_ec_str; }
		string get_last_error_win32() noexcept;
		const char* what() const noexcept override {
			return "win32 error occurred"; 
		}

		virtual string full_error_message();
	protected:
		codes m_ec = codes::win32_error;
		string m_ec_str = READ_ONLY_STRING("errors::codes::win32_error");
		string m_info = READ_ONLY_STRING("win32 error: ") + get_last_error_win32();
		string m_location;
	};



	class pointer_is_nullptr : public std::exception {
	public:
		pointer_is_nullptr(const string& p_name,const string& location=errors::get_location())
			:m_pointer_name(p_name),m_location(location){ }

		const char* what() const noexcept override {
			return "nullptr!";
		}

		string get_pointer_variable_name() { return m_pointer_name; }
		string get_error_code_string() noexcept { return m_ec_str; }

		string full_error_message();
	private:
		codes m_ec = codes::pointer_is_nullptr;
		string m_ec_str = READ_ONLY_STRING("errors::codes::pointer_is_nullptr");
		string m_info = READ_ONLY_STRING("pointer has no memory to point to...");
		string m_location;
		string m_pointer_name;
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



	class string_length_too_long : public std::exception {
	public:
		const char* what() const noexcept override {
			return "string is too long!";
		}

	private:
		codes m_ec = codes::string_length_too_long;
		string m_info = READ_ONLY_STRING(
			"the strings you are comparing is too long for whatever reason");
	};



	class index_out_of_range : public std::exception{
	public:
		index_out_of_range(size_t index) :m_index(index) {}

		const char* what() const noexcept override {
			return "index is wrong!";
		}

	private:
		codes m_ec = codes::index_out_of_range;
		string m_info = READ_ONLY_STRING("you are attempting to access an array or vector using an index value that is beyond the capacity of the array/vector");
		size_t m_index;
	};



	class win32_font_error : public std::exception{
	public:
		win32_font_error() = default;

		const char* what() const noexcept override {
			return "font failed to be created.";
		}
	private:
		codes m_ec = codes::win32_font_error;
		string m_info = READ_ONLY_STRING("font failed to be created.");
	};



	class division_by_zero : public std::exception {
	public:
		division_by_zero() = default;

		const char* what() const noexcept override {
			return "error division by zero!";
		}

	private:
		codes m_ec = codes::division_by_zero;
		string m_info = READ_ONLY_STRING("division by zero error!");
	};



	class dx_error : public std::exception {
	public:
		dx_error(HRESULT hr);

		const char* what() const noexcept override {
			return "dx error occurred!";
		}

	private:
		codes m_ec = codes::dx_error;
		string m_info = READ_ONLY_STRING("DirectX error hresult: ");
	};



	class get_client_rect_failed : public win32_error {
	public:
		get_client_rect_failed() = default;
		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }
		string full_error_message() noexcept override;
		string get_code_string() noexcept override { return m_ec_str; }
	private:
		codes m_ec = codes::get_client_rect_failed;
		string m_ec_str = READ_ONLY_STRING("errors::codes::get_client_rect_failed");
		string m_info = READ_ONLY_STRING("unable to get the window rectangle.");
	};


	class invalidate_rect_failed : public win32_error {
	public:
		invalidate_rect_failed() = default;
		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }
	private:
		codes m_ec = codes::invalidate_rect_failed;
		string m_info = READ_ONLY_STRING("unable to invalidate rect.");
	};


	class win32_menu_error : public win32_error {
	public:
		win32_menu_error() = default;
		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }
	private:
		codes m_ec = codes::win32_menu_error;
		string m_info = READ_ONLY_STRING("unable to create menu.");
	};


	class win32_HWND_error : public win32_error {
	public:
		win32_HWND_error() = default;
		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }
		string full_error_message() noexcept override;
		string get_code_string() noexcept override { return m_ec_str; }
	private:
		codes m_ec = codes::win32_HWND_error;
		string m_ec_str = READ_ONLY_STRING("codes::win32_HWND_error");
		string m_info = READ_ONLY_STRING("the handle to the window is nullptr.") + get_last_error_win32();
	};

	class win32_register_class_fail : public win32_error {
	public:
		win32_register_class_fail(const string& location = errors::get_location())
			:m_location(location){ }

		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }
		string full_error_message() noexcept override;
		string get_code_string() noexcept override { return m_ec_str; }

	private:
		codes m_ec = codes::win32_register_class_fail;
		string m_ec_str = READ_ONLY_STRING("codes::win32_register_class_fail");
		string m_info = READ_ONLY_STRING("class was unable to be registered...");
		string m_location;
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

	
	void handle_error_codes(errors::codes code, const string& location = errors::get_location());
}