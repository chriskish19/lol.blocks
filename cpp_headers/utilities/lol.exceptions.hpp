#pragma once
#include "pch/lol.blocks.main.PCH.hpp"
#include "lol.blocks_error_codes.hpp"
#include "logging_sys.hpp"




class lol_base_exception : public std::exception, public virtual log_info{
public:


protected:


};

class win32_window_error_exception : public lol_base_exception {
public:


private:


};

class win32_general_error : public lol_base_exception {
public:


private:

};

template<typename function_return_type,typename ... function_arguments_types>
inline auto handle_exceptions(
	std::function<function_return_type(function_arguments_types ...)> function_that_may_throw,
	function_arguments_types ... individual_arguments) {
	
	
	try {
		return function_that_may_throw(individual_arguments ...);
	}
	catch (const std::logic_error& e) {

	}
	catch (const std::runtime_error& e) {

	}
	catch (const win32_window_error_exception& e) {

	}
	catch (const win32_general_error& e) {

	}
	catch (const lol_base_exception& e) {

	}
	catch (const std::exception& e) {

	}
}