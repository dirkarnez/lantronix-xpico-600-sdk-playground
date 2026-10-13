# vim:tabstop=4:shiftwidth=4:softtabstop=0:noexpandtab

export HOST_PLATFORM := $(shell uname)
ifeq ($(filter MINGW% MSYS2% MSYS_NT% Linux,$(HOST_PLATFORM)),)
$(error This platform is not supported: $(HOST_PLATFORM))
else
$(info Building on host platform $(HOST_PLATFORM))
endif

#
# Pick up command line args & defaults for build debug/log options
#
ocd_logfile := $(ocd_logpath)/.ocd.log
ocd_dbg :=
quiet_q :=-qq
veryquiet :=@
ifneq ($(VERBOSE),)
quiet :=
output :=
ifeq ($(VERBOSE),2)
ocd_dbg :=-d2
quiet_q :=-q
else ifeq ($(VERBOSE),3)
ocd_dbg :=-d3
quiet_q :=
veryquiet :=
endif
else
quiet :=@
output := > $(ocd_logfile) 2>&1
endif

ifneq ($(OCDLOG),)
ocd_loglevel := $(OCDLOG)
else
ocd_loglevel := 0
endif

#
# define normalize_path based on environment.
#
define normalize_path
$(abspath $(1))
endef

PROJECT_NAME := $(notdir $(abspath .))
PROJECT_ROOT_DIRECTORY := $(call normalize_path,../../..)

BASE_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/custom
WORK_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/work
ifeq ($(HOST_PLATFORM),Linux)
BASE_NORMALIZED_DIRECTORY := $(BASE_DIRECTORY)
WORK_NORMALIZED_DIRECTORY := $(WORK_DIRECTORY)
else
BASE_NORMALIZED_DIRECTORY := $(shell [ -d $(BASE_DIRECTORY) ] && cd $(BASE_DIRECTORY) && pwd -W)
WORK_NORMALIZED_DIRECTORY := $(shell [ -d $(WORK_DIRECTORY) ] && cd $(WORK_DIRECTORY) && pwd -W)
endif

ENV_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/env
RULES_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/rules
LANTRONIX_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/lantronix
PROJECT_DIRECTORY := $(PROJECT_ROOT_DIRECTORY)/build
LD_DIRECTORY := $(LANTRONIX_DIRECTORY)
GENERATED_TOOLS_DIRECTORY = $(LANTRONIX_DIRECTORY)/bin
ROMIMAGE_DIRECTORY := $(GENERATED_TOOLS_DIRECTORY)/$(ROMIMAGE_REPO)

TARGET_NAME = $(PROJECT_NAME)_$(TARGET_VERSION)

export PROJECT_INCLUDES = \
    $(LANTRONIX_DIRECTORY)/includes/system \
    $(LANTRONIX_DIRECTORY)/includes \
    $(BASE_DIRECTORY)/includes \
    $(WORK_DIRECTORY)/$(PROJECT_NAME)/lantronix/includes \
    $(WORK_DIRECTORY)/$(PROJECT_NAME)/includes \

#
# define tools based on environment.
#
ifneq ($(filter CYGWIN% MINGW% MSYS% Linux,$(HOST_PLATFORM)),)
TOOLCHAIN_BASE_DIR := $(PROJECT_ROOT_DIRECTORY)/toolchain/gcc-arm-none-eabi
TOOLCHAIN_BIN_DIR := $(TOOLCHAIN_BASE_DIR)/bin
GCC_VERSION := $(shell $(TOOLCHAIN_BIN_DIR)/arm-none-eabi-gcc -dumpversion)
TOOLCHAIN_INC_DIR := $(TOOLCHAIN_BASE_DIR)/arm-none-eabi/include
TOOLCHAIN_LIB_INC_DIR := $(TOOLCHAIN_BASE_DIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include
TOOLCHAIN_LIB_INC_FIXED_DIR := $(TOOLCHAIN_BASE_DIR)/lib/gcc/arm-none-eabi/$(GCC_VERSION)/include-fixed
MKDIR := mkdir
else

endif

SHORTENED_NAME = $(patsubst $(PROJECT_ROOT_DIRECTORY)/%,%,$(1))

MANGLE = $(subst /,__,$(subst ..,up,$(call SHORTENED_NAME,$(1))))

VARDEF_NUMBER_RANGE_FLAGS := \
  VARDEF_NUMBER_RANGE_MAX=59999 \
  VARDEF_NUMBER_RANGE_MIN=50000 \

SYSTEM_INCLUDES := \
  $(TOOLCHAIN_INC_DIR) \
  $(TOOLCHAIN_LIB_INC_DIR) \
  $(TOOLCHAIN_LIB_INC_FIXED_DIR) \

PROJECT_DIRECTORIES := \
  lantronix/bin \
  lantronix/includes/system \
  VisualStudio \

ifeq ($(HOST_PLATFORM),Linux)
MKIMAGE := $(LANTRONIX_DIRECTORY)/bin/ltrx-mkimage-linux64
else
MKIMAGE := $(LANTRONIX_DIRECTORY)/bin/ltrx-mkimage-win64.exe
endif

export MKIMAGE

LANTRONIX_MODULE_NAMES := $(basename $(notdir $(wildcard $(LANTRONIX_DIRECTORY)/modules/*.elf)))

define LANTRONIX_ELF_COPY_template

$(WORK_DIRECTORY)/$(PROJECT_NAME)/lantronix/modules/$(notdir $(1)): $(1)
	@echo $$(notdir $$@)
	@$(MKDIR) -p $$(dir $$@)
	@cp -f $$< $$@

endef

$(foreach MODULE,$(LANTRONIX_MODULE_NAMES),$(eval $(call LANTRONIX_ELF_COPY_template,$(LANTRONIX_DIRECTORY)/modules/$(MODULE).elf)))
