# vim:tabstop=4:shiftwidth=4:softtabstop=0:noexpandtab

LANTRONIX_SOURCE_FILES := \
    aes \
    azure_iot \
    ble_beacon_scanner \
    bluetooth \
    bridge \
    cli \
    percepxion \
    discovery \
    gatt_server \
    line_to_mqtt \
    lpd \
    main \
    modbus \
    modem_emulation \
    monitor \
    mqtt \
    mux \
    ntp \
    security \
    smtp \
    snmp \
    spp \
    tunnel \
    usb_device \
    usb_host \
    user_data \
    virtual_line \
    websockets \
    xnetwork \
    xserial \

define MODULE_ECLIPSE_template

ifeq ($(1),$(filter $(1),$(LANTRONIX_SOURCE_FILES)))

$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).elf: \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/modules/$(1)/$(1)$(2).elf
	@echo $$(notdir $$@)
	@$(MKDIR) -p $$(dir $$@)
	@cp -f $$< $$@

else

$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).elf: \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/modules/$(1)/$(1)$(2).symbols.elf \
  $(LANTRONIX_DIRECTORY)/module_final.ld \
  $(PREVIOUS_ELF_FILE)
	@echo $$(notdir $$@)
	@$(MKDIR) -p $$(dir $$@)
	$(quiet)$(CC) \
	  $$(LDFLAGS) -Wl,-Map,$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).map \
	  -Wl,-T $(LANTRONIX_DIRECTORY)/module_final.ld \
	  -Wl,--defsym,ltrx_linker_module_$(1)_flash_end=ltrx_linker_module_flash_end \
	  -Wl,--defsym,ltrx_linker_module_$(1)_ram_end=ltrx_linker_module_ram_end \
	  -Wl,--start-group \
	  -Ttext $$(call SYMBOL_VALUE,$(PREVIOUS_ELF_FILE),ltrx_linker_module_$(PREVIOUS_MODULE)_flash_end) \
	  -Tdata $$(call SYMBOL_VALUE,$(PREVIOUS_ELF_FILE),ltrx_linker_module_$(PREVIOUS_MODULE)_ram_end) \
	  $(WORK_DIRECTORY)/$(PROJECT_NAME)/modules/$(1)/$(1)$(2).symbols.elf \
	  -Wl,--end-group \
	  -o $$@

$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).cmd: \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).elf \
  $(PREVIOUS_ELF_FILE)
	@echo $$(notdir $$@)
	@echo "add-symbol-file $(WORK_NORMALIZED_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(1)/$(1)$(2).elf 0" > $$@

endif

PREVIOUS_ELF_FILE := $(WORK_DIRECTORY)/$(PROJECT_NAME)/modules/$(1)/$(1)$(2).elf
PREVIOUS_MODULE := $(1)

endef # MODULE_ECLIPSE_template

define MODULE_ECLIPSE_IMAGE_template
$$(foreach MODULE,$(MODULE_ORDERED_NAMES),$$(eval $$(call MODULE_ECLIPSE_template,$(strip $$(MODULE)),$(1))))
endef

ifeq ($(words $(PARTITION_NAMES)),0)
$(foreach MODULE,$(MODULE_ORDERED_NAMES),$(eval $(call MODULE_ECLIPSE_template,$(strip $(MODULE)))))
else
$(foreach PART,$(PARTITION_NAMES),$(eval $(call MODULE_ECLIPSE_IMAGE_template,$(PART))))
endif

define ECLIPSE_STARTUP_IMAGE_template
$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/startup$(1).txt : \
  $(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/main/main$(1).elf \
  $$(foreach MODULE,$$(filter-out $(LANTRONIX_SOURCE_FILES),$(MODULE_ORDERED_NAMES)),$(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(strip $$(MODULE))/$(strip $$(MODULE))$(1).cmd)
	@echo $$(notdir $$@)
	@echo "" > $$@
	$(veryquiet)$$(foreach MODULE,$(filter-out $(LANTRONIX_SOURCE_FILES),$(MODULE_ORDERED_NAMES)), \
	  cat \
	    $(WORK_DIRECTORY)/$(PROJECT_NAME)/Eclipse/$(strip $$(MODULE))/$(strip $$(MODULE))$(1).cmd >> $$@; \
	  echo $$$$'\r\n' >> $$@; \
	)
endef

ifeq ($(words $(PARTITION_NAMES)),0)
$(eval $(call ECLIPSE_STARTUP_IMAGE_template,))
else
$(foreach PART,$(PARTITION_NAMES),$(eval $(call ECLIPSE_STARTUP_IMAGE_template,$(strip $(PART)))))
endif

