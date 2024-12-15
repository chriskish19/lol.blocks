// Private header for singletons class

#ifndef LOL_BLOCKS_SINGLETONS_HEADER_HPP
#define LOL_BLOCKS_SINGLETONS_HEADER_HPP

class singleton_manager {
public:
	static singleton_manager* get_singleton_manager() noexcept;

	~singleton_manager();
private:
	static void create_singleton_manager_instance() noexcept;

	singleton_manager() = default;

	inline static singleton_manager* private_inline_static_singleton_manager_instance_p = nullptr;

};

// LOL_BLOCKS_SINGLETONS_HEADER_HPP
#endif