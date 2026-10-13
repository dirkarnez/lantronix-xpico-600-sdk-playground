# -----------------------------------------------------------------------------------
# DESCRIPTION:
# This file defines MODULE_NAMES used by this project.
# -----------------------------------------------------------------------------------

MODULE_NAMES := \
    cli \
    discovery \
    main \
    security \
    mqtt \
    websockets \
    ntp \
    line_to_mqtt_example \
    $(if $(filter xPico200,$(PLATFORM_NAME)),usb_device) \

EXCLUDED_MODULES := \
    line_to_mqtt \
