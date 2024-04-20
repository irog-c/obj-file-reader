#pragma once

#include "bfd_file_handler.hpp"
#include <string_view>

class Reader {
    public:
	Reader() = delete;
	explicit Reader(std::string_view file_name);

	auto object_file_info(void) const -> std::string;

    private:
	BFDFileHandler bfd_file_handler_;
	std::string file_info_;
};
