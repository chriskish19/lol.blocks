#include "draw.hpp"

dx::draw::draw(UINT window_width, UINT window_height, HWND window_handle)
	:devices_11(window_width, window_height, window_handle)
{

}

errors::codes dx::draw::clear_buffer(float red, float green, float blue)
{
	const float color[] = {
		red,green,blue,1.0f
	};
	
	m_device_context_p->ClearRenderTargetView(m_render_target_p, color);
	
	return errors::codes::success;
}
