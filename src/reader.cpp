#include "reader.hpp"
#include "bfd_file_descriptor.hpp"

#include <iostream>
#include <sstream>

Reader::Reader(std::string_view file_path)
    : bfd_file_descriptor_(file_path)
{
	auto sections = bfd_file_descriptor_.get_all_sections();
	auto symbols = bfd_file_descriptor_.get_all_symbols();
	auto ss = std::stringstream();

	ss << "Architecture: " << bfd_file_descriptor_.get_architecture_type() << '\n';
	ss << "Size: " << bfd_file_descriptor_.get_object_file_size() << '\n';
	ss << "List of sections:\n";
	for (const auto& section_name : sections) {
		ss << '\t' << section_name << '\n';
	}

	ss << "List of symbols:\n";
	for (const auto& symbol_name : symbols) {
		ss << '\t' << symbol_name << '\n';
	}

	file_info_ = ss.str();
}

auto Reader::object_file_info() const -> std::string
{
	return file_info_;
}
