/****************************************************************
	Header: t_window_class.hpp

	Purpose: a class template for handling window class mt...

****************************************************************/

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

// classes
#include "main_program_lol.blocks.exe/classes/window/monolithic/main_window_class_mt.hpp"

namespace window {
	
	class t_window : public window_class_mt {
	public:
		template<typename FunctionType, typename... Args>
		t_window(FunctionType&& func, Args&&... args) {
			// Create a callable object using std::bind
			auto bound_func = std::bind(std::forward<FunctionType>(func), std::forward<Args>(args)...);

			m_callback = std::function<void()>(bound_func);
		}

		std::function<void()> m_callback;

		~t_window() = default;
	};

	
}