#include "test.go.hpp"

errors::codes testing::go() {
	
	errors::codes code = string_conversions("test string!");
	if (code != errors::codes::success) {
		std::cout << "error when converting strings! test failed..." << '\n';
	}

	return errors::codes(code);
}