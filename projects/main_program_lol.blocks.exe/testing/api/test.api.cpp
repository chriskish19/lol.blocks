#include "test.api.hpp"

void testing::handle_basic_error_codes(errors::codes code, const string& location) noexcept
{
    using namespace errors;

    switch (code) {
    case codes::success:
    {
#if USING_NARROW_STRINGS
        std::cout << errors_cstr::success << "\n";
        std::cout << location << "\n";
#endif

#if USING_WIDE_STRINGS
        std::wcout << errors_cstr::success << "\n";
        std::wcout << location << "\n";
#endif
        break;
    }

    case codes::division_by_zero:
    {
#if USING_NARROW_STRINGS
        std::cout << errors_cstr::division_by_zero << "\n";
        std::cout << location << "\n";
#endif

#if USING_WIDE_STRINGS
        std::wcout << errors_cstr::division_by_zero << "\n";
        std::wcout << location << "\n";
#endif
        break;
    }

    // add the rest

    default:
        std::cout << "code not found... \n";
    }
}

errors::codes testing::create_windows(size_t number_of_open_windows)
{
    window_t* local_window_test = new window_t;
    local_window_test->go();

    std::cout << "running window test...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "3\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "1\n";

    local_window_test->create_windows(number_of_open_windows);
    std::cout << "running window test...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "3\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    std::cout << "1\n";

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

    std::string file_data = fm.file_data_to_string();

    std::wstring wide = utilities::to_wide_string(file_data);

    std::string narrow = utilities::to_narrow_string(wide);

    if (file_data != narrow) {
        return errors::codes::strings_not_equal;
    }

    
    return errors::codes(errors::codes::success);
}
