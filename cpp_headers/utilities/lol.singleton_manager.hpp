#pragma once


class singleton_manager {
public:
	static singleton_manager* get_singleton_manager() noexcept;

	~singleton_manager();
private:
	void create_singleton_manager_instance() noexcept;

	singleton_manager() = default;

	inline static singleton_manager* private_singleton_manager_instance_p = nullptr;

	// create singleton objects here
	// 
};