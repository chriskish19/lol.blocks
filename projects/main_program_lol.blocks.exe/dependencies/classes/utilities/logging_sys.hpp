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
	class logger {
	public:
		logger() = default;
		~logger();
	private:
		class base_logger {
		public:
			base_logger();
			~base_logger();
			errors::codes log_a_message(const string& message);
		private:
			class time_str {
			public:
				time_str();
				errors::codes set_current_time();
				string m_time_str;
				static const size_t reserved_length_heap_mem = 32;
			};
		public:
			class log_message {
			public:
				log_message();
				errors::codes set_log_message(const string& message);
				static const size_t reserved_length_mem_heap = 256;
				string m_message;
			};
		private:
			log_message* m_log_message_p = new log_message;
			time_str* m_time_str_p = new time_str;
		public:
			log_message* get_message_p() { return m_log_message_p; }
		};
	public:
		class logs {
		public:
			logs();
			~logs();

			size_t get_index_pos() { return m_index_pos; }
			errors::codes log_message(const string& message);
			string get_most_recent_log();
			string get_log_by_index(size_t index = 0);
			size_t get_vec_log_size() { return m_bl_vec_p.size(); }
			base_logger* get_base_logger_p_by_index(size_t index = 0);
			size_t get_log_index_pos() { return m_index_pos; }
		private:
			std::vector<base_logger*> m_bl_vec_p = {};
			static const size_t m_bl_vec_reserved_capacity = 500;
			size_t m_index_pos = 0;

			std::mutex m_message_mtx;
		};
	private:
		std::atomic<logs*>* m_stored_logs_p = new std::atomic<logs*>(new logs);
	public:
		std::atomic<logs*>* get_logs_p() { return m_stored_logs_p; }
	};



	

}



// LOGGING_SYSTEM_HEADER_HPP
#endif