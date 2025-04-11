#include NAMES_INCLUDE
#include UI_INCLUDE_PATH

lol_blocks::main_window::main_window() {

	// register class
	m_register_code = register_window(m_wc);

	// create the window
	m_handle = create_window(m_wd);

	if (m_handle == nullptr) {
		m_hwnd_code = codes::HWND_error;
	}
	else {
		ShowWindow(m_handle, SW_SHOW);
	}

}

std::vector<lol_blocks::codes> lol_blocks::main_window::get_codes() {
	std::vector<codes> code_v;
	
	if (m_register_code != codes::success) {
		code_v.push_back(m_register_code);
	}

	if (m_hwnd_code != codes::success) {
		code_v.push_back(m_hwnd_code);
	}

	return code_v;
}