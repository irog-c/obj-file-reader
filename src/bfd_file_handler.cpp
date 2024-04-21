#include "bfd_file_handler.hpp"
#include "bfd_init.hpp"

#include <bitset>
#include <errno.h>
#include <stdexcept>
#include <string>

static auto close_file(bfd* abfd) -> void
{
	if (abfd != nullptr) {
		bfd_close(abfd);
	}
}

static auto get_symbol_type(const flagword flags) -> std::string
{
	std::string result;

	if (flags & BSF_LOCAL) {
		result += "local";
		result += " ";
	}
	if (flags & BSF_GLOBAL) {
		result += "global";
		result += " ";
	}
	if (flags & BSF_FUNCTION) {
		result += "function";
		result += " ";
	}
	if (flags & BSF_OBJECT) {
		result += "object";
		result += " ";
	}
	if (flags & BSF_DEBUGGING) {
		result += "debugging";
		result += " ";
	}
	if (flags & BSF_WEAK) {
		result += "weak";
		result += " ";
	}
	if (flags & BSF_WARNING) {
		result += "warning";
		result += " ";
	}
	if (flags & BSF_SECTION_SYM) {
		result += "section";
		result += " ";
	}
	if (flags & BSF_INDIRECT) {
		result += "indirect";
		result += " ";
	}
	if (flags & BSF_KEEP) {
		result += "keep";
		result += " ";
	}

	if (!result.empty()) {
		result.pop_back();
	}

	if (result.empty())
		return "unknown";
	else
		return result;
}

static auto is_defined_symbol(asymbol* symbol) -> bool
{
	const auto symbol_section = bfd_asymbol_section(symbol);
	return symbol_section != bfd_und_section_ptr and symbol_section != bfd_com_section_ptr;
}

BFDFileHandler::BFDFileHandler(std::string_view file_path)
    : file_ptr_(nullptr, &close_file)
{
	bfd_init();
	file_ptr_t abfd(bfd_openr(file_path.data(), nullptr), &close_file);
	if (abfd == nullptr) {
		if (errno == ENOENT) {
			throw std::runtime_error("Failed opening file with bfd, file does not exist");
		}

		throw std::runtime_error("Failed opening file with bfd");
	}

	if (not bfd_check_format(abfd.get(), bfd_object)) {
		throw std::runtime_error("Incorrect file format");
	}

	file_ptr_ = std::move(abfd);
}

auto BFDFileHandler::get_architecture_type() const -> std::string
{
	return std::string(bfd_printable_name(file_ptr_.get()));
}

auto BFDFileHandler::get_object_file_size() const -> std::size_t
{
	return bfd_get_file_size(file_ptr_.get());
}

auto BFDFileHandler::get_all_sections() const -> std::vector<std::string>
{
	auto sections = std::vector<std::string>();
	bfd_map_over_sections(
	    file_ptr_.get(), +[](bfd*, asection* section, void* obj) {
		    auto sections_ptr = static_cast<std::vector<std::string>*>(obj);
		    if (section) {
			    sections_ptr->push_back(bfd_section_name(section));
		    }
	    },
	    &sections);

	return sections;
}

auto BFDFileHandler::get_all_symbols() const -> std::vector<std::string>
{
	auto size = bfd_get_symtab_upper_bound(file_ptr_.get());
	auto symbol_table = std::make_unique<asymbol*[]>(size);
	auto number_of_symbols = bfd_canonicalize_symtab(file_ptr_.get(), symbol_table.get());
	if (number_of_symbols < 0) {
		throw std::runtime_error("Failed to canonicalize symtab");
	}

	auto symbols = std::vector<std::string>(number_of_symbols);
	for (int i = 0; i < number_of_symbols; ++i) {
		auto flags = symbol_table[i]->flags;
		auto symbol_type = [symbol = symbol_table[i], &flags]() -> std::string {
			if (is_defined_symbol(symbol))
				return get_symbol_type(flags);

			return "undefined";
		}();
		auto flags_str = std::bitset<sizeof(flagword) * 8>(flags).to_string();
		symbols[i] = "[" + symbol_type + "] " + "[flags: " + flags_str + "] " + bfd_asymbol_name(symbol_table[i]);
	}

	return symbols;
}
