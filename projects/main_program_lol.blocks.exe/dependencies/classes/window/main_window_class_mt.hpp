#ifndef WINDOW_CLASS_MT_HPP
#define WINDOW_CLASS_MT_HPP

// include win32gui
#include "win32gui.include/win32gui.include.hpp"

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// class dependencies
#include "main_program_lol.blocks.exe/dependencies/classes/window/main_window_class.hpp"
#include "main_program_lol.blocks.exe/dependencies/classes/utilities/thread_manager.hpp"

namespace main_lol_blocks_exe {
	extern std::condition_variable* m_public_safe_exit;
	extern std::atomic<bool>* m_public_safe_exit_gate_latch;


	// singleton class
	class window_class_mt: 
		public utilities::thread_master, 
		public window_relative{

	public:
		inline static window_class_mt* create_window_class_mt_instance() {
			if (m_window_class_mt_instance == nullptr) {
				window_class_mt* hello_window_class_mt = new window_class_mt();
				m_window_class_mt_instance = hello_window_class_mt;
			}
			return m_window_class_mt_instance;
		}

		~window_class_mt() {
			if (m_thread_runner != nullptr) {
				delete m_thread_runner;
			}
		}
		
		


	private:
		window_class_mt() = default;


		inline static window_class_mt* m_window_class_mt_instance = nullptr;
		
		class run_windows_class_mt : public utilities::thread_master {
		public:
			inline void threads_go(){
				// launch a first thread window
				this->launch_thread(&window_manager::windows_message_handler, m_wm);

				// creates new windows on thread_master
				this->launch_thread(&run_windows_class_mt::new_window_gate, this);
				
				// exit program thread
				all_windows_closed_gate();
			}

			void all_windows_closed_gate() noexcept {
				std::mutex local_mtx;
				std::unique_lock<std::mutex> local_lock(local_mtx);
				m_wm->m_public_all_windows_closed_signaler.wait(local_lock, [this]
					{
						return m_wm->m_all_windows_closed_gate_latch.load();
					});

				// begin to exit the program
				m_exit_new_window_gate.store(true);
				m_public_new_window_gate_latch->store(true);
				m_public_window_create_signaler->notify_all();  // get the thread moving again if its stalled
			}

			void new_window_gate() noexcept {
				while (m_exit_new_window_gate.load() == false) {
					std::mutex local_mtx;
					std::unique_lock<std::mutex> local_lock(local_mtx);
					m_public_window_create_signaler->wait(local_lock, []
						{
							return m_public_new_window_gate_latch->load();
						});
					m_public_new_window_gate_latch->store(false);
					
					// duble check were not in a exit scenario
					if (m_exit_new_window_gate.load() == false) {
						this->launch_thread(&window_manager::windows_message_handler, m_wm);
					}
				}

				m_public_safe_exit_gate_latch->store(true);
				m_public_safe_exit->notify_all();
			}
		private:
			std::atomic<bool> m_exit_new_window_gate = false;
			window_manager* m_wm = window_manager::get_me_a_window_create_p();
		};

		run_windows_class_mt* m_thread_runner = new run_windows_class_mt;

	public:
		// call this function with actual system main thread
		inline void go() {
			// this-> is actually on a different instance of master_thread than run_windows_class_mt's instance
			this->launch_master_thread(&run_windows_class_mt::threads_go, m_thread_runner);
		}
	};
}

// WINDOW_CLASS_MT_HPP
#endif