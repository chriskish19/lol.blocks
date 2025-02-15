#include "go.hpp"

errors::any_two<errors::codes,errors::win32_codes> main::go() {
	// global logging window messages throughout whole program
	auto log_window_p = global::system_global_manager_p->get_atomicwrapped_system_log_window_p();
	std::thread lw_thread(&window::log_window::go, log_window_p->load());

	// main window class
	window::window_class_mt* local_window_mt_system_p = new window::window_class_mt;
	local_window_mt_system_p->go();


	// waits until all display windows are closed
	local_window_mt_system_p->wait();
	log_window_p->load()->set_all_display_windows_closed(true);
	auto all_display_windows_closed = global::system_global_manager_p->get_display_windows_closed_p();
	all_display_windows_closed->store(log_window_p->load()->get_all_display_windows_closed());
	log_window_p->load()->add_x_log_window();
	if (local_window_mt_system_p != nullptr) {
		delete local_window_mt_system_p;
		local_window_mt_system_p = nullptr;
	}

	// a message sent to the system log window
	global::system_global_manager_p->
		log_to_system_log_window(READ_ONLY_STRING("All display windows closed. Close this window to exit program."));

	// system log window can stay open to show possible errors
	if (lw_thread.joinable()) {
		lw_thread.join();
	}

	// the return values of the functions in here need some error checking
	return errors::any_two<errors::codes, errors::win32_codes>(errors::codes::success, errors::win32_codes::success);
}

errors::any_two<errors::codes,errors::win32_codes> main::draw()
{
	
	
	
	
	return errors::any_two<errors::codes, errors::win32_codes>(errors::codes::success, errors::win32_codes::success);
}

void main::shutdown()
{
	// delete global pointer
	global::system_global_manager_p.reset();

	// deletes error handling
	code_error_objs::clean_up();
	win32_code_objs::clean_up();

}
