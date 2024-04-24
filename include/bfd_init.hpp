#pragma once

#define PACKAGE "object-file-reader"
#define PACKAGE_VERSION "0.0.2"
#include <bfd.h>

static auto init_function = []() -> int {
	bfd_init();
	return 0;
}();
