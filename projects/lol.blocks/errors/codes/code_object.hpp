/***********************************************
* File: code_object.hpp
*
* Purpose: 
*
* Used: 
*
************************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDENCIES_INCLUDE_PATH
#include CODES_INCLUDE_PATH
#include CODE_UTILITIES_INCLUDE_PATH


namespace lol_blocks {
	class lolblock_error : public std::exception {
	public:
		lolblock_error() = default;
		lolblock_error(codes code, const string& description, const string& location = get_location())
			:m_code(code),m_description(description),m_location(location){ }
		
	
		const codes m_code;
		const string m_description;
		const string m_location;
	};


}