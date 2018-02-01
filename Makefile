SHELL  = /bin/bash

C      = /usr/bin/gcc
CC     = /usr/bin/g++

CFLAGS = -std=c++17
OFLAGS = $(CFLAGS) -lSDL2 -lGL -lGLEW

ORIGIN = .
BUILD  = $(ORIGIN)/build
SOURCE = $(ORIGIN)/source

SOURCEFILES = $(shell find -type f -name "*.cpp")
OUTPUTFILES = $(patsubst %.cpp, %.o, $(SOURCEFILES))

BINARY      = libthunder.a

all: $(OUTPUTFILES) $(BINARY)
	@echo -en "[\e[32mBUILD\e[0m] Done\n"

$(BINARY):
	@echo -en "[\e[32mBUILD\e[0m] Compiling objects into \e[36m'"$(BUILD)/$(BINARY)"'\e[0m\n"
	@[ -f $(BUILD)/$(BINARY) ] && rm $(BUILD)/$(BINARY) || echo -en ""
	@echo -en "[\e[32mBUILD\e[0m] "
	ar -cvq $(BUILD)/$(BINARY) $(OUTPUTFILES)
