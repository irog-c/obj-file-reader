#pragma once

#include <memory>
#include <string_view>
#include <vector>
#include <functional>

using bfd = struct bfd;

class BFDFileHandler {
    public:
	explicit BFDFileHandler(std::string_view file_path);

	auto get_architecture_type() const -> std::string;
	auto get_object_file_size() const -> std::size_t;
	auto get_all_sections() const -> std::vector<std::string>;
	auto get_all_symbols() const -> std::vector<std::string>;

    private:	
	using file_ptr_t = std::unique_ptr<bfd, std::function<void(bfd*)>>;
	file_ptr_t file_ptr_;
};
