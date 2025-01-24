#include "timer.hpp"

UINT utilities::timer::milliseconds()
{
	auto start = std::chrono::system_clock::now();
	interval();
	if (m_interval_check == true) {
		auto end = std::chrono::system_clock::now();
		// Calculate the difference
		auto duration = end - start;
		auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		m_delta_ms = (UINT)duration_milliseconds;
		return (UINT)duration_milliseconds;
	}
	return m_delta_ms;
}

void utilities::timer::interval()
{
	if (m_interval_check == false) {
		m_interval_check = true;
	}
	else {
		m_interval_check = false;
	}
}
