#include NAMES_INCLUDE
#include PCH_INCLUDE_PATH


#if MAIN_ENTRY


int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	
	return 0;
}



#elif TEST_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {

	
	return NULL;
}

int main() {
	// Prepare arguments for wWinMain
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	HINSTANCE hPrevInstance = nullptr;
	LPWSTR lpCmdLine = GetCommandLineW();
	int nShowCmd = SW_SHOW;

	// Call wWinMain
	return wWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

#elif DEMO_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {

	lol_blocks::main_window* window = new lb::main_window;
	HWND wh = window->handle();
	UINT width;
	UINT height;

	try {
		width = lba::get_window_width(wh);
		height = lba::get_window_height(wh);
	}
	catch (const lb::lolblock_error& e) {
		CERR << e.m_description << '\n';
		CERR << e.m_location;
		return static_cast<int>(lb::codes::exception_thrown_and_handled);
	}


	dx11::ss_demo* dx_demo = new dx11::ss_demo(wh, width, height);
	dx_demo->load_content();

	std::chrono::high_resolution_clock::time_point lastTime;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - lastTime).count();
			lastTime = now;

			dx_demo->update(deltaTime);
			dx_demo->render();
		}
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}

	if (dx_demo != nullptr) {
		delete dx_demo;
		dx_demo = nullptr;
	}

	// Demo Shutdown
	return static_cast<int>(msg.wParam);
}



#endif