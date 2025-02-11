/****************************************************************
	Header: lol.codes.hpp

	Purpose: error handling for the whole program

****************************************************************/

// NOTES: This header is designed to be used anywhere and everywhere in lol.blocks
// it doesnt depend on any classes...


#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"


namespace w32errors_cstr {
	// win32_codes string explainations
	const character* success = READ_ONLY_STRING("win32_codes: success, successful execution");
	const character* menu_error = READ_ONLY_STRING("win32_codes: menu_error, an issue with when creating a menu item using CreateMenu()");
	const character* HWND_error = READ_ONLY_STRING("win32_codes: HWND_error, the window handle is nullptr");
	const character* register_class_fail = READ_ONLY_STRING("win32_codes: register_class_fail, issue when calling RegisterClass()");
	const character* get_client_rect_fail = READ_ONLY_STRING("win32_codes: get_client_rect_fail, issue when trying to obtain the client window size using GetClientRect()");
	const character* invalidate_rect_fail = READ_ONLY_STRING("win32_codes: invalidate_rect_fail, issue when calling the function InvalidateRect()");
	const character* font_error = READ_ONLY_STRING("win32_codes: font_error, a problem when creating a new font. The function CreateFont() failed");
}

namespace errors_cstr {
	// regular codes string explainations
	const character* success = READ_ONLY_STRING("codes: success, successful execution");
	const character* pointer_is_nullptr = READ_ONLY_STRING("codes: pointer_is_nullptr, pointer has no memory to point to");
	const character* wide_string_copy_fail_wcs_cpy = READ_ONLY_STRING("codes: wide_string_copy_fail_wcs_cpy, wide string copy function failed to copy the string");
	const character* strings_not_equal = READ_ONLY_STRING("codes: strings_not_equal, the two strings you are comparing are different in size or characters");
	const character* empty_string = READ_ONLY_STRING("codes: empty_string, the string is empty. no characters.");
	const character* string_length_too_long = READ_ONLY_STRING("codes: string_length_too_long, the strings length is too long for this function to procced");
	const character* index_out_of_range = READ_ONLY_STRING("codes: index_out_of_range, you are trying to access an array/vector using an index that is non existant in the array/vector");
	const character* division_by_zero = READ_ONLY_STRING("codes: division_by_zero, trying to divide by zero is undefined");
	const character* unknown_keyboard_key_in_system_message_handler = READ_ONLY_STRING("codes: unknown_keyboard_key_in_system_message_handler, where key presses are handled in the program a key has been pressed that is not known");
	const character* unknown_mouse_button_in_system_message_handler = READ_ONLY_STRING("codes: unknown_mouse_button_in_system_message_handler, where mouse button presses are handled in the program a mouse button has been pressed which is not known");
	const character* dx_error = READ_ONLY_STRING("codes: dx_error, a direct x error has occurred");
	const character* exception_thrown_and_handled = READ_ONLY_STRING("codes: exception_thrown_and_handled, an exception has occurred and has been caught and handled");
	const character* to_wide_string_failed = READ_ONLY_STRING("codes: to_wide_string_failed, converting a narrow string to wide string has failed");
	const character* to_narrow_string_failed = READ_ONLY_STRING("codes: to_narrow_string_failed, converting a wide string to narrow has failed");
}


/*  helpful functions for error objects */ 
/****************************************/
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
}


/*  codes and dependant templates		*/
/****************************************/
namespace errors {
	template<typename t1, typename t2>
	class any_two {
	public:
		any_two() = default;
		any_two(const t1& one,const t2& two) noexcept
			:m_one(one), m_two(two) {
		}

		t1 m_one;
		t2 m_two;
	};


	template<typename t>
	class basic_error : public std::exception {
	public:
		basic_error(const any_two<t,string>& code) noexcept
			:m_error_code(code){}

		basic_error(const t code,const string& message) noexcept {
			m_error_code.m_one = code;
			m_error_code.m_two = message;
		}

		const char* what() const noexcept override {
#if USING_WIDE_STRINGS
			return to_narrow_string(m_error_code.m_two).c_str();
#endif

#if USING_NARROW_STRINGS
			return m_error_code.m_two.c_str();
#endif
		}

		virtual string full_error_message() noexcept{
			return std::format(READ_ONLY_STRING("error message: {}"), m_error_code.m_two);
		}
	protected:
		any_two<t,string> m_error_code;
	};

	
	// basic random error code mesages
	// most are class objects with the same names below
	// they are also exceptions
	enum class codes {
		success = 0,
		pointer_is_nullptr,
		wide_string_copy_fail_wcs_cpy,
		strings_not_equal,
		empty_string,
		string_length_too_long,
		index_out_of_range,
		division_by_zero,
		unknown_keyboard_key_in_system_message_handler,
		unknown_mouse_button_in_system_message_handler,
		dx_error,
		exception_thrown_and_handled,
		to_wide_string_failed,
		to_narrow_string_failed
	};

