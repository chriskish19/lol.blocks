#include "test.api.hpp"

void testing::handle_basic_error_codes(errors::codes code, const string& location) noexcept
{
    switch (code) {
    case errors::codes::success:
    {
        COUT << errors_cstr::success << ROS('\n');
        COUT << location << ROS('\n');
        break;
    }

    case errors::codes::division_by_zero:
    {
        COUT << errors_cstr::division_by_zero << ROS("\n");
        COUT << location << ROS("\n");

        break;
    }

    // add the rest

    default:
        COUT << ROS("code not found... \n");
    }
}

errors::codes testing::create_windows(size_t number_of_open_windows)
{
    window_t* local_window_test = new window_t;
    local_window_test->go();

    COUT << ROS("running window test...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("3\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("2\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("1\n");

    local_window_test->create_windows(number_of_open_windows);
    COUT << ROS("running window test...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("3\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("2\n");
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    COUT << ROS("1\n");

    local_window_test->close_windows();

    local_window_test->join_master();

    if (local_window_test != nullptr) {
        delete local_window_test;
    }


	return errors::codes(errors::codes::success);
}

errors::codes testing::draw_shapes(draw* p_draw, window::log_window* log_p)
{
    utilities::timer game_time;

#if ENABLE_ALL_EXCEPTIONS
    if (log_p == nullptr) {
        code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
        throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("log_window* log_p"));
    }
    if (p_draw == nullptr) {
        code_error_objs::code_obj error(code_error_objs::pointer_is_nullptr);
        throw errors::pointer_is_nullptr(error,READ_ONLY_STRING("draw* p_draw"));
    }
#endif

    p_draw->ready_triangle();


    while (true) {

        const float c = std::sin(game_time.peek()) / 2.0f + 0.5f;
        p_draw->clear_buffer(c, c, 1.0f);

        p_draw->render_triangle();
    }
	
	
	return errors::codes();
}

errors::codes testing::string_conversions(const std::string& narrow_test)
{
    std::wstring wide = utilities::to_wide_string(narrow_test);

    std::string narrow = utilities::to_narrow_string(wide);

    if (narrow != narrow_test) {
        return errors::codes::strings_not_equal;
    }
    
    return errors::codes::success;
}

errors::codes testing::string_conversions_file(const std::filesystem::path& p)
{
    utilities::file_manager fm(p);
    errors::codes error_code = fm.open();
    
    if (error_code != errors::codes::success) {
        testing::handle_basic_error_codes(error_code);
        return error_code;
    }

    string file_data = fm.file_data_to_string();

    std::string narrow = utilities::to_narrow_string(file_data);

    std::wstring wide = utilities::to_wide_string(narrow);

    if (file_data != wide) {
        return errors::codes::strings_not_equal;
    }

    
    return errors::codes(errors::codes::success);
}

errors::codes testing::window_logger()
{
    window::system_log_window local_log_window;
    std::thread lg_window_thread(&window::system_log_window::go, &local_log_window);
    
    // will need a signaller instead of this jank
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // we need to wait until lg_window_thread has initialized or we wreck stuff
    local_log_window.add_x_log_window();


    // spam it with messages
    std::filesystem::path exe_path = std::filesystem::current_path();
    utilities::file_manager fm(exe_path / "test_files/string.txt"); // a file with lots of code in it

    errors::codes code = fm.open();
    testing::handle_basic_error_codes(code);

    // get the all the code into a string
    string data = fm.file_data_to_string();

    // so janky here
    auto atomic_log_p = local_log_window.get_logs_p();
    auto logs_p = atomic_log_p->load();
    auto bl_log_p = logs_p->get_base_logger_p_by_index();
    auto log_message_p = bl_log_p->get_message_p();
    auto time_message_p = bl_log_p->get_time_p();

    std::size_t message_length = log_message_p->reserved_length_mem_heap - time_message_p->reserved_length_heap_mem;

    std::size_t last_index = 0;
    for (std::size_t i = 0; i < data.size()-message_length; i+=message_length) {
        string single_log_message(data, i, message_length);
        logs_p->log_message(single_log_message);
        last_index = i;
        local_log_window.update();
    }
    
    // get the last message, there would be overlap in the 2nd last message and the last but this
    // is a test so it doesnt matter about displaying anything important or readable
    string last_log_message(data, last_index, std::string::npos);
    logs_p->log_message(last_log_message);
    local_log_window.update();


    if (lg_window_thread.joinable()) {
        lg_window_thread.join();
    }
    
    

    return errors::codes(errors::codes::success);
}
