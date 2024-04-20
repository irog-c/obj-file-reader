cc = g++
source_dir = src
include_dir = include
object_dir = obj
bear = $(shell command -v bear 2> /dev/null)
flags = -O2 -Wall -Wextra -std=c++20 -I$(include_dir) -g
objects = $(object_dir)/main.o $(object_dir)/reader.o $(object_dir)/bfd_file_handler.o
exec = object-reader

$(exec): $(objects) | $(object_dir)
	$(cc) $(objects) -o $(exec) -lbfd

$(object_dir)/main.o: $(source_dir)/main.cpp $(include_dir)/reader.hpp | $(object_dir)
	$(cc) -c $(source_dir)/main.cpp $(flags) -o $@

$(object_dir)/reader.o: $(source_dir)/reader.cpp $(include_dir)/reader.hpp $(object_dir)/bfd_file_handler.o | $(object_dir)
	$(cc) -c $(source_dir)/reader.cpp $(flags) -o $@

$(object_dir)/bfd_file_handler.o: $(source_dir)/bfd_file_handler.cpp $(include_dir)/bfd_file_handler.hpp | $(object_dir)
	$(cc) -c $(source_dir)/bfd_file_handler.cpp $(flags) -o $@

$(object_dir):
	mkdir -p $(object_dir)

.PHONY: clean
clean:
	rm -f $(object_dir)/* $(exec) compile_commands.json

.PHONY: compile-commands
compile-commands:
ifdef bear
	bear -- make
endif

