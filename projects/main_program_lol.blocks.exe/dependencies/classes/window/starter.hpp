#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

namespace window {
	// abstract class
	class foundation {
	public:
		foundation() = default;
	protected:
		virtual static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual LRESULT CALLBACK ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		virtual void window_settings() = 0;


		HWND m_window_handle = nullptr;
		HINSTANCE m_hinst = GetModuleHandle(NULL);
		std::wstring c_name = L"foundation";
	};
	
	
	
	class starter {
	public:
		starter() = default;

		starter(const std::wstring& class_name);

	private:


	};
}