/****************************************************************
	Header: function_binder.hpp

	Purpose: creates a call back function and binds the arguments.

****************************************************************/

#pragma once

// all macros
#include "main_program_lol.blocks.exe/macros/include/lol.macros.include.hpp"

// all external library headers
#include "main_program_lol.blocks.exe/pch/includes/external.hpp"

namespace utilities {

    class function_binder {
    public:
        template <typename F, typename class_obj>
        function_binder(F&& func, class_obj&& obj) {
            // Bind the provided function and arguments
            auto callback = std::bind(func,obj);

            m_callback = std::function<void()>(callback);
        }

        std::function<void()> m_callback;
    };

	
}