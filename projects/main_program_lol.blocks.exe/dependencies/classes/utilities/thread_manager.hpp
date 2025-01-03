#pragma once

// stl
#include "main_program_lol.blocks.exe/dependencies/stl/stl_macro_definitions.hpp"

// windows api
#include "main_program_lol.blocks.exe/dependencies/win32api/windows_includes.hpp"

// global variables
#include "main_program_lol.blocks.exe/dependencies/global/globals.hpp"

namespace utilities {
	
	class thread_master {
	public:
		thread_master() = default;
		~thread_master();

		// Wrapper to launch a thread
		template<typename FunctionType, typename... Args>
		std::jthread* launch_thread(FunctionType&& func, Args&&... args) noexcept {
			// Create a callable object using std::bind
			auto bound_func = std::bind(std::forward<FunctionType>(func), std::forward<Args>(args)...);

			// Wrap in std::function to match create_new_thread signature
			auto callable = std::function<void()>(bound_func);

			std::jthread* thread_obj = new std::jthread(callable);

			{
				std::unique_lock<std::mutex> local_lock(thread_mp_mtx);
				m_thread_p_id_mp.emplace(thread_obj->get_id(), thread_obj);
			}
			
			return thread_obj;
		}

		// Wrapper to launch the master thread
		template<typename FunctionType, typename... Args>
		std::jthread* launch_master_thread(FunctionType&& func, Args&&... args) noexcept {
			// Create a callable object using std::bind
			auto bound_func = std::bind(std::forward<FunctionType>(func), std::forward<Args>(args)...);

			// Wrap in std::function to match create_new_thread signature
			auto callable = std::function<void()>(bound_func);

			m_master_thread = new std::jthread(callable);
			m_master_thread_id = m_master_thread->get_id();
			return m_master_thread;
		}


		void join_all() noexcept {
			for (auto pair : m_thread_p_id_mp) {
				if (pair.second->joinable()) {
					pair.second->join();
				}
			}
		}

		void detach_all() {
			for (auto pair : m_thread_p_id_mp) {
				if (pair.second->joinable()) {
					pair.second->detach();
				}
			}
		}

		void join_one(std::thread::id ID) {
			auto found_thread = m_thread_p_id_mp.find(ID);
			if (found_thread != m_thread_p_id_mp.end()) {
				if (found_thread->second->joinable()) {
					found_thread->second->join();
				}
			}
		}

		void detach_one(std::thread::id ID) {
			auto found_thread = m_thread_p_id_mp.find(ID);
			if (found_thread != m_thread_p_id_mp.end()) {
				if (found_thread->second->joinable()) {
					found_thread->second->detach();
				}
			}
		}

		void join_master() noexcept {
			if (m_master_thread->joinable()) {
				m_master_thread->join();
			}
		}
	protected:
		std::mutex thread_mp_mtx;
		std::unordered_map < std::thread::id, std::jthread*> m_thread_p_id_mp = {};

		std::jthread* m_master_thread = nullptr;
		std::thread::id m_master_thread_id;
	};



	// singleton class
	class thread_manager {
	public:
		inline static thread_manager* create_thread_manager() {
			if (m_instance_threads == nullptr) {
				thread_manager* hello_threaders = new thread_manager();
				m_instance_threads = hello_threaders;
			}
			return m_instance_threads;
		}

		~thread_manager() {
			delete this;
		}

		// call this in main.cpp by main thread
		void thread_manager_main_thread_go() noexcept;
	private:
		thread_manager() = default;

		inline static thread_manager* m_instance_threads = nullptr;

		std::unordered_map < std::thread::id,std::thread*> m_thread_p_id_mp = {};
	};
}