	enum class win32_codes {
		success = 0,
		menu_error,
		HWND_error,
		register_class_fail,
		get_client_rect_fail,
		invalidate_rect_fail,
		font_error
	};
}

/* regular code error objects */
/******************************/
namespace code_error_objs {
	using namespace errors;

	extern any_two<codes, string>* success,
		pointer_is_nullptr,
		wide_string_copy_fail_wcs_cpy,
		strings_not_equal,
		empty_string,
		string_length_too_long,
		index_out_of_range,
		division_by_zero,
		unknown_keyboard_key_in_system_message_handler,
		unknown_mouse_button_in_system_message_handler,
		dx_error,
		exception_thrown_and_handled,
		to_wide_string_failed,
		to_narrow_string_failed;

	class code_obj {
	public:
		code_obj(any_two<codes,string>* code) noexcept
			:m_code(*code){ }

		string output() {
			return m_code.m_two;
		}
	protected:
		any_two<codes, string> m_code;
	};
}

namespace win32_code_objs {
	using namespace errors;

	extern any_two<win32_codes, string>* success,
		menu_error,
		HWND_error,
		register_class_fail,
		get_client_rect_fail,
		invalidate_rect_fail,
		font_error;

	class code_obj {
	public:
		code_obj(any_two<win32_codes, string>* code) noexcept
			:m_code(*code) {
		}

		string output() {
			return m_code.m_two;
		}
	protected:
		any_two<win32_codes, string> m_code;
	};

	
}




/*  error objects						*/
/****************************************/
namespace errors {

	class base_error {
	public:
		base_error() = default;
		virtual string full_error_message() noexcept;
		virtual string get_code_string() noexcept;
	};

	class success {
	public:
		codes m_ec = codes::success;
		string m_info = READ_ONLY_STRING("successful execution no errors returned!");
	};

	class win32_error : public std::exception, public base_error{
	public:
		win32_error(const string& location=errors::get_location()) noexcept;
		virtual string get_more_info() noexcept { return m_info; }
		virtual codes get_code() noexcept { return m_ec; }
		string get_code_string() noexcept override { return m_ec_str; }
		string get_last_error_win32() noexcept;
		
		
		const char* what() const noexcept override {
			return "win32 error occurred"; 
		}

		string full_error_message() noexcept override;
	protected:
		codes m_ec = codes::win32_error;
		string m_ec_str = READ_ONLY_STRING("errors::codes::win32_error");
		string m_info = READ_ONLY_STRING("win32 error: ") + get_last_error_win32();
		string m_location;
	};



	class pointer_is_nullptr : public std::exception, public base_error {
	public:
		pointer_is_nullptr(const string& p_name,const string& location=errors::get_location())
			:m_pointer_name(p_name),m_location(location){ }

		const char* what() const noexcept override {
			return "nullptr!";
		}

		string get_pointer_variable_name() { return m_pointer_name; }
		string get_code_string() noexcept override{ return m_ec_str; }

		string full_error_message() noexcept override;
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



	class dx_error : public std::exception , public base_error{
	public:
		dx_error(HRESULT hr, const string& location = errors::get_location()) noexcept;
		dx_error(HRESULT hr, ID3DBlob* error, const string& location = errors::get_location()) noexcept;
		
		// only use if dx11 device was created
		dx_error(HRESULT hr, ID3D11InfoQueue* debug_info_p, const string& location = errors::get_location()) noexcept;


		const char* what() const noexcept override {
			return "dx error occurred!";
		}

		string full_error_message() noexcept override;
		string get_code_string() noexcept override { return m_ec_str; }

	private:
		codes m_ec = codes::dx_error;
		string m_info = READ_ONLY_STRING("DirectX error hresult: ");
		string m_location;
		string m_ec_str = READ_ONLY_STRING("errors::codes::dx_error");
		string m_dx_error_blob_str;
		string m_debug_info_str;

		void translate_HRESULT(HRESULT hr) noexcept;
		void translate_error_blob(ID3DBlob* error) noexcept;
		void translate_debug_info(ID3D11InfoQueue* debug_info_p) noexcept;
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
		win32_menu_error(const string& location = get_location())
			:m_location(location){ }

		string get_more_info() noexcept override { return m_info; }
		codes get_code() noexcept override { return m_ec; }

		string full_error_message() noexcept override;
		string get_code_string() noexcept override { return m_ec_str; }
	private:
		codes m_ec = codes::win32_menu_error;
		string m_info = READ_ONLY_STRING("unable to create menu.");
		string m_location;
		string m_ec_str = READ_ONLY_STRING("errors::codes::win32_menu_error");
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

	class to_wide_string_fail : public std::exception {
	public:
		to_wide_string_fail();


	protected:

	};

}

/*  some ways of dealing with exceptions and errors	*/
/****************************************************/
namespace errors {
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
		catch (const std::filesystem::filesystem_error& e) {

		}

		return std::nullopt;
	}


	void handle_error_codes(errors::codes code, const string& location = errors::get_location()) noexcept;
}
