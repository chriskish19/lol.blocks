#include "test.api.hpp"

errors::codes testing::create_number_of_windows(size_t number_of_open_windows)
{
	window::window_class_mt* local_windows = new window::window_class_mt;
	local_windows->go();
	
	
	return errors::codes();
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
