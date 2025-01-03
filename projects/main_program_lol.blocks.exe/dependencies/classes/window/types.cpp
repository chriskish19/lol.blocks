#include "types.hpp"

windows_string::windows_string(const std::wstring& s) noexcept
:m_ws(s),m_lpcws(m_ws.c_str()){

}
