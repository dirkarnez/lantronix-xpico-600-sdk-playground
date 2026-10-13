# vim:tabstop=4:shiftwidth=4:softtabstop=0:noexpandtab

cfg_jtag_targets := download-config
jtag_targets := dump erase download run reset $(cfg_jtag_targets)

#
# JTAG targets
#
.PHONY: $(jtag_targets)

WAIT_FOR_DOWNLOAD := $(filter download,$(MAKECMDGOALS))

ifneq ($(filter %config,$(MAKECMDGOALS)),)
dlimage := ../../../../work/$(PROJECT_NAME)/$(CFG_TARGET_NAME).rom
dladdr := $(INSTALL_ADDRESS_CFG)
else
PART ?= $(word 1,$(PARTITION_NAMES))
dlimage := ../../../work/$(PROJECT_NAME)/project/project$(PART).rom
dladdr := $(INSTALL_ADDRESS_FW$(PART))
endif

ifneq ($(filter download%,$(MAKECMDGOALS)),)
ifeq ($(words $(wildcard $(dlimage))),0)
$(error No download image found)
endif
endif

ocd_dir = ../../../jtag/openocd
ifeq ($(HOST_PLATFORM),Linux)
ocd_bin = $(ocd_dir)/Linux64/openocd-all-brcm-libftdi
else
ocd_bin = $(ocd_dir)/Win32/openocd-all-brcm-libftdi.exe
endif
ocd_adapter = Olimex_ARM-USB-TINY-H
ocd_board = BCM4390x
ocd_flash_helper = bcm4390x-sflash-write.tcl
ocd_flash_write_app = bcm4390x_sflash_write.elf

ifeq ($(START),)
ocd_flash_dump_start = 0x0
else
ocd_flash_dump_start = $(START)
endif
ifeq ($(LENGTH),)
ocd_flash_dump_length = 0x4000
else
ocd_flash_dump_length = $(LENGTH)
endif

$(ocd_logpath) :
	@$(MKDIR) -p $(WORK_DIRECTORY)/$(PROJECT_NAME)/

dump : | $(ocd_logpath)
	$(quiet)fname=flash_`date +%m-%d-%H%M%S`.bin ; \
	echo ; \
	echo "Dumping flash at $(ocd_flash_dump_start) length $(ocd_flash_dump_length) to $$fname" ; \
	$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -f $(ocd_dir)/$(ocd_flash_helper) \
	  -c "sflash_read_file $(ocd_dir)/$(ocd_flash_write_app) $$fname $(ocd_flash_dump_start) $(ocd_flash_dump_length)" \
	  -c shutdown \
	  $(output) ;

erase : | $(ocd_logpath)
	$(quiet)echo "Erasing flash" ; \
	$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -f $(ocd_dir)/$(ocd_flash_helper) \
	  -c "sflash_erase $(ocd_dir)/$(ocd_flash_write_app) $(ocd_loglevel)" \
	  -c shutdown \
	  $(output) ;

download $(cfg_jtag_targets) : | $(ocd_logpath)
	@echo "Downloading $(dlimage) to $(dladdr)"
	$(quiet)$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -f $(ocd_dir)/$(ocd_flash_helper) \
	  -c "sflash_write_file $(ocd_dir)/$(ocd_flash_write_app) $(dlimage) $(dladdr) $(ocd_loglevel)" \
	  -c shutdown \
	  $(output) ; rc=$$? ; echo -n "Download " ; \
	  [ $$rc -eq 0 ] && echo "successful" || (echo "failed" ; exit 1)

run : $(WAIT_FOR_DOWNLOAD) | $(ocd_logpath)
	@echo "Resetting target"
	$(quiet)$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -c init -c "reset run" -c shutdown \
	  $(output) && \
	  echo "Target running"

reset : | $(ocd_logpath)
	$(quiet)$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -c init -c "reset init" -c shutdown \
	  $(output) && \
	  echo "Target reset"

halt : | $(ocd_logpath)
	$(quiet)$(ocd_bin) $(ocd_dbg) \
	  -f $(ocd_dir)/$(ocd_adapter).cfg \
	  -f $(ocd_dir)/$(ocd_board).cfg \
	  -c init -c "reset halt" -c shutdown \
	  $(output) && \
	  echo "Target halted"
