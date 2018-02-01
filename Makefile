SHELL  = /bin/bash

C      = /usr/bin/gcc
CC     = /usr/bin/g++

CFLAGS = -std=c++17

ORIGIN = .
BUILD  = $(ORIGIN)/build
SOURCE = $(ORIGIN)/source

SOURCEFILES  = $(shell find -type f -name "*.cpp")
OUTPUTFILES  = $(patsubst %.cpp, %.o, $(SOURCEFILES))

BINARY       = libthunder.a

FILESCHANGED = 0

all: $(BUILD)/$(BINARY)
	@[ $(FILESCHANGED) -eq 0 ] && echo -en "[\e[32mBUILD\e[0m] All files up-to-date\n" \
				   || echo -en ""

	@echo -en "[\e[32mBUILD\e[0m] Done\n"

$(BUILD)/$(BINARY): $(OUTPUTFILES)
	$(eval FILESCHANGED = 1)

	@echo -en "[\e[32mBUILD\e[0m] Compiling objects into \e[36m'"$(BUILD)/$(BINARY)"'\e[0m\n"
	@[ -f $(BUILD)/$(BINARY) ] && rm $(BUILD)/$(BINARY) || echo -en ""

	@echo -en "[\e[32mBUILD\e[0m] "
	ar -cvq $(BUILD)/$(BINARY) $(OUTPUTFILES)

%.o: %.cpp
	@echo -en "[\e[32mBUILD\e[0m]"
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(BUILD)/$(BINARY) $(OUTPUTFILES)

check:
	ar -t $(BUILD)/$(BINARY)
