#pragma once
#include <exception>
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