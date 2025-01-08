#include "types.hpp"

windows_string::windows_string(const std::wstring& s) noexcept
:m_ws(new std::wstring(s)),m_lpcws(m_ws->c_str()){

}

windows_string::~windows_string()
{
	if (m_ws) {
		delete m_ws;
	}
}
