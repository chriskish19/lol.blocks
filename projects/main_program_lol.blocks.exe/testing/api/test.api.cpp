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
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("log_window* log_p"));
    }
    if (p_draw == nullptr) {
        throw errors::pointer_is_nullptr(READ_ONLY_STRING("draw* p_draw"));
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
