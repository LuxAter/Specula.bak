
SHELL=/bin/bash
ifndef .VERBOSE
    .SILENT:
endif
ROOT=$(shell pwd)
ROOT=/home/arden/Programming/cpp/specula
CXX=clang++
CXXIGNORE=
CXXFLAGS=-std=c++17 -fPIC -Wall -Wpedantic --static -O3
LINK=-lpthread -lz
SOURCE=source
INCLUDE_DIR=include
INCLUDE=-I$(ROOT)/$(EXTERNAL)/estl -I$(ROOT)/$(BUILD)/libpng/include
BUILD=build
EXTERNAL=external
TEST=test
EXAMPLE=example
COMMON_INCLUDE=-I$(ROOT)/$(INCLUDE_DIR) $(INCLUDE)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[1;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C++ object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef

all: build-specula
clean: clean-specula
install: install-specula
uninstall: uninstall-specula

# SPECULA {{{

SPECULA=$(ROOT)/specula
SPECULA_FILES=source/main.cpp
SPECULA_OBJS=$(SPECULA_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(SPECULA_OBJS:.o=.d)

build-specula: build-libspecula.a pre-specula $(SPECULA)
	$(call complete_target,$(shell basename $(SPECULA)))

clean-specula:
	$(call clean_target,$(shell basename $(SPECULA)))
	if [ -e "$(SPECULA)" ]; then rm $(SPECULA); fi

pre-specula:
	$(call scan_target,$(shell basename $(SPECULA)))

$(SPECULA): $(SPECULA_OBJS) FORCE
	$(call print_link_exe,$(shell basename $(SPECULA)))
	$(CXX) $(SPECULA_OBJS) $(LIBSPECULA.A) $(LINK) $(COMMON_INCLUDE) -o $(SPECULA)

install-specula: build-specula
	$(call install_target,$(shell basename $(SPECULA)))
	mkdir -p $(INSTALL_PATH)/bin/
	cp $(SPECULA) $(INSTALL_PATH)/bin

uninstall-specula:
	$(call uninstall_target,$(shell basename $(SPECULA)))
	if [ -e "$(INSTALL_PATH)/bin/$(shell basename $(SPECULA))" ]; then rm $(INSTALL_PATH)/bin/$(shell basename $(SPECULA)); fi

# }}}
# LIBSPECULA.A {{{

LIBSPECULA.A=build/libspecula.a
LIBSPECULA.A_FILES=$(filter-out source/main.cpp, $(shell find "source/" -name "*.cpp"))
LIBSPECULA.A_OBJS=$(LIBSPECULA.A_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(LIBSPECULA.A_OBJS:.o=.d)

build-libspecula.a: build-libpng.a pre-libspecula.a $(LIBSPECULA.A)
	$(call complete_target,$(shell basename $(LIBSPECULA.A)))

clean-libspecula.a: clean-libpng.a
	$(call clean_target,$(shell basename $(LIBSPECULA.A)))
	if [ -e "$(LIBSPECULA.A)" ]; then rm $(LIBSPECULA.A); fi

pre-libspecula.a:
	$(call scan_target,$(shell basename $(LIBSPECULA.A)))

$(LIBSPECULA.A): $(LIBSPECULA.A_OBJS) FORCE
	$(call print_link_lib,$(shell basename $(LIBSPECULA.A)))
	ar rcs $@ $(LIBSPECULA.A_OBJS)
	mkdir -p $(ROOT)/tmp/libpng.a && cd $(ROOT)/tmp/libpng.a && ar x $(ROOT)/build/libpng.a/lib/libpng.a && ar qc $(ROOT)/$@ $(ROOT)/tmp/libpng.a/*.o && rm -rf $(ROOT)/tmp/libpng.a

install-libspecula.a: build-libspecula.a
	$(call install_target,$(shell basename $(LIBSPECULA.A)))
	mkdir -p $(INSTALL_PATH)/lib/
	mkdir -p $(INSTALL_PATH)/include/$(NAME)/
	cp $(LIBSPECULA.A) $(INSTALL_PATH)/lib
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.h") $(INSTALL_PATH)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.hpp") $(INSTALL_PATH)/include/$(NAME); fi

uninstall-libspecula.a:
	$(call uninstall_target,$(shell basename $(LIBSPECULA.A)))
	if [ ! -e "$(INSTALL_PATH)/lib/$(shell basename $(LIBSPECULA.A))" ]; then rm $(INSTALL_PATH)/lib/$(shell basename $(LIBSPECULA.A)); fi
	if [ ! -e "$(INSTALL_PATH)/include/$(NAME)" ]; then rm $(INSTALL_PATH)/include/$(NAME) -r; fi

# }}}
# LIBPNG.A {{{

build-libpng.a: pre-libpng.a
	if [ ! -f "external/libpng/configure" ]; then $(call print_run_cmd,autogen.sh) && cd external/libpng && ./autogen.sh; fi
	if [ ! -f "external/libpng/Makefile" ]; then $(call print_run_cmd,configure) && cd external/libpng && ./configure --prefix=$(ROOT)/build/libpng.a; fi
	if [ ! -d "$(ROOT)/build/libpng.a" ]; then $(call print_run_cmd,make) && cd external/libpng && make install; fi
	$(call complete_target,libpng.a)

clean-libpng.a:
	$(call clean_target,libpng.a)
	if [ -e "external/libpng/Makefile" ]; then cd external/libpng && make clean && rm Makefile; fi
	if [ -d "$(ROOT)/build/libpng.a" ]; then rm $(ROOT)/build/libpng.a -r; fi

pre-libpng.a:
	$(call scan_target,libpng.a)

# }}}

$(ROOT)/$(BUILD)/%.cpp.o: %.cpp
	$(call print_build_cpp,$@)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

$(ROOT)/$(BUILD)/%.c.o: %.c
	$(call print_build_c,$@)
	mkdir -p $(@D)
	$(CC) $(CCFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

FORCE:
