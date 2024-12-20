// private header which defines exception handling in lol.blocks

#ifndef LOL_BLOCKS_EXCEPTIONS_HEADER_HPP
#define LOL_BLOCKS_EXCEPTIONS_HEADER_HPP

namespace utilities {
	class lol_base_exception : public std::exception, public virtual log_info {
	public:
		lol_base_exception() = default;
	protected:
		virtual const char* what() noexcept {
			return "lol base exception thrown!";
		}
	};

	class win32_window_error_exception : public lol_base_exception {
	public:
		win32_window_error_exception() = default;

		win32_window_error_exception(std::initializer_list<lolblock_ec::codes> error_codes) {}


	private:


	};

	class win32_general_error : public lol_base_exception {
	public:


	private:

	};

	// complex but very useful for catching and handling all functions throughtout lol.blocks
	template<typename function_return_type, typename ... function_arguments_types>
	inline auto handle_exceptions(
		std::function<function_return_type(function_arguments_types ...)> function_that_may_throw,
		function_arguments_types ... individual_arguments) {


		try {
			return function_that_may_throw(individual_arguments ...);
		}
		catch (const std::logic_error& e) {

		}
		catch (const std::runtime_error& e) {

		}
		catch (const win32_window_error_exception& e) {

		}
		catch (const win32_general_error& e) {

		}
		catch (const lol_base_exception& e) {

		}
		catch (const std::exception& e) {

		}
	}
}



#endif