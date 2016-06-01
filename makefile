CC = clang
LD = clang

SHELL = bash

# Database drivers which need to be compiled
# Available drivers:
# - all (A)
# - mysql (M)
# - postgresql (P)
# - none (N)
DATABASE_DRIVER = "'A'"

MODULES = ai application building controller d
LDFLAGS = -lm -lz -lssl -lcrypto -lmysqlclient -lpthread -lstdc++ -ldl -lpqxx -o ias
CCFLAGS = -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -I"src/" \
		 -D IAS_DATABASE_DRIVER=$(DATABASE_DRIVER) \
 		 -I/usr/local/include/mysql \
		 -I/usr/include/mysql -O3 -Wno-vla-extension -Wno-vla -Wno-sign-conversion \
		 -Wno-global-constructors -Wno-float-equal -Wno-unused-parameter \
		 -Wno-padded -Wno-weak-vtables -Wno-c++98-compat -emit-llvm -Werror \
		 -Wno-exit-time-destructors -Wno-error-deprecated \
		 -Wall -c -fmessage-length=0 -std=c++11

SOURCEDIR = src/
BUILDDIR = build/

SOURCES = $(shell cd $(SOURCEDIR) && find ias/ -name "*.cpp" && cd ..)
OBJECTS = $(addprefix build/, $(SOURCES:.cpp=.bc))

NO_COLOR = \x1b[0m
YELLOW_COLOR = \x1b[33;01m
GREEN_COLOR = \x1b[32;01m
BOLD = \033[1m
NO_BOLD = \033[0m
OK_STRING = $(BOLD)$(GREEN_COLOR)[OK]$(NO_COLOR)$(NO_BOLD)
ARROW = $(YELLOW_COLOR)=>$(NO_COLOR)

.PHONY: all configuration update_binary
.DEFAULT: all

all: ias

ias: $(OBJECTS)
	@mkdir -p build
	@echo -e "$(ARROW) Linking bytecode."
	@$(LD) $(LDFLAGS) -o $@ $^
	@mkdir -p bin/
	@rm -f bin/ias
	@mv ias bin/ias
	@echo -e "$(BOLD)DONE$(NO_BOLD)"

build/%.bc: src/%.cpp
	@mkdir -p $(dir $(OBJECTS))
	@echo -en "$(ARROW) $(BOLD)Compiling:$(NO_BOLD) "$(word 2,$@ $<)
	@$(CC) $(CCFLAGS) -o $@ $<
	@echo -e " $(OK_STRING)"

clean:
	@rm -f -r build
	@rm -f -r bin

update_binary:
	@cp bin/ias /usr/bin/ias

configuration:
	@mkdir -p /etc/ias/configuration
	@cp -r configuration /etc/ias

install_service_files:
	@cp scripts/systemd/* /etc/systemd/system/

install:
	@make -s update_binary
	@make -s configuration
	@make -s install_service_files
