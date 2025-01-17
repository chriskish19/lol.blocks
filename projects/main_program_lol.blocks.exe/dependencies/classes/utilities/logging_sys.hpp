#ifndef LOGGING_SYSTEM_HEADER_HPP
#define LOGGING_SYSTEM_HEADER_HPP

// type settings
#include "main_program_lol.blocks.exe/dependencies/macros/type_settings.hpp"

// debug settings
#include "main_program_lol.blocks.exe/dependencies/macros/debug_settings.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// error handling
#include "main_program_lol.blocks.exe/errors/lol.codes.hpp"


namespace utilities {
	class base_logger {
	public:
		base_logger();
		~base_logger();
	private:

		class time_str {
		public:
			time_str();
			errors::codes set_current_time();
			string m_time_str;
			static const size_t reserved_length_heap_mem = 32;
		};

		class log_message {
		public:
			log_message();
			errors::codes set_log_message(const string& message);
			static const size_t reserved_length_mem_heap = 256;
			string m_message;
		};

		log_message* m_log_message_p = new log_message;
		time_str* m_time_str_p = new time_str;
	};

}



// LOGGING_SYSTEM_HEADER_HPP
#endif