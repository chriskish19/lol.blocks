#include "dependencies/include/win32gui_dependencies_include.hpp"

#ifndef WIN32_GUI_GROUND_HPP
#define WIN32_GUI_GROUND_HPP

// Basic functionality for controling the gui elements and adding them to a window

namespace win32gui {
	HWND create_textbox(HWND parent_window, unsigned int x, unsigned int y, std::wstring message);
	HWND create_menu_bar(HWND this_window, unsigned int x, std::filesystem::path menu_bar_path);

}



// WIN32_GUI_GROUND_HPP
#endif