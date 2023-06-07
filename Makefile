CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

# flags for preprocessor
CPPFLAGS =

OBJECTS = rational.o utest.o

all: utest

utest : $(OBJECTS)

clean:
	@$(RM) utest $(OBJECTS)

clear:
	clear

test: all clear
	./utest && echo "\e[32;40mPass\e[0m" || echo "\e[31;40mFailed $? times\e[0m"


.PHONY: clean all clear test


# dependencies
rational.o: rational.hpp
utest.o: rational.hpp
