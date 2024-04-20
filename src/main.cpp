#include "reader.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

auto main(const int argc, const char* argv[]) -> int
{
	if (argc < 2) {
		std::cerr << "Bad arguments\n";
		return EXIT_FAILURE;
	}

	auto file_name = std::string(argv[1]);
	std::unique_ptr<Reader> reader;
	try {
		reader = std::make_unique<Reader>(file_name);
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	std::cout << "File info: " << reader->object_file_info() << '\n';
	return EXIT_SUCCESS;
}
