#pragma once

#include "bfd_file_descriptor.hpp"
#include <string_view>

class Reader {
    public:
	Reader() = delete;
	explicit Reader(std::string_view file_name);

	auto object_file_info(void) const -> std::string;

    private:
	BFDFileDescriptor bfd_file_descriptor_;
	std::string file_info_;
};
