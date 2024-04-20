#pragma once
#include <cstddef>
#define PACKAGE "object-file-reader"
#define PACKAGE_VERSION "0.0.1"
#include <bfd.h>

#include <memory>
#include <string_view>
#include <vector>

class BFDFileDescriptor {
    public:
	explicit BFDFileDescriptor(std::string_view file_path);
	auto get_architecture_type() const -> std::string;
	auto get_object_file_size() const -> std::size_t;
	auto get_all_sections() const -> std::vector<std::string>;
	auto get_all_symbols() const -> std::vector<std::string>;

    private:
	static auto close_file(bfd* abfd) -> void
	{
		if (abfd != nullptr) {
			bfd_close(abfd);
		}
	}
	using file_ptr_t = std::unique_ptr<bfd, decltype(&close_file)>;
	file_ptr_t file_ptr_;
};
