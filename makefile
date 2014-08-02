CC = clang
LD = clang

MODULES = ai application building controller d
LDFLAGS = -lm -lz -lssl -lcrypto -lmysqlclient -lpthread -lstdc++ -ldl
CCFLAGS = -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -I"src/" -I/usr/include/eigen3 -I/usr/include/mysql -O3 -emit-llvm -w -Wall -Werror -c -fmessage-length=0 -std=c++11

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
	
install:
	@mv bin/ias /usr/bin/ias
	
configuration:
	@mkdir -p /etc/ias/configuration
	@touch /etc/ias/configuration/server
	@touch /etc/ias/configuration/controller
	@touch /etc/ias/configuration/controller_devices