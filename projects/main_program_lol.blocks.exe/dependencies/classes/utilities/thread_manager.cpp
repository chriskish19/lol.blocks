#include "thread_manager.hpp"

void utilities::thread_manager::thread_manager_main_thread_go() noexcept
{
	// all threads build them herare
	//..............................
	// launch the any logic code here
	

	// then have main thread wait here.....

	// use a function to return a thread id, the one that needs to be killed!

	// then a while loop that handles killing of threads
}

utilities::thread_master::~thread_master()
{
	for (auto pair : m_thread_p_id_mp) {
		std::jthread* t = pair.second;
		if (t != nullptr) {
			delete t;
		}
	}

	if (m_master_thread != nullptr) {
		delete m_master_thread;
	}
}
