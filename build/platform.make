
PRODUCT_ID := Z7

#ifneq ($(HOST_PLATFORM),Linux)
#USE_ECLIPSE := true
#endif

INSTALL_ADDRESS_CFG := 0x0801C000
PARTITION_SIZE := 0x00600000
FLASH_END_ADDRESS := 0x09000000
INSTALL_ADDRESS_FW := 0x08040000
STAGING_ADDRESS_FW := $(shell printf 0x%X $$((($(INSTALL_ADDRESS_FW)+$(FLASH_END_ADDRESS))/2)))

ENTRY_POINT_OFFSET = $(call SYMBOL_VALUE,$(LANTRONIX_DIRECTORY)/modules/main.symbols.elf,ltrx_linker_module_main_data_offset)

export BSP_DIRECTORY_NAME := RW610

TARGET_VERSION = $(LANTRONIX_VERSION).$(SDK_VERSION)

include ../../../env/env.make
ifneq ($(HOST_PLATFORM),Linux)
include ../../../build/jtag.make
endif
include $(LANTRONIX_DIRECTORY)/version.make
include $(LANTRONIX_DIRECTORY)/defines.make
include ../../../rules/common.make
#include ../../../build/eclipse.make

CFLAGS += \
  -O0 -g3 \
  -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb \
  -ffreestanding \
  -fno-builtin \
  -fmerge-constants \
  -fmacro-prefix-map="$(<D)/"= \
  -fstack-usage \
  -D_DEFAULT_SOURCE \
  -D_XOPEN_SOURCE=700 \

ASMFLAGS += \
  -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb

LDFLAGS += \
  -nostdlib \
  -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb \

USAGE_MESSAGE = $$(($(1))) of $$(($(2))) ($$((($(1))*100/($(2))))%, $$((($(2))-($(1)))) remaining)

.PHONY: create_work_directory

create_work_directory:
	@echo $(notdir $@)
	$(quiet)$(MKDIR) -p $(WORK_DIRECTORY)/$(PROJECT_NAME)
