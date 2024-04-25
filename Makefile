CXX           = g++
INCLUDE_DIR   = include
CXXFLAGS      = -O2 -Wall -Wextra -std=c++20 -I$(INCLUDE_DIR)
OUTPUT_OPTION = -MMD -MP -o $@ 

SOURCE = $(wildcard src/*.cpp)
OBJS   = $(SOURCE:.cpp=.o)
DEPS   = $(SOURCE:.cpp=.d)

all: object-reader

object-reader: $(OBJS)
	$(CXX) -o object-reader $(OBJS) -lbfd

.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f object-reader

.phony: compile-commands
compile-commands:
	bear --output compile_commands.json --append -- make
-include $(DEPS)